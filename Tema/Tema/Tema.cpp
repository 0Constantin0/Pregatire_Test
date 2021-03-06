// Tema.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include<string>
#include<malloc.h>

struct Produs {
	int id;
	float pret;
	char * denumire;
	int nrmagazine;
	int *stocMagazine;
};
//void scrieFisierBinar(Produs p,FILE* *f) {
//	fwrite(&p.id,sizeof(int),1,*f);
//	fwrite(&p.pret, sizeof(float), 1, *f);
//	int x = strlen(p.denumire) + 1;
//	fwrite(&x, sizeof(int), 1, *f);
//	fwrite(p.denumire, x, 1, *f);
//	//x = sizeof(p.stocMagazine) / sizeof(int);
//	fwrite(p.stocMagazine,sizeof(int), sizeof(p.stocMagazine), *f);
//	//fwrite()
//}


//Lucru cu Produsul
Produs creareConsola() {
	Produs p;
	printf("Id = "); scanf("%d", &p.id); printf("\n");
	printf("Pret = "); scanf("%f", &p.pret); printf("\n");
	printf("Denumire = ");
	char temp[20];
	scanf("%s", temp);
	p.denumire = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(p.denumire, temp);
	printf("\n");
	printf("Introduceti nr magazinelor ");
	scanf("%d", &p.nrmagazine);
	printf("\n");
	p.stocMagazine = (int *)malloc(sizeof(int)*p.nrmagazine);
	for (int i = 0; i < p.nrmagazine; i++) {
		printf("Pentru magazinul %d ", i + 1);
		scanf("%d",&p.stocMagazine[i]);
		printf("\n");
	}
	return p;

}
void creareConsola1(Produs * p) {
	printf("Id = "); scanf("%d", &(*p).id); printf("\n");
	printf("Pret = "); scanf("%f", &(*p).pret); printf("\n");
	printf("Denumire = ");
	char temp[20];
	scanf("%s", temp);
	(*p).denumire = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy((*p).denumire, temp);
	printf("\n");
	printf("Introduceti nr magazinelor ");
	scanf("%d", &(*p).nrmagazine);
	printf("\n");
	(*p).stocMagazine = (int *)malloc(sizeof(int)*(*p).nrmagazine);
	for (int i = 0; i < (*p).nrmagazine; i++) {
		printf("Pentru magazinul %d ", i + 1);
		scanf("%d", &(*p).stocMagazine[i]);
		printf("\n");
	}
}
void afisareProdus(Produs *p) {
	printf("id = %d\n", (*p).id);
	printf("pret =%.2f\n", (*p).pret);
	printf("denumire = %s\n", (*p).denumire);
	for (int i = 0; i < (*p).nrmagazine; i++)
		printf("\t\t magazinul %d are %d produse\n", i + 1, (*p).stocMagazine[i]);
	printf("\n");
}
int stocTotal(Produs *p) {
	int sum = 0;
	for (int i = 0; i < (*p).nrmagazine; i++) {
		sum += (*p).stocMagazine[i];
	}
	return sum;
}
Produs * citireFProdus(FILE *f) {
	Produs *p = (Produs*)malloc(sizeof(Produs));
	char temp[20];
	fscanf(f, "%d", &p->id);
	fscanf(f, "%f", &p->pret);
	fscanf(f, "%s", temp);
	p->denumire = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	strcpy(p->denumire, temp);
	fscanf(f, "%d", &p->nrmagazine);
	p->stocMagazine = (int*)malloc(sizeof(int)*p->nrmagazine);
	for (int i = 0; i < p->nrmagazine; i++) {
		fscanf(f, "%d", &p->stocMagazine[i]);
	}
	return p;
}


