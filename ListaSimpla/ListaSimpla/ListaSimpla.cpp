#include "stdafx.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct Student {
	char nrMat[6];
	char* nume;
	char facultate[7];
	float avg;

};
struct Nod {
	Student stud;
	Nod *next;
};
Nod* inserareSfarsit(Nod *n, Student s) {
	Nod *nou = (Nod*)malloc(sizeof(Nod));
	strcpy(nou->stud.nrMat, s.nrMat);
	nou->stud.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->stud.nume, s.nume);
	strcpy(nou->stud.facultate, s.facultate);
	nou->stud.avg = s.avg;
	nou->next = 0;
	if (!n) {
		return nou;
	}
	else
	{
		Nod * t;
		t = n;
		while (t->next)
			t = t->next;
		t->next = nou;
	}
	return n;

}
void afisareLista(Nod * t) {
	
	if (t != 0) {
		Nod * n = t;
		while (n)
		{
			printf("NrMat = %s\n", n->stud.nrMat);
			printf("Nume = %s\n", n->stud.nume);
			printf("Facultate = %s\n", n->stud.facultate);
			printf("Media = %.2f\n", n->stud.avg);
			n = n->next;
			printf("\n");
		}
	}
	else printf("Lista e goala\n");
}
Nod* InserareInceput(Nod *n, Student s) {
	Nod * nou = (Nod*)malloc(sizeof(Nod));
	strcpy(nou->stud.nrMat, s.nrMat);
	nou->stud.nume = (char *)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->stud.nume, s.nume);
	strcpy(nou->stud.facultate, s.facultate);
	nou->stud.avg = s.avg;
	nou->next = 0;
	if (!n)
	{
		return nou;
	}
	else {
		nou->next = n;
		return nou;
	}
}
Nod * stergereNod(Nod *n, char mat[6]) {
	Nod *a, *p;
	//Daca este primul
	if (strcmp(n->stud.nrMat, mat) == 0) {
		a = n;
		n = n->next;
		free(a->stud.nume);
		free(a);
		return n;
	}
	//Daca este in interior
	else
	{
		p = n;
		a = n->next;
		while (a->next) {
			if (strcmp(a->stud.nrMat, mat) == 0) {
				p->next = a->next;
				free(a->stud.nume);
				free(a);
				return n;
			}
			p = a;
			a = a->next;
		}
		if ((strcmp(a->stud.nrMat, mat) == 0))
		{
			p->next = a->next;
			free(a->stud.nume);
			free(a);
			return n;
		}
	}
	return n;
}
Nod* interschimbare(Nod* p, char* snume) {
	Nod *urm, *act;
	if (!p || !p->next)
		return p;
	//Daca e la inceput
	if (strcmp(p->stud.nume, snume) == 0) {
		act = p;
		urm = p->next;
		act->next = urm->next;
		urm->next = act;
		p = urm;
	}
	//Daca este in interior
	else
	{
		act = p;
		urm = p->next;
		while (urm->next && strcmp(urm->stud.nume, snume) != 0) {
			urm = urm->next;
			act = act->next;
		}
		if (urm->next) {
			Nod *k, *p;
			p = urm->next;
			act->next = p;
			k = p->next;
			p->next = urm;
			urm->next = k;


		}

	}
	return p;

}
Nod* dezalocarelista(Nod *p) {
	Nod * x = 0;
	while (p) {
		x = p->next;
		if (p->stud.nume != 0)
			free(p->stud.nume);
		free(p);
		p = x;
	}
	p = 0;
	return p;
}

Nod* inserareSortata(Nod* p, Student s) {
	Nod *nou = (Nod*)malloc(sizeof(Nod));
	strcpy(nou->stud.nrMat, s.nrMat);
	nou->stud.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->stud.nume, s.nume);
	strcpy(nou->stud.facultate, s.facultate);
	nou->stud.avg = s.avg;
	nou->next = 0;
	Nod * x = p, *y=0, *k=0;
	if (!x){
		return nou;
	}
	else {

		while (x) {
			if (nou->stud.avg <= x->stud.avg) {
				nou->next = x;
				x = nou;
				if (k!=0)
				return k;
				else return x;
			}
			else {
				k = x;
				y = x->next;
				k->next = nou;
				x = y;
			}
		}
	}
}
int main()
{
	FILE *f, *g;
	f = fopen("fisier.txt", "r");
	Student stud;
	stud.nume = 0;
	char temp[20];
	Nod *lista = 0;
	int x = 0;
	//Citirea din fisier text
	if (f)
	{
		fscanf(f, "%d", &x);
		for (int i = 0; i < x; i++) {
			fscanf(f, "%s", stud.nrMat);
			fscanf(f, "%s", temp);
			if (stud.nume!=NULL) {
			free(stud.nume); 
			}
			stud.nume = (char*)malloc((strlen(temp) + 1) * sizeof(char));
			strcpy(stud.nume, temp);
			fscanf(f, "%s", stud.facultate);
			fscanf(f, "%f", &stud.avg);
			//lista = InserareInceput(lista, stud);
			//lista = inserareSfarsit(lista, stud);
			lista = inserareSortata(lista, stud);
			
		}
		afisareLista(lista);
		char tem[10] = "George";
		//stergereNod(lista,tem);
		printf("\n");
		//lista = interschimbare(lista, tem);
		//afisareLista(lista);
		fclose(f);
		printf("\n");
		printf("\n");
		lista = dezalocarelista(lista);
		printf("\n");
		afisareLista(lista);
	}
	else
		printf("Fisierul nu a fost gasit");


	//Scriere in fisier binar
	/*g = fopen("fisier.dat", "wb");
	if (f)
	{
	fwrite(stud.nrMat, sizeof(stud.nrMat),1, f);
	int x = strlen(stud.nume);
	fwrite(&x, sizeof(int), 1, g);
	fwrite(stud.nume, x, 1, g);
	fwrite(stud.facultate, sizeof(stud.facultate), 1, g);
	fwrite(&stud.avg, sizeof(stud.avg), 1, g);

	}*/
	return 0;
}