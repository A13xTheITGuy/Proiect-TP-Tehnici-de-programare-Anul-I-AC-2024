#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <conio.h> // getch();

#define MAX 10

unsigned sir_numere[MAX], subsiruri[MAX], pozitii[MAX], freq[MAX];
int ratia = -1;
uint8_t N, nr_subs;

void Print(uint8_t k, FILE* g) // printeaza subsirul in fisier
{
	for (int i = 0; i <= k; i++)
		fprintf(g,"%u ", subsiruri[i]);
	fprintf(g,"\n");
}

void Console_Print(int k) // printeaza subsirul pe ecran
{
	printf(" ");
	for (int i = 0; i <= k; i++)
		printf("%u ", subsiruri[i]);
	printf("\n");
}

uint8_t IsValid(uint8_t k) // Verifica daca sirul curent din stiva este valid
{		
	if (k > 0) {
		if (subsiruri[k - 1] > subsiruri[k])
			// ne asiguram ca avem un subsir crescator
			return 0;
		else
			if (subsiruri[k - 1] == subsiruri[k] && pozitii[k - 1] == pozitii[k])
				// ne asiguram ca nu luam doua elemente identice in calcul
				// ( egale numerele si pozitiile lor )
				return 0;
			else
				// calculam ratia ultimilor doi termeni
				ratia = subsiruri[k] - subsiruri[k - 1];
	}
	for (int i = 0; i < k; i++)
		if (pozitii[i] == pozitii[k])
			// asigura nerepetarea pozitiilor 
			return 0;
	for (int i = 1; i <= k; i++)
		if (subsiruri[i] - subsiruri[i - 1] != ratia)
			// asigura ca sirul nostru este o progresia aritmetica
			return 0;
	return 1;
}

void bkt(uint8_t k, FILE* g) // backtracking
{
	for (int i = 0; i < N; i++) {
		subsiruri[k] = sir_numere[i];
		pozitii[k] = i;
		if (IsValid(k)){
			if (k != 0){ // daca avem doar un singur element in subsir, atunci nu il afisam
				Print(k, g);
				Console_Print(k);
				nr_subs++; // contor numarare numar de subsiruri, in functie 
				           // de acesta se afiseaza mesajul corespunzator ( daca
				           // nu s-au afisat subsiruri, afiseaza mesaj ca nu
				           // exista subisruri )
			}
			bkt(k + 1, g); // apelarea functiei backtracking pentru urmatoarea pozitie
		}
	}
}

int main()
{
	/*
		21. PRA

		Se dau N numere naturale (0 < N <= 10). Sa se afiseze cate subsiruri crescatoare formate din
	cel putin doi termeni reprezinta o progresie aritmetica si care sunt acestea. Subsirurile pot fi afisate in
	orice ordine, cate un subsir pe o linie.

		Exe: 4
			 2 3 4 6

		=> 8 subsiruri cu subsirurile : (2 3) (2 3 4) (2 4) (2 4 6) (2 6) (3 4) (3 6) (4 6)

	*/

	printf(" \n  Problema 21.PRA Proiect TP; Stan Alexandru Daniel; Seria B; Subgrupa 03.1; IS Anul I \n\n");

	FILE* f = fopen("pra.in", "r"); // deschidere/ citire fisier "pra.in"
	if (f == NULL) {
		// daca nu s-a putut deschide/ citi fisierul "pra.in", atunci
		// afisare pe ecran eroare
		printf(" | ERROR | Nu s-a putut deschide fisierul \"pra.in\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut deschide/citi fisierul \"pra.in\"!\n\n");

	uint8_t i = 0, nr_intersch = 0;
	fscanf(f, "%hhu", &N); // citire numar de elemente din fisier
	while (N <= 0 || N > 10) {
		printf(" | ERROR | Reintroduceti valoarea lui N ( numar natural intre (0,11) ): "); scanf("%hhu", &N);
		printf("\n");
	}

	// citire elemente din fisier si numararea a fiecarui element de cate ori apare, adica frecventa fiecarui element
	for (int poz = 0; poz < N; poz++)
	{
		fscanf(f,"%u", &sir_numere[poz]);
		freq[sir_numere[poz]]++;
	}
		
	//afisare sir introdus in fisier
	printf(" | DEBUG | Sirul de numere introdus este: ");
	for (int poz = 0; poz < N; poz++)
		printf("%u ", sir_numere[poz]);
	printf("\n\n");

	fclose(f);

	FILE* g = fopen("pra.out", "w");
	if (g == NULL) {
		printf(" | ERROR | Nu s-a putut crea fisierul/ scrie in fisierul \"pra.out\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut crea fisierul/ scrie in fisierul \"pra.out\"!\n\n");
	printf(" | DEBUG | Toate subsirurile crescatoare formate din cel putin doi termeni reprezinta o progresie aritmetica sunt: ");
	
	printf("\n");
	bkt(0,g);

	// Daca numarul de subsiruri este peste 0, atunci se afiseaza pentru debugging
	// mesaj pe ecran a numarului de siruri, altfel se afiseaza mesajul ca nu
	// exista astfel de subsiruri.

	if (nr_subs > 0)
		printf(" \n\n | DEBUG | Numarul de subsiruri este %d\n\n", nr_subs);
	else
		if (nr_subs == 0)
			printf("Nu exista subsiruri cu conditiile impuse de problema.\n\n");
	fprintf(g, "%u\n", nr_subs);

	fclose(g);
	system("pause"); // getch();
	return 0;
}