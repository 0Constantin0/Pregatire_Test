// Varianta2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//Despre Reteta
struct Reteta {
	unsigned int nr;
	int nr_medicamente;
	char** lista;
	char *numeMedic;
	double valoare;
	float procent_compensare;
};
Reteta* citireReteta(FILE *f) {
	char temp[30];
	Reteta * nou = (Reteta*)malloc(sizeof(Reteta));
	fscanf(f, "%u", &nou->nr);
	fscanf(f, "%i", &nou->nr_medicamente);
	nou->lista = (char**)malloc(sizeof(char*)*nou->nr_medicamente);
	for (int i = 0; i < nou->nr_medicamente; i++) {
		fscanf(f, "%s", temp);
		nou->lista[i] = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
		strcpy(nou->lista[i], temp);
	}
	fscanf(f, "%s", temp);
	nou->numeMedic = (char*)malloc(sizeof(char)*(strlen(temp) + 1));
	strcpy(nou->numeMedic, temp);
	fscanf(f, "%lf", &nou->valoare);
	fscanf(f, "%f", &nou->procent_compensare);
	return nou;
}
void afisareReteta(Reteta * r){
	printf("Nr reteta = %u\n", r->nr);
	printf("Nr medicamente = %d\n", r->nr_medicamente);
	for (int i = 0; i < r->nr_medicamente; i++) {
		printf("Lista Medicamente = %s\n", r->lista[i]);
	}
	printf("Nume medic = %s\n", r->numeMedic);
	printf("Valoare reteta = %lf\n", r->valoare);
	printf("Procent compensare = %.2f\n", r->procent_compensare);
}
//Despre Nod
struct Nod {
	Reteta * r;
	Nod * next;
};
Nod* creareNod(Reteta *r) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->next = 0;
	nou->r = r;
	return nou;
}
Nod * inserareSfarsit(Nod * list, Reteta * r) {
	Nod * nou = creareNod(r);
	if (!list) {
		return nou;
	}
	else {
		Nod * aux = list;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	return list;
}

//Despre HashTable
struct HashTable {
	int dim;
	Nod* *list;
};
int hashFunction(int nr, int dim) {
	int s = 0;
	while (nr != 0) {
		s += nr % 10;
		nr = nr / 10;
	}
	return s % dim;
}
HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.list = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < ht.dim; i++) {
		ht.list[i] = 0;
	}
	return ht;
}
HashTable inserareHashTable(HashTable ht, Reteta *r) {
	int cod = 0;
	if (ht.list) {
		cod = hashFunction(r->nr_medicamente, ht.dim);
		ht.list[cod] = inserareSfarsit(ht.list[cod], r);
	}
	return ht;
}
void traversare(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.list[i])
		{
			Nod * aux = ht.list[i];
			while (aux) {
				afisareReteta(aux->r);
				aux = aux->next;
			}	
		}		
	}
}
double valoareRetete(HashTable ht, double nr)
{
	int sum = 0;
	int cod = 0;
	cod = hashFunction(nr,ht.dim);
	if (ht.list[cod]) {
		Nod * aux = ht.list[cod];
		while (aux) {
			sum += aux->r->nr_medicamente;
			aux = aux->next;
		}
		
	}
	return sum;
}
int numarReteteMedic(HashTable ht, char * nume, int nr) {
	int cod = hashFunction(nr, ht.dim);
	int count = 0;
	if (ht.list[cod]) {
		Nod * aux = ht.list[cod];
		while (aux) {
			if (strcmp(aux->r->numeMedic, nume) == 0) {
				count++;
			}
			aux = aux->next;
		}

	}
	return count;
}
int main()
{
	int x = 0;
	HashTable ht;
	ht = initializareHashTable(5);
	FILE * f = fopen("fisier.txt", "r");
	if (f) {
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			ht = inserareHashTable(ht, citireReteta(f));
		}
		traversare(ht);
		printf("Numar medicamente pentru codul specificat este %lf\n", valoareRetete(ht, 3));
		char tem1[20] = "Constantin";
		printf("Numarul de retete ale doctorului %s este %d", tem1, numarReteteMedic(ht,tem1, 2));
		fclose(f);
	}
	

    return 0;
}