//Lucru cu lista simpla
struct nodListaSimpla {
	Produs * p;
	nodListaSimpla *next;
};
nodListaSimpla* creareNodLS(Produs *p) {
	nodListaSimpla *nou = (nodListaSimpla*)malloc(sizeof(nodListaSimpla));
	nou->p = p;
	nou->next = 0;
	return nou;
}
nodListaSimpla* inserareInceput(nodListaSimpla * list, Produs *p) {
	if (!list) {
		list = creareNodLS(p);
		return list;
	}
	else {
		nodListaSimpla *nou = creareNodLS(p);
		nou->next = list;
		return nou;
	}
}
nodListaSimpla* inserareSfarsit(nodListaSimpla* list, Produs *p) {
	if (!list) {
		list = creareNodLS(p);
		return list;
	}
	else {
		nodListaSimpla * nou = creareNodLS(p);
		nodListaSimpla * aux = list;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
		return list;
	}
}
void afisareListaSimpla(nodListaSimpla *list) {
	nodListaSimpla * aux = list;
	if (aux) {
		while (aux) {
			afisareProdus(aux->p);
			aux = aux->next;
		}
	}
	else printf("Lista este goala\n");
}
nodListaSimpla* inserareSortata(nodListaSimpla * list, Produs * p) {
	if (!list) {
		nodListaSimpla * nou = creareNodLS(p);
		nou->next = nou;
		return nou;
	}
	else {
		nodListaSimpla * nou = creareNodLS(p);
		nodListaSimpla * aux = list;
		while (aux && (strcmp(nou->p->denumire, aux->p->denumire) > 0))
			aux = aux->next;
		nou->next = aux->next;
		aux->next = nou;
		return list;
	}
}
void afisareListaCirculara(nodListaSimpla * list) {
	nodListaSimpla * aux = list->next;
	afisareProdus(list->p);
	while (aux != list) {
		afisareProdus(aux->p);
		aux = aux->next;
	}
}
nodListaSimpla* stergereProdus(nodListaSimpla *list, int id) {
	nodListaSimpla * aux = list;
	if (list->p->id == id) {
		nodListaSimpla *aux1 = list;
		list = list->next;
		free(aux1->p->denumire);
		free(aux1->p->stocMagazine);
		free(aux1->p);
		return list;
	}
	while (aux->next && aux->next->p->id != id)
		aux = aux->next;
	nodListaSimpla *temp = aux->next;
	aux->next = temp->next;
	free(temp->p->denumire);
	free(temp->p->stocMagazine);
	free(temp->p);
	return list;

}
nodListaSimpla* stergereTotala(nodListaSimpla *list) {
	while (list) {
		nodListaSimpla * aux = list;
		list = list->next;
		free(aux->p->denumire);
		free(aux->p->stocMagazine);
		free(aux);
	}
	return list;
}
int* raportStoc(nodListaSimpla *list) {
	int j = 0;
	nodListaSimpla *aux = list;
	while (aux)
	{
		j++;
		aux = aux->next;
	}
	int * vect = (int*)malloc(sizeof(int)*j);
	aux = list;
	int i = 0;
	while (aux) {
		vect[i] = stocTotal(aux->p);
		i++;
		aux = aux->next;
	}
	return vect;
}

//Lucru cu lista dubla
struct NodListaDubla {
	Produs * p;
	NodListaDubla *prev;
	NodListaDubla *next;
};
struct ListaDB {
	NodListaDubla * inceput;
	NodListaDubla * sfarsit;
};
NodListaDubla* creareNodLD(Produs *p) {
	NodListaDubla *nou = (NodListaDubla*)malloc(sizeof(NodListaDubla));
	nou->p = p;
	nou->next = 0;
	nou->prev = 0;
	return nou;
}
ListaDB inserareInceput(ListaDB list, Produs * p) {
	if (!list.inceput) {
		list.inceput = list.sfarsit = creareNodLD(p);
		return list;
	}
	else {
		NodListaDubla *nou = creareNodLD(p);
		nou->next = list.inceput;
		list.inceput->prev = nou;
		list.inceput = nou;
		return list;
	}
}
ListaDB inserareSfarsit(ListaDB list, Produs *p) {
	if (!list.inceput) {
		list.inceput = list.sfarsit = creareNodLD(p);
		return list;
	}
	else {
		NodListaDubla *nou = creareNodLD(p);
		list.sfarsit->next = nou;
		nou->prev = list.sfarsit;
		list.sfarsit = nou;
		return list;
	}
}
void afisareListaDB(ListaDB list) {
	if (list.inceput) {
		NodListaDubla *aux = list.inceput;
		while (aux) {
			afisareProdus(aux->p);
			aux = aux->next;
		}
	}
	else printf("Lista este goala\n");
}
ListaDB stergereProdus(ListaDB list, int id) {
	NodListaDubla *aux = list.inceput;
	while (aux != list.sfarsit) {
		if (aux->p->id == id) {
			if (aux == list.inceput)
			{
				NodListaDubla *temp = aux;
				list.inceput = aux->next;
				aux->next->prev = 0;
				free(temp->p->denumire);
				free(temp->p->stocMagazine);
				free(temp);
				return list;
			}
			else {
				NodListaDubla *temp = aux;
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;
				free(temp->p->denumire);
				free(temp->p->stocMagazine);
				free(temp);
				return list;
			}


		}
		aux = aux->next;
	}
	if (aux->p->id == id && aux == list.sfarsit) {
		NodListaDubla *temp = aux;
		list.sfarsit = aux->prev;
		list.sfarsit->next = 0;
		free(temp->p->denumire);
		free(temp->p->stocMagazine);
		free(temp);
		return list;
	}
	return list;
}
ListaDB stergereTotala(ListaDB list) {
	while (list.inceput) {
		NodListaDubla * aux = list.inceput;
		list.inceput = list.inceput->next;
		free(aux->p->denumire);
		free(aux->p->stocMagazine);
		free(aux);
	}
	list.inceput = list.sfarsit = 0;
	return list;

}
//ListaDB inserareSortata(ListaDB list, Produs * p) {
//	if (list.inceput == 0) {
//		NodListaDubla *nou = creareNodLD(p);
//		nou->next = nou;
//		nou->prev = nou;
//		list.inceput = nou;
//		list.sfarsit = nou;
//	}
//	else {
//		NodListaDubla *nou = creareNodLD(p);
//		NodListaDubla *aux = list.inceput;
//		while (aux !=list.sfarsit && strcmp(nou->p->denumire, aux->p->denumire) >= 0)
//			aux = aux->next;
//		if (aux == list.sfarsit) {
//			nou->next = aux->next;
//			nou->prev = aux;
//			aux->next->prev = nou;
//			aux->next = nou;
//			list.sfarsit = nou;
//			return list;
//		}
//		else if (aux = list.inceput) {
//			nou->next = aux;
//			nou->prev = aux->prev;
//			aux->prev->next = nou;
//			aux->prev = nou;
//			list.inceput = nou;
//			return list;
//		}
//		else {
//			nou->next = aux->next;
//			nou->prev = aux;
//			aux->next->prev = nou;
//			aux->next = nou;
//		}
//		return list;
//		/*NodListaDubla *nou = creareNodLD(p);
//		NodListaDubla *aux = list.inceput->next;
//		while (aux != list.inceput && strcmp(nou->p->denumire, aux->p->denumire) < 0)
//			aux = aux->next;
//		if (aux == list.inceput) {
//			nou->next = list.inceput;
//			nou->prev = list.inceput->prev;
//			list.inceput->prev->next = nou;
//			list.inceput->prev = nou;
//			list.inceput = nou;
//			return list;
//			
//		}
//		else {
//			nou->next = aux->next;
//			nou->prev = aux;
//			aux->next->prev = nou;
//			aux->next = nou;
//		}
//		return list;*/
//
//	}
//}

