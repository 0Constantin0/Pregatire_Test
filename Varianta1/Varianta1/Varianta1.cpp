// Varianta1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//nou->rez->id = rez->id;
//nou->rez->denumire_hotel = (char*)malloc((strlen(rez->denumire_hotel) + 1) * sizeof(char));
//strcpy(nou->rez->denumire_hotel, rez->denumire_hotel);
//nou->rez->nr_camere_rezervate = rez->nr_camere_rezervate;
//nou->rez->nume_client = (char*)malloc((strlen(rez->nume_client) + 1) * sizeof(char));
//strcpy(nou->rez->nume_client, rez->nume_client);
//nou->rez->perioada_rezervarii = (char*)malloc((strlen(rez->perioada_rezervarii) + 1) * sizeof(char));
//strcpy(nou->rez->perioada_rezervarii, rez->perioada_rezervarii);
//nou->rez->suma_plata = rez->suma_plata;
// Despre rezervare

//if (strcmp(aux->rez->denumire_hotel, nume) == 0) {
//	ht->list[i] = ht->list[i]->next;
//	free(aux->rez->denumire_hotel);
//	free(aux->rez->nume_client);
//	free(aux->rez->perioada_rezervarii);
//	free(aux);
//}
//else {
//	Nod * x = aux->next;
//	while (x) {
//		Nod * temp = x;
//		if (strcmp(temp->rez->denumire_hotel, nume) == 0) {
//			free(temp->rez->denumire_hotel);
//			free(temp->rez->nume_client);
//			free(temp->rez->perioada_rezervarii);
//			free(temp);
//		}
//		aux = aux->next;
//	}
//}

struct Rezervare {
	unsigned int id;
	char* denumire_hotel;
	int nr_camere_rezervate;
	char * nume_client;
	char * perioada_rezervarii;
	float suma_plata;
};
void afisareRezervare(Rezervare * rez) {
	printf("Id = %d\n", rez->id);
	printf("Denumire hotel = %s\n", rez->denumire_hotel);
	printf("Nr camere rezervate = %d\n", rez->nr_camere_rezervate);
	printf("Nume Client = %s\n", rez->nume_client);
printf("Perioada Rezervarii = %s\n", rez->perioada_rezervarii);
printf("Suma de plata = %.2f\n", rez->suma_plata);
printf("\n");
}
Rezervare* citireRezervare(FILE *f) {
	Rezervare *nou = (Rezervare*)malloc(sizeof(Rezervare));
	char temp[20];
	fscanf(f, "%u", &nou->id);
	fscanf(f, "%s", temp);
	nou->denumire_hotel = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->denumire_hotel, temp);
	fscanf(f, "%d", &nou->nr_camere_rezervate);
	fscanf(f, "%s", temp);
	nou->nume_client = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->nume_client, temp);
	fscanf(f, "%s", temp);
	nou->perioada_rezervarii = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->perioada_rezervarii, temp);
	fscanf(f, "%f", &nou->suma_plata);
	return nou;
}
//Despre Nod
struct Nod {
	Rezervare *rez;
	Nod *next;
};
Nod* creareNod(Rezervare *rez) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = 0;
	nou->rez = rez;
	return nou;

}
Nod* inserareSfarsit(Nod* list, Rezervare *rez) {
	Nod * nou = creareNod(rez);
	if (!list) {
		return nou;
	}
	else {
		Nod* aux = list;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	return list;
}

//Despre Hashtable
struct HashTable {
	int dim;
	Nod* *list;
};
int hashFunction(char *serie, int dim) {
	int sum = 0;
	for (int i = 0; i < strlen(serie); i++)
		sum += serie[i];
	return sum % dim;
}
HashTable initializareHAshTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.list = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < dim; i++) {
		ht.list[i] = 0;
	}
	return ht;
}
HashTable inserareHashTable(HashTable ht, Rezervare *rez) {
	int cod = hashFunction(rez->denumire_hotel, ht.dim);
	ht.list[cod] = inserareSfarsit(ht.list[cod], rez);
	return ht;
}
void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		Nod *aux = ht.list[i];
		while (aux) {
			afisareRezervare(aux->rez);
			aux = aux->next;

		}
		printf("\n");

	}
}
int camereNecesare(HashTable ht, const char * date) {
	int sum = 0;
	for (int i = 0; i < ht.dim; i++) {
		Nod *aux = ht.list[i];
		while (aux) {
			if (strcmp(aux->rez->perioada_rezervarii, date) == 0) {
				sum += aux->rez->nr_camere_rezervate;
			}
			aux = aux->next;
		}
	}
	return sum;
}
HashTable stergereRezervari(HashTable ht, char * nume) {
	int cod = hashFunction(nume,ht.dim);
	if (ht.list[cod]) {
		Nod * aux = ht.list[cod];
		//Nod * aux1 = ht.list[cod];
		//if (strcmp(aux1->rez->denumire_hotel, nume) == 0) {
		//	ht.list[cod] = aux1->next;
		//	free(aux1->rez->denumire_hotel);
		//	free(aux1->rez->nume_client);
		//	free(aux1->rez->perioada_rezervarii);
		//	free(aux1);
		//}
		while (aux) {
			Nod * kiss = aux;
			aux = aux->next;
			if (strcmp(kiss->rez->denumire_hotel, nume) == 0) {
				if (kiss == ht.list[cod]) {
					ht.list[cod] = kiss->next;
				}
				Nod * temp = kiss;
				free(temp->rez->denumire_hotel);
				free(temp->rez->nume_client);
				free(temp->rez->perioada_rezervarii);
				free(temp);
			}
			
		}
		ht.list[cod] = 0;
	}
	return ht;
}
int main()
{
	HashTable ht;
	int x = 0;
	FILE *f = fopen("fisier.txt", "r");
	if (f) {
		fscanf(f, "%d", &x);
		ht = initializareHAshTable(x);
		for (int i = 0; i < x; i++) {
			ht = inserareHashTable(ht, citireRezervare(f));
		}
		afisareHashTable(ht);
		printf("Numar camere : %d", camereNecesare(ht, "12"));
		printf("\n");
		printf("\n");
		char temp[20] = "Moxa";
		ht = stergereRezervari(ht, temp);
		afisareHashTable(ht);
	}
    return 0;
}

