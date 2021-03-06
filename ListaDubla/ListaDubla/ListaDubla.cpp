// ListaDubla.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<string.h>
#include<malloc.h>
struct Student {
	char nrMat[10];
	char * nume;
	char facultate[15];
	float avg;
};
struct Nod {
	Student *stud;
	Nod *prev;
	Nod *next;
};
struct ListaDbl {
	Nod *inceput, *sfarsit;
};
ListaDbl inserareSfarsit(ListaDbl list, Student stud) {
		Nod * nou= (Nod*)malloc(sizeof(Nod));
		nou->stud = (Student*)malloc(sizeof(Student));
		strcpy(nou->stud->nrMat, stud.nrMat);
		nou->stud->nume = (char*)malloc((strlen(stud.nume) + 1) * sizeof(char));
		strcpy(nou->stud->nume, stud.nume);
		strcpy(nou->stud->facultate, stud.facultate);
		nou->stud->avg = stud.avg;
		nou->prev = list.sfarsit;
		nou->next = 0;
		if (!list.inceput)
		{
			list.inceput = nou;
			list.sfarsit = nou;
		}
		else {
			list.sfarsit->next = nou;
			list.sfarsit = nou;
		}
		return list;
}
void afisareNod(Nod *p) {
	printf("NrMat= %s\n", p->stud->nrMat);
	printf("NrMat= %s\n", p->stud->nume);
	printf("NrMat= %s\n", p->stud->facultate);
	printf("NrMat= %.2f\n", p->stud->avg);
	printf("\n");
}
void afisareListaDubla(ListaDbl list) {
	if (list.inceput != 0)
	{
		Nod *p = list.inceput;
		while (p != list.sfarsit) {
			afisareNod(p);
			p = p->next;
		}
		afisareNod(p);
	}
	else printf("Lista este goala\n");
}
ListaDbl dezalocareListaDubla(ListaDbl list) {
	if (list.inceput != 0) {
		Nod *p = list.inceput, *dep=0;
		while (p != list.sfarsit) {
			dep = p->next;
			free(p->stud->nume);
			free(p->stud);
			p = dep;
		}
		free(p->stud->nume);
		free(p->stud);
		free(p);
		list.inceput = 0;
		list.sfarsit = 0;
	}
	return list;
}

ListaDbl inserareInceput(ListaDbl list, Student stud) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	nou->stud = (Student*)malloc(sizeof(Student));
	strcpy(nou->stud->nrMat, stud.nrMat);
	nou->stud->nume = (char*)malloc((strlen(stud.nume) + 1) * sizeof(char));
	strcpy(nou->stud->nume, stud.nume);
	strcpy(nou->stud->facultate, stud.facultate);
	nou->stud->avg = stud.avg;
	nou->prev = 0;
	nou->next = 0;
	if (list.inceput == 0 && list.sfarsit == 0)
	{
		list.inceput = nou;
		list.sfarsit = nou;
	}
	else {
		nou->next = list.inceput;
		list.inceput->prev = nou;
		list.inceput = nou;
	}
	return list;

}

ListaDbl inseraresortata(ListaDbl list, Student stud) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	Nod * x=list.inceput , *k = 0;
	nou->stud = (Student*)malloc(sizeof(Student));
	strcpy(nou->stud->nrMat, stud.nrMat);
	nou->stud->nume = (char*)malloc((strlen(stud.nume) + 1) * sizeof(char));
	strcpy(nou->stud->nume, stud.nume);
	strcpy(nou->stud->facultate, stud.facultate);
	nou->stud->avg = stud.avg;
	nou->prev = 0;
	nou->next = 0;
	if (list.inceput == 0 && list.sfarsit == 0) {
		list.inceput = nou;
		list.sfarsit = nou;
	}
	else {
		while (nou->stud->avg > x->stud->avg) {
			x = x->next;
		}
			
		nou->next = x;
		nou->prev = x->prev;
		if (x->prev)
		x->prev->next = nou;
		else list.inceput = nou;
		x->prev = nou;
	}
	return list;
}
int main()
{
	FILE *f;
	Student stud;
	stud.nume = 0;
	int x = 0;
	char temp[20];
	ListaDbl lista;
	lista.inceput = 0;
	lista.sfarsit = 0;

	f = fopen("fisier.txt", "r");
	if (f) {
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			fscanf(f, "%s", stud.nrMat);
			fscanf(f, "%s", temp);
			if (stud.nume != 0)
				free(stud.nume);
			stud.nume = (char*)malloc((strlen(temp) + 1) * sizeof(char));
			strcpy(stud.nume, temp);
			fscanf(f, "%s", stud.facultate);
			fscanf(f, "%f", &stud.avg);
			//lista = inserareSfarsit(lista, stud);
			//lista = inserareInceput(lista, stud);
			lista = inseraresortata(lista, stud);
		}

		if (stud.nume != 0)
			free(stud.nume);
		fclose(f);
		afisareListaDubla(lista);
		lista= dezalocareListaDubla(lista);
		afisareListaDubla(lista);
	}
	else printf("fisierul nu a fost deschis\n");

    return 0;
}

