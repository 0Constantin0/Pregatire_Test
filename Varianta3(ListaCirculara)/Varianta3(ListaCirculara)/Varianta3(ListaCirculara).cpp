// Varianta3(ListaCirculara).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//Despre rezervare
struct Rezervare {
	unsigned int id;
	char* denumire_hotel;
	unsigned char nr_camere_rezervate;
	char * nume_client;
	char * perioada_rezervare;
	float valoare;
};
Rezervare* citireRezervare(FILE *f) {
	Rezervare * nou = (Rezervare*)malloc(sizeof(Rezervare));
	char temp[30];
	fscanf(f, "%d", &nou->id);
	fscanf(f, "%s", temp);
	nou->denumire_hotel = (char*)malloc(sizeof(char)*((strlen(temp) + 1)));
	strcpy(nou->denumire_hotel, temp);
	fscanf(f, "%hhu", &nou->nr_camere_rezervate);
	fscanf(f, "%s", temp);
	nou->nume_client = (char*)malloc(sizeof(char)*((strlen(temp) + 1)));
	strcpy(nou->nume_client, temp);
	fscanf(f, "%s", temp);
	nou->perioada_rezervare = (char*)malloc(sizeof(char)*((strlen(temp) + 1)));
	strcpy(nou->perioada_rezervare, temp);
	fscanf(f, "%f", &nou->valoare);
	return nou;

}
void afisareRezervare(Rezervare * s) {
	printf("Id = %u\n", s->id);
	printf("Denumire Hotel = %s\n", s->denumire_hotel);
	printf("Nr camere rezervate = %hhu\n", s->nr_camere_rezervate);
	printf("Nume Client = %s\n", s->nume_client);
	printf("Perioada rezervare = %s\n", s->perioada_rezervare);
	printf("valoare = %.2f\n", s->valoare);
	printf("\n");
}
//Despre Nod
struct NodDublu {
	Rezervare * rez;
	NodDublu *next;
	NodDublu * prev;
};
NodDublu* creareNodDublu(Rezervare *s) {
	NodDublu * nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->next = 0;
	nou->prev = 0;
	nou->rez = s;
	return nou;
}
//Despre ListaDubla
struct ListaDubla {
	NodDublu *inceput;
	NodDublu * sfarsit;
};
ListaDubla inserareListaDubla(ListaDubla list, Rezervare * rez) {
	NodDublu * nou = creareNodDublu(rez);
	if (!list.inceput) {
		list.inceput = list.sfarsit = nou;
		nou->next = nou;
		nou->prev = nou;
		return list;
	}
	else {
		nou->next = list.sfarsit->next;
		nou->prev = list.sfarsit;
		list.inceput->prev = nou;
		list.sfarsit->next = nou;
		list.sfarsit = nou;
		return list;
	}
}
void afisareListaDubla(ListaDubla list) {
	NodDublu * aux = list.sfarsit;
	while (aux!=list.inceput) {
		afisareRezervare(aux->rez);
		aux = aux->prev;
	}
	afisareRezervare(list.inceput->rez);
}
float incasariPotentiale(ListaDubla list, char * nume) {
	float s = 0;
	NodDublu *aux = list.inceput;
	while (aux!=list.sfarsit) {
		if (strcmp(aux->rez->perioada_rezervare, nume )== 0) {
			s += aux->rez->valoare;
		}
		aux = aux->next;
	}
	if (strcmp(list.sfarsit->rez->perioada_rezervare, nume) == 0) {
		s += list.sfarsit->rez->valoare;
	}
	return s;
}
int numarCamere(ListaDubla list, char * nume) {
	NodDublu * aux;
	aux = list.inceput;
	int x = 0;
	while (aux!= list.sfarsit) {
		if (strcmp(aux->rez->denumire_hotel, nume) == 0) {
			x += aux->rez->nr_camere_rezervate;
		}
		aux = aux->next;
	}
	if (strcmp(aux->rez->denumire_hotel, nume) == 0) {
		x += aux->rez->nr_camere_rezervate;
	}
	return x;
}
int main()
{
	int x = 0;
	FILE * f = fopen("fisier.txt", "r");
	if (f) {
		ListaDubla list;
		list.inceput = 0;
		list.sfarsit = 0;
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			list = inserareListaDubla(list, citireRezervare(f));
		}
		afisareListaDubla(list);
		char temp[10] = "12";
		printf("Incasarile potentiale pentru data %s sunt %.3f\n", temp, incasariPotentiale(list, temp));
		char tem1[10] = "ceva";
		printf("Numarul de camere rezervate la hotelul %s este %d\n", tem1, numarCamere(list, tem1));
		fclose(f);
	}
    return 0;
}

