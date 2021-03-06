// Varianta4Examen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
//Despre Examen
struct Examen {
	char* materie;
	unsigned int cod_materie;
	int nrStudenti;
	float *noteStudenti;
	int numarCredite;
};
Examen* citesteExamen(FILE *f) {
	Examen * nou = (Examen*)malloc(sizeof(Examen));
	char temp[20];
	fscanf(f, "%s", temp);
	nou->materie = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy(nou->materie, temp);
	fscanf(f, "%u", &nou->cod_materie);
	fscanf(f, "%d", &nou->nrStudenti);
	nou->noteStudenti = (float*)malloc(sizeof(float)*nou->nrStudenti);
	for (int i = 0; i < nou->nrStudenti; i++) {
		fscanf(f, "%f", &nou->noteStudenti[i]);
	}
	fscanf(f, "%d", &nou->numarCredite);
	return nou;
}
void afisareExamen(Examen *s) {
	printf("Materie = %s\n", s->materie);
	printf("Cod Materie = %u\n", s->cod_materie);
	printf("Nr studenti = %d\n", s->nrStudenti);
	for (int i = 0; i < s->nrStudenti; i++) {
		printf("Studentul %d are nota = %.2f\n",i,s->noteStudenti[i]);
	}
	printf("Numar credite = %d\n", s->numarCredite);
	printf("\n");
}

// Despre Nod
struct Nod {
	Examen * ex;
	Nod* next;
};
Nod* creareNod(Examen *s) {
	Nod *nou = (Nod*)malloc(sizeof(Nod));
	nou->ex = s;
	nou->next = 0;
	return nou;
}
Nod* inserareNod(Nod* list, Examen * s) {
	Nod * nou = creareNod(s);
	if (!list) {
		return nou;
	}
	else {
		Nod * aux = list;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	return list;
}

//Despre HashTable
struct HashTable {
	int dim;
	Nod * *vector;
};
int hashFunction(unsigned int cod, int dim) {
	int s = 0;
	while (cod != 0) {
		s += cod % 10;
		cod = cod / 10;
	}
	return s % dim;
}
HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod)*dim);
	for (int i = 0; i < dim; i++) {
		ht.vector[i] = 0;
	}
	return ht;
}
HashTable inserareHashTable(HashTable ht, Examen *s) {
	if (ht.vector) {
		Nod * nou = creareNod(s);
		int cod = hashFunction(s->cod_materie, ht.dim);
		ht.vector[cod] = inserareNod(ht.vector[cod], s);
	}
	return ht;
}
void afisareHashTable(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i])
		{
			Nod * aux = ht.vector[i];
			while (aux) {
				afisareExamen(aux->ex);
				aux = aux->next;
			}
		}
	}
}

//Lista DubluInlantuita
struct NodD {
	char* Materie;
	float ex;
	NodD *prev;
	NodD *next;
};
NodD* creareNod(float ex,char * nume) {
	NodD* nou = (NodD*)malloc(sizeof(NodD));
	nou->Materie = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(nou->Materie, nume);
	nou->ex = ex;
	nou->next = 0;
	nou->prev = 0;
	return nou;
}
struct ListaDB {
	NodD * inceput;
	NodD * sfarsit;
};
ListaDB inserareListaDB(ListaDB list, float s,char * nume) {
	NodD *nou = creareNod(s,nume);
	if (!list.inceput) {
		list.inceput = list.sfarsit = nou;
	}
	else {
		list.sfarsit->next = nou;
		nou->prev = list.sfarsit;
		list.sfarsit = nou;
	}
	return list;
}
float promovatiExamen(Nod *s) {
	float y = 0;
	while (s) {
		for (int i = 0; i < s->ex->nrStudenti; i++) {
			if (s->ex->noteStudenti[i] >= 5)
				y++;
		}
		s = s->next;
	}
	return y;
}
ListaDB procentPromovare(HashTable ht) {
	ListaDB list;
	list.inceput = 0;
	list.sfarsit = 0;
	float s = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod * aux = ht.vector[i];
			if(aux)
			{
				s = (promovatiExamen(aux)/aux->ex->nrStudenti)*100;
				list = inserareListaDB(list, s, aux->ex->materie);
			}
		}
	}
	return list;

}
void afisarepromovare(NodD* list) {
	printf("Materia = %s are un procent de promovabilitate de %f\n", list->Materie,list->ex);
}
void afisareListaDB(ListaDB list) {
	NodD * aux = list.inceput;
	while (aux) {
		afisarepromovare(aux);
		aux = aux->next;
	}
}
Examen* citireExamenSTR(FILE *f, char * buffer) {
	Examen * ex = (Examen*)malloc(sizeof(Examen));
	char * token;
	token = strtok(buffer, ";");
	ex->materie = (char*)malloc(sizeof(char)*(strlen(token) + 1));
	strcpy(ex->materie, token);
	token = strtok(NULL, ";");
	ex->cod_materie = atoi(token);
	token = strtok(NULL, ";");
	ex->nrStudenti = atoi(token);
	ex->noteStudenti = (float*)malloc(sizeof(float)*ex->nrStudenti);
	for (int i = 0; i < ex->nrStudenti; i++) {
		token = strtok(NULL, ";");
		ex->noteStudenti[i] = atof(token);
	}
	token = strtok(NULL, ";");
	ex->numarCredite = atoi(token);
	return ex;

}
int main()
{
	int x = 0;
	HashTable ht;
	ListaDB list;
	list.inceput = 0;
	list.sfarsit = 0;
	ht = initializareHashTable(4);
	char buffer[200];
	FILE *f = fopen("fisier1.txt", "r");
	if (f) {
		while (fgets(buffer, 200, f)) {
			
			ht = inserareHashTable(ht, citireExamenSTR(f,buffer));		
		}
		/*fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			ht = inserareHashTable(ht, citesteExamen(f));
		}
		*/
		afisareHashTable(ht);
		list = procentPromovare(ht);
		afisareListaDB(list);
	}
    return 0;
}

