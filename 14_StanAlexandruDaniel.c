#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <conio.h> // getch();

#define MAX 100000

int N, K; // numarul de angajati, respectv puterea maxima

void sume_in_viramente(FILE* g, unsigned suma, int K) // se genereaza viramentele minime si se afiseaza
{
	for (int puteri = 0; puteri <= K && suma != 0; puteri++) {
		unsigned putere_10_0 = (unsigned)pow(10, puteri);
		unsigned putere_10_1 = (unsigned)pow(10, puteri + 1);
		while (suma % putere_10_1 >= putere_10_0) {
			printf("%d ", putere_10_0);
			fprintf(g, "%d ", putere_10_0);
			suma -= putere_10_0;
		}
	}
	printf("\n\n");
	fprintf(g, "\n");
}

int main()
{
	/*
		14. SAL

		La o firma angajatii sunt platiti pe parcursul a celei de-a cincea zi lucratoare. In decursul zilei
	vor fi platiti cei N angajati (0 < N <= 100 000) avand tranzactiile disponibile pentru a vira sumele in cont
	toate puterile lui 10 mai mici sau egale cu 10^K (0 <= K <= 9) . Sa se afiseze cum se pot oferi exact toate
	sumele de bani pentru toti angajatii, astfel incat numarul de viramente sa fie minim. Sumele necesare
	pentru virat S (S <= 10 000 000) vor fi date ca un vector de N numere naturale, iar numarul natural K
	se va citi imediat dupa N. Complexitate maxima O(N x K).

		Exe: 3 4
			 110 1000 1200

		=> Afisare:
					10 100
					1000
					100 100 1000
	*/

	printf(" \n  Problema 14. SAL Proiect TP; Stan Alexandru Daniel; Seria B; Subgrupa 03.1; IS Anul I \n\n");

	FILE* f = fopen("sal.in", "r");
	if (f == NULL) {
		printf(" | ERROR | Nu s-a putut deschide/citi fisierul \"sal.in\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut deschide/citi fisierul \"sal.in\"!\n\n");

	FILE* g = fopen("sal.out", "w");
	if (g == NULL) {
		printf(" | ERROR | Nu s-a putut crea fisierul/ scrie in fisierul \"sal.out\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut crea fisierul/ scrie in fisierul \"sal.out\"!\n\n");

	fscanf(f, "%d", &N);
	while (N <= 0 || N > 100000) {
		/* se verifica conditiile impuse de problema pentru N,
		   iar daca N este invalid, atunci se reciteste de la tastatura. */
		printf(" | ERROR | Reintroduceti valoarea lui N ( numar natural intre (0,100000] ): "); scanf("%d", &N);
		printf("\n");
	}
	fscanf(f, "%d", &K);
	while (K < 0 || K > 9) {
		/* se verifica conditiile impuse de problema pentru K,
		   iar daca K este invalid, atunci se reciteste de la tastatura. */
		printf(" | ERROR | Reintroduceti valoarea lui N ( numar natural intre [0,9] ): "); scanf("%d", &K);
		printf("\n");
	}

	for (int poz = 0; poz < N; poz++) { // luam fiecare suma de virat 
		int Suma_curenta;
		fscanf(f, "%d", &Suma_curenta);
		while (Suma_curenta < 0 || Suma_curenta > 10000000) {
			/* se verifica conditiile inpuse de problema pentru S (/ suma citita din fisier),
			   iar daca suma este invalida, atunci se reciteste suma de la tastatura. */
			printf(" | ERROR | Reintroduceti suma angajatului cu numarul %d ( initial: %d ) ( numar natural intre [0,10000000] ): ", poz + 1, Suma_curenta); scanf("%d", &Suma_curenta);
			printf("\n");
		}
		printf(" | DEBUG | Suma de virat cu numarul %u este: %u \n", poz + 1, Suma_curenta); // afisarea sumelor de virat
		printf("           Suma pentru angajatul cu numarul %d se poate oferi prin numarul de viramente minim in urmatorul fel: ", poz + 1);
		// afisarea sumelor prin umarul de viramente minim
		sume_in_viramente(g, Suma_curenta, K);
	}
	printf("\n");

	fclose(f);
	fclose(g);

	system("pause"); // getch();
	return 0;
}