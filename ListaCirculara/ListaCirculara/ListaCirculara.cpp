// ListaCirculara.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
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
Nod* inserareListaCirculara(Nod* list, Student *s) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->next = 0;
	nou->stud = s;
	if (!list) {
		nou->next = nou;
		return nou;
	}
	else {
		//Inserare in fata primului nod
		/*Nod* aux = list->next;
		list->next = nou;
		nou->next = aux;*/

		//Inserare la sfarsit de nod
		nou->next = list;
		Nod * aux = list;
		while (aux->next != list)
			aux = aux->next;
		aux->next = nou;
	}

	return list;
}
void afisareCirculara(Nod* list) {
	if (list) {
		Nod * aux = list->next;
		afisareStudent(list->stud);
		while (aux != list) {
			afisareStudent(aux->stud);
			aux = aux->next;
		}
	}
}
void scriereStudent(Student * stud,FILE *f) {
	fprintf(f, "nrMAt = %s \n", stud->nrMat);
	fprintf(f, "Nume = %s\n", stud->nume);
	fprintf(f, "Facultate = %s\n", stud->facultate);
	fprintf(f, "Media = %.2f \n", stud->avg);
	fprintf(f, "\n");
}
void scriereFisier(const char * nume, Nod* list) {
	if (list) {
		FILE *f = fopen(nume, "w");
		Nod * aux = list->next;
		scriereStudent(list->stud, f);
		while (aux != list) {
			scriereStudent(aux->stud,f);
			aux = aux->next;
		}
		fclose(f);
	}
	else printf("fisierul nu a fost creat");
}
int main()
{
	int x = 0;
	FILE *f = fopen("fisier.txt", "r");
	Nod *list = 0;
	if (f) {
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			list = inserareListaCirculara(list, citireStudent(f));
		}
		afisareCirculara(list);
		fclose(f);
		scriereFisier("Output.txt", list);
	}


    return 0;
}

