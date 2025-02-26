#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <conio.h> // getch();

#define MAX 999

int main()
{
	/*
		8. SWP

		Se da un sir de N biti (0 < N < 1 000). Acest sir trebuie sortat crescator folosind doar
	interschimbari ale pozitiilor. Sa se afiseze numarul minim de interschimbari necesare, precum si toate
	interschimbarile efectuate. Orice solutie minima e acceptata. Complexitate maxima O(N).
	
		Exemplu: 8
			     10101010 => 00001111 cu interschimbarile: 1-6, 3-8

	*/

	printf(" \n  Problema 8.SWP Proiect TP; Stan Alexandru Daniel; Seria B; Subgrupa 03.1; IS Anul I \n\n");

	FILE* f = fopen("swp.in", "r");
	if (f == NULL) {
		printf(" | ERROR | Nu s-a putut deschide/ citi fisierul \"swp.in\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut deschide/citi fisierul \"swp.in\"!\n\n");

	uint16_t N;
	uint8_t i = 0, sir_biti[MAX], nr_intersch = 0, contor_biti_0 = 0, contor_biti_1 = 0;
	char bit, sir_init_biti[MAX];
	fscanf(f,"%hu", &N);
	while (N <= 0 || N >= 1000){
		/* se verifica conditiile impuse de problema pentru N,
		   iar daca N este invalid, atunci se reciteste de la tastatura. */
		printf(" | ERROR | Reintroduceti valoarea lui N ( numar natural intre (0,1000) ): "); scanf("%hu", &N);
		printf("\n");
	}

	fscanf(f, "%s", &sir_init_biti);
	
	// afisare sirul de biti introdus initial pe ecran pentru debugging
	printf(" | DEBUG | Sirul de biti introdus initial este: ");
	for (int poz = 0; poz < N; poz++)
		printf("%c", sir_init_biti[poz]);
	printf("\n\n");

	while (i < N) { // pentru fiecare caracter
		if (sir_init_biti[i] == '0' || sir_init_biti[i] == '1'){
			if (sir_init_biti[i] == '0')
				contor_biti_0 += 1;
			else
				contor_biti_1 += 1;
			sir_biti[i] = sir_init_biti[i] - 48; // salvam bitii ca si numere in vectorul "sir_biti"
		}
		else{ // daca caracterul curent nu este 1 sau 0, atunci recitim bitul de la tastatura si il salvam iarasi ca si caracter
			printf(" | ERROR | Reintroduceti bitul de pe poz. %hhu:", i);
			getchar();
			scanf("%c", &bit);
			printf("\n");
			sir_init_biti[i] = bit;
		}
		i++;
	}
	fclose(f);

	// afisarea sirului de biti final pe ecran pentru debugging ( modificat daca a fost vreo interventie )
	printf(" | DEBUG | Sirul de biti modificat ( in caz in care avem si cifre diferite de 1 sau 0 ) este: ");
	for (int poz = 0; poz < N; poz++)
		printf("%c", sir_init_biti[poz]);
	printf("\n\n");

	FILE* g = fopen("swp.out", "w");
	if (g == NULL) {
		printf(" | ERROR | Nu s-a putut crea fisierul/ scrie in fisierul \"swp.out\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut crea fisierul/ scrie in fisierul \"swp.out\"!\n\n");

	// afisarea interschimbarilor
	printf(" | DEBUG | Toate interschimbarile efectuate sunt: ");

	i = 0;
	uint8_t nr_0 = 0;
	for (int poz = 0; poz <= N/2; poz++){ // mergem cu variabila "poz" pana la jumatate inclusiv 
		if (nr_0 == contor_biti_0)
			// Daca contorul curent de biti nuli este egal cu numarul total de biti nuli,
			// atunci ne oprim, deoarece s-au epuizat toti bitii nuli, si nu mai avem cum
			// sa interschimbam
			break;
		if (sir_biti[poz] == 0)  // daca bitul este 0, atunci in contorizam
			nr_0++;
		if (sir_biti[poz] == 1 && sir_biti[N - 1 - i] != 0){
			// Daca bitul "poz" este 1 si bitul "N - 1 - i" este diferit de 0 (tot 1),
			// atunci i devine i+1 ca sa mergem cu o pozitie in stanga si de a verifica
			// urmatorul bit de pe stanga
			i++;
			poz--;
		}
		else
			if (sir_biti[poz] == 1 && sir_biti[N - 1 - i] == 0){
				// Daca bitul "N - 1 - i" este 0, atunci in contorizam si pe el.
				// Daca bitul "poz" este 1 si bitul "N - 1 - i" este 0,
				// atunci printam interschimbarea si intershimbam
				nr_0++;
				fprintf(g, "%d %hu\n", poz + 1, N - i );
				printf(" %d - %hu ", poz + 1, N - i);
				nr_intersch++; 
				sir_biti[poz] = 0;
				sir_biti[N - 1 - i] = 1;
				i++;
			}
	}
	if (nr_intersch > 0){	
		printf(" \n\n | DEBUG | Numarul de interschimbari efectuate este %hhu\n\n", nr_intersch);
		fprintf(g, "%hhu\n", nr_intersch);
	}
	else
		if (nr_intersch == 0){ 
			printf("Nu au fost efectuate interschimbari.\n\n");
			fprintf(g,"Nu au fost efectuate interschimbari.\n\n");
		}


	fclose(g); 

	// afisarea sirului nou de biti pe ecran pentru debugging 
	printf(" | DEBUG | Sirul nou de biti este: ");
	for (int poz = 0; poz < N; poz++)
		printf("%hhu", sir_biti[poz]);
	printf("\n\n");

	system("pause"); // getch();
	return 0;

}