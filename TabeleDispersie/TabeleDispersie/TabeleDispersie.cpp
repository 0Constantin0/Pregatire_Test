// TabeleDispersie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string.h>
#include<stdio.h>
#include<malloc.h>

struct Student {
	char nrMat[10];
	char * nume;
	char facultate[10];
	float avg;
};
struct Nod {
	Student * stud;
	Nod* next;
};
struct HashTable {
	Nod* *vector;
	int dim;
};
//Despre Student
void afisareStudent(Student * s) {
	printf("NrMat = %s\n", s->nrMat);
	printf("Nume = %s\n", s->nume);
	printf("Facultate = %s\n", s->facultate);
	printf("Media = %.2f \n", s->avg);
	printf("\n");
}
Student* citireStudent(FILE *f) {
	char temp[20];
	Student *nou = (Student*)malloc(sizeof(Student));
	fscanf(f, "%s", nou->nrMat);
	fscanf(f, "%s", temp);
	nou->nume = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->nume, temp);
	fscanf(f, "%s", nou->facultate);
	fscanf(f, "%f", &(nou->avg));
	return nou;
}

//Despre nod
Nod* inserareSfarsit(Nod* list, Student * stud) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->stud = stud;
	nou->next = 0;
	if (!list) {
		return nou;
	}
	else
	{
		Nod* aux = list;
		while (aux->next)
			aux = aux->next;
		aux->next = nou;
	}
	return list;
}
Nod* creareNod(Student * stud) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->stud = stud;
	nou->next = 0;
	return nou;

}
//Despre hashtable
int hashfunction(char * serie , int dim) {
	int s = 0;
	for (int i = 0; i < strlen(serie); i++) {
		s += serie[i];
	}
	return s % dim;

}
HashTable initializareHashTable(int dim) {
	HashTable ht;
	ht.dim = dim;
	ht.vector = (Nod**)malloc(sizeof(Nod*)*dim);
	for (int i = 0; i < ht.dim; i++) {
		ht.vector[i] = 0;
		
	}
	return ht;
}
int inserareHAshTable(HashTable ht, Student* stud) {
	if (ht.vector) {
		int hashcode = hashfunction(stud->nrMat, ht.dim);
		if (ht.vector[hashcode]) {
			ht.vector[hashcode] = inserareSfarsit(ht.vector[hashcode], stud);
			return hashcode;
		}
		else {
			ht.vector[hashcode] = creareNod(stud);
			return hashcode;
		}
	}
	else return -1;

}
void afisareHashTable(HashTable ht) {
	
	for (int i = 0; i < ht.dim; i++) {
		if (ht.vector[i]) {
			Nod *p = ht.vector[i];
			while (p) {
				afisareStudent(p->stud);
				p = p->next;
			}
			

		}
	}
	
}
void stergereHashTable(HashTable *ht) {
	
	for (int i = 0; i < ht->dim; i++) {
		if (ht->vector[i]) {
			Nod * aux = ht->vector[i];
			while (aux) {
				Nod * temp = aux;
				aux = aux->next;
			free(temp->stud->nume);
			free(temp->stud);
			free(temp);
			}
			ht->vector[i] = 0;
		}
	}
	free(ht->vector);
	ht->dim = 0;
	ht->vector = 0;
}
Student* gasireStudent(char *serie,HashTable ht) {
	int x = hashfunction(serie, ht.dim);
	Nod * cauta = ht.vector[x];
	if (cauta) {
		if (strcmp(cauta->stud->nrMat, serie) == 0)
			return cauta->stud;
		else cauta = cauta->next;
	}
	Student * s = (Student*)malloc(sizeof(Student));
	strcpy(s->nrMat , "");
	s->nume = 0;
	strcpy(s->facultate, "");
	s->avg = 0;
	return s;
}
int main()
{
	int x = 0;
	HashTable ht;
	ht = initializareHashTable(5);
	FILE *f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &x);
	for (int i = 0; i < x; i++) {
		inserareHAshTable(ht, citireStudent(f));
	}
	afisareHashTable(ht);
	printf("\n");
	char temp[10] = "a14";
	afisareStudent(gasireStudent(temp,ht));
	stergereHashTable(&ht);
	afisareHashTable(ht);
    return 0;
}

