// Coada.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct Student {
	char nrMat[10];
	char* nume;
	char facultate[10];
	float avg;
};
struct Nod {
	Student *stud;
	Nod * next;
};
Student * creareStudent(Student * s) {
	Student * nou = (Student*)malloc(sizeof(Student));
	strcpy(nou->nrMat, s->nrMat);
	nou->nume = (char*)malloc((strlen(s->nume) + 1) * sizeof(char));
	strcpy(nou->nume, s->nume);
	strcpy(nou->facultate, s->facultate);
	nou->avg = s->avg;
	return nou;
}
void afisareStudent(Student * s) {
	if (s) {
		printf("nrMAt = %s \n", s->nrMat);
		printf("Nume = %s\n", s->nume);
		printf("Facultate = %s\n", s->facultate);
		printf("Media = %.2f \n", s->avg);
		printf("\n");
	}
}
//Hello
Student * citireStudent(FILE *f) {
	Student * nou = (Student *)malloc(sizeof(Student));
	char temp[20];
	fscanf(f, "%s", nou->nrMat);
	fscanf(f, "%s", temp);
	nou->nume = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(nou->nume, temp);
	fscanf(f, "%s", nou->facultate);
	fscanf(f, "%f", &nou->avg);
	return nou;
}
Nod* inserareSfarsit(Nod*list, Student *s) {
	Nod *nou = (Nod*)malloc(sizeof(Nod));
	nou->stud = creareStudent(s);
	nou->next = 0;
	Nod * aux = list;
	if (!aux) {
		
		return nou;
	}
	else {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;

		return list;
	}
}
Nod * putLista(Nod* list, Student * s) {
	list = inserareSfarsit(list, s);
	return list;
}
void afisareLista(Nod * list) {
	if (list) {
		while (list) {
			afisareStudent(list->stud);
			list = list->next;
		}
	}
	else printf("Lista este goala\n");
}

Student* getLista(Nod* *list) {
	if (list) {
		Student * nou = creareStudent((*list)->stud);
		Nod * aux = (*list)->next;
		if ((*list)->stud->nume)
			free((*list)->stud->nume);
		free((*list));
		*list = aux;
		return nou;
	}
	else printf("Coada este goala");
}
void afisareGetLista(Nod* *list) {
	while (*list) {
		afisareStudent(getLista(list));
	}
}
int main()
{
	int x = 0;
	FILE *f = fopen("fisier.txt", "r");
	Nod * lista = 0;
	if (f) {
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			//lista = inserareSfarsit(lista, citireStudent(f));
			lista = putLista(lista, citireStudent(f));
		}
		afisareGetLista(&lista);
		//afisareLista(lista);

	}
	else printf("Fisierul nu a fost deschis");
    return 0;
}

