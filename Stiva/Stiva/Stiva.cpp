// Stiva.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<string.h>
#include<malloc.h>
struct Student {
	char nrMat[10];
	char * nume;
	char facultate[10];
	float avg;
};
struct Nod {
	Student *stud;
	Nod *next;
};
Student* citireStudent(FILE *f) {
	char temp[20];
	Student *nou = (Student*)malloc(sizeof(Student));
	fscanf(f,"%s",nou->nrMat);
	fscanf(f, "%s", temp);
	nou->nume = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->nume, temp);
	fscanf(f, "%s", nou->facultate);
	fscanf(f, "%f", &nou->avg);
	return nou;
}
Nod* inserareInceput(Nod * list, Student *stud) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->stud = stud;
	nou->next = 0;
	if (!list) {
		return nou;
	}
	else {
		nou->next = list;
		return nou;
	}
}
void afisareStudent(Student * s) {
	if (s) {
		printf("nrMat = %s\n", s->nrMat);
		if (s->nume)
			printf("nume= %s\n", s->nume);
		printf("Facultate= %s\n", s->facultate);
		printf("Media = %.2f\n", s->avg);
		printf("\n");
	}
}
void afisareLista(Nod* list) {
	if (!list)
		printf("Lista e goala");
	else {
		while (list) {
			afisareStudent(list->stud);
			list = list->next;
		}
	}
	
}
Nod* dezalocareLista(Nod* list) {
	Nod *x = list;
	while (x) {
		list = x;
		if (list->stud->nume)
			free(list->stud->nume);
		x = list->next;
		free(list);
		list = 0;
	}
	return list;
}

//Pentru stiva
Nod* pushStack(Nod*lista, Student* stud) {
	lista = inserareInceput(lista, stud);
	return lista;
}
int main()
{
	int x = 0;
	FILE *f = fopen("fisier.txt", "r");
	Nod * list = 0;
	if (f) {
		fscanf(f, "%d", &x);
		for (int i = 0 ; i < x;i++)
		list = inserareInceput(list, citireStudent(f));
	}
	else printf("Fisierul nu a fost deschis");
	afisareLista(list);
	list = dezalocareLista(list);
	afisareLista(list);
}