// Lucru cu Stiva

void push(nodListaSimpla* *stack, Produs * p) {
	*stack = inserareInceput(*stack,p);
}
Produs* pop(nodListaSimpla* *stack) {
	nodListaSimpla * aux = *stack;
	*stack = (*stack)->next;
	Produs *nou = (Produs*)malloc(sizeof(Produs));
	nou->id = aux->p->id;
	nou->denumire = (char*)malloc((strlen(aux->p->denumire) + 1) * sizeof(char));
	strcpy(nou->denumire, aux->p->denumire);
	nou->pret = aux->p->pret;
	nou->nrmagazine = aux->p->nrmagazine;
	nou->stocMagazine = (int*)malloc(sizeof(int)*nou->nrmagazine);
	for (int i = 0; i < nou->nrmagazine; i++)
		nou->stocMagazine[i] = aux->p->stocMagazine[i];
	free(aux->p->denumire);
	free(aux->p->stocMagazine);
	free(aux);
	return nou;
}


int main()
{	
	//Lucru cu produsul
	/*Produs p = creareConsola();
	Produs p;
	creareConsola1(&p);
	afisareProdus(&p);
	printf("Stoc total %d\n", stocTotal(p));*/

	//Lucru cu lista simpla 

	//FILE *f = fopen("fisier.txt", "r");
	//if (f) {
	//	nodListaSimpla * list = (nodListaSimpla*)malloc(sizeof(nodListaSimpla));
	//	list = 0;
	//	for (int i = 0; i < 4; i++) {
	//		//list = inserareInceput(list, citireFProdus(f));
	//		list = inserareSfarsit(list, citireFProdus(f));
	//		//list = inserareSortata(list, citireFProdus(f));
	//	}
	//	//afisareListaCirculara(list);
	//	afisareListaSimpla(list);
	//	//list = stergereProdus(list, 2);
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("Magazinul %d are %d produse\n", i+1, raportStoc(list)[i]);
	//	}
	//	list = stergereTotala(list);
	//	afisareListaSimpla(list);
	//	fclose(f);
	//}
	//else printf("Fisierul nu a fost deschis");
	
	
	//Lucru cu lista dubla

	
	//FILE * g = fopen("fisier.txt", "r");
	//if (g) {
	//	ListaDB lista;
	//	lista.inceput = 0;
	//	lista.sfarsit = 0;
	//	for (int i = 0; i < 4; i++) {
	//		//lista = inserareInceput(lista, citireFProdus(g));
	//		lista = inserareSfarsit(lista, citireFProdus(g));
	//	}
	//	afisareListaDB(lista);
	//	//lista = stergereProdus(lista,1);
	//	lista = stergereTotala(lista);
	//	afisareListaDB(lista);
	//	fclose(g);
	//}
	//else  printf("Fisierul nu a fost deschis");
	

	//Lucru cu stack
	
	/*FILE *f = fopen("fisier.txt", "r");
	if (f) {
		nodListaSimpla * stack = (nodListaSimpla*)malloc(sizeof(nodListaSimpla));
		stack = 0;
		for (int i = 0; i < 4; i++) {
			push(&stack, citireFProdus(f));
		}
		for (int i = 0; i < 4; i++) {
			afisareProdus(pop(&stack));
		}
	}*/
	return 0;
}

