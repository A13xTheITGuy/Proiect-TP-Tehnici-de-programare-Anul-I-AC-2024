#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <conio.h> // getch();

int N, K; // numarul de valori din vector, respectv numarul de subsecvente
uint8_t index = 1; // indexul secventei de la final din vectorul Sir_de_numere cu pozitiile maximelor

void impartire_sir(unsigned* Sir_de_numere, int N, int poz, int start, int stop)
{

	if (start <= stop){ // atata timp cat nu am iesit din limitele subsirului
		unsigned max= 0;
		for (int i = start; i <= stop; i++) // determinam maximul din intervalul subsirului
			if (max <= Sir_de_numere[i] && poz != i) {
				max = Sir_de_numere[i];
				poz = i;
			}

		if (poz != -1) { // daca s-a gasit max 
			if (index <= K) {
				// introducem pozitiile maximelor in ultimele "K" pozitii ale sirului

				if (index == 1) { // daca este primul maxim, il bagam pe prima pozitie
					Sir_de_numere[N - 1 + (index)] = poz;
					index++;
				}
				else { // daca pozitia este mai mult de prima , dar mai mica decat a treia inclusiv
					
					uint8_t ind = 1; // index curent pentru determinare loc de introdus moul max

					/* selectam locul in care tebuie introdus noul max, mai exact inaintea primului element
					   mai mare ca acesta */
					while (poz > Sir_de_numere[N - 1 + (ind++)] && ind <= index);
					ind--;

					/* avand pozitia potrivita, acum "tragem" toata partea dreapta cu o pozitie in dreapta
					   si introducem maximul */
					for (int i = N - 1 + index; i > N - 1 + ind; i--)
						Sir_de_numere[i] = Sir_de_numere[i - 1];
					Sir_de_numere[N - 1 + ind] = poz;
					index++;
				}
			}
			else { // daca am iesit din vector, comparam urmatoarele maxime cu ultimele K valori din vector

				/* aflam pozitia minimului dintre cele K pozitii de la final, apoi daca min < max,
				   atunci il introducem pe max in loc de min in vector astfel incat ultimele K elemente din 
				   vector sa fie ordonate crescator */

				unsigned min = INT_MAX, poz_min = -1;

				for (int i = 1; i <= K; i++) { // determinam minimul impreuna cu pozitia lui "poz_min"
					if (min > Sir_de_numere[Sir_de_numere[N - 1 + i]]) {
						min = Sir_de_numere[Sir_de_numere[N - 1 + i]];
						poz_min = N - 1 + i;
					}
				}

				if (min < max && poz_min!=-1) { // daca min < max si am gasit un minim
					for (int i = poz_min; i < N + K - 1; i++) // scoatem minimul din vector
						Sir_de_numere[i] = Sir_de_numere[i + 1];			

					uint8_t ind = 1; // index curent pentru determinare loc de introdus moul max

					/* selectam locul in care trebuie introdus noul max, mai exact inaintea primului element
					   mai mare ca acesta */
					while (poz > Sir_de_numere[N - 1 + (ind++)] && ind < index);
					ind--;

					/* avand pozitia potrivita, acum "tragem" toata partea dreapta cu pozitie in dreapta
					   si introducem maximul */
					for (int i = N - 1 + K; i > N - 1 + ind; i--)
						Sir_de_numere[i] = Sir_de_numere[i - 1];
					Sir_de_numere[N - 1 + ind] = poz;
				}
			}
		}
		impartire_sir(Sir_de_numere, N, poz, start, poz - 1); // impartire sir in partea stanga lui "poz"
		impartire_sir(Sir_de_numere, N, poz, poz + 1, stop); // impartire sir in partea dreapta lui "poz"
	}
}

int main()
{
	/*
		27. KMX

		Se dau doua numere naturale N (0 <= N <= 10^5) si K (0 <= K <= 10^3) si un sir de N numere naturale
	mai mici decat 10^3. Sa se imparta sirul in exact K subsecvente astfel incat suma maximelor din
	subsecvente sa fie maxima. Afisati exact K linii reprezentand subsecventele. Daca exista mai multe
	solutii, se poate afisa oricare. Complexitate maxima O(N+K) memorie.

		Exe: 8 3
			 1 5 8 4 6 3 2 7

		=> Afisare:
					1 5 8
					4 6 3
					2 7
	*/

	printf(" \n  Problema 27. KMX Proiect TP; Stan Alexandru Daniel; Seria B; Subgrupa 03.1; IS Anul I \n\n");

	FILE* f = fopen("kmx.in", "r");
	if (f == NULL) {
		printf(" | ERROR | Nu s-a putut deschide/citi fisierul \"kmx.in\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut deschide/citi fisierul \"kmx.in\"!\n\n");

	uint32_t i = 0; // uint32_t = unsigned int
	fscanf(f, "%d", &N);
	while (N < 0 || N > 100000) {
		/* se verifica conditiile impuse de problema pentru N,
		   iar daca N este invalid, atunci se reciteste de la tastatura valoarea acestuia. */
		printf(" | ERROR | Reintroduceti valoarea lui N ( numar natural intre [0,100000] ): "); scanf("%d", &N);
		printf("\n");
	}

	fscanf(f, "%d", &K);
	while (K < 0 || K > 1000 || K > N) {
		/* se verifica conditiile impuse de problema pentru K,
		   iar daca K este invalid, atunci se reciteste de la tastatura valoarea acestuia. */
		printf(" | ERROR | Reintroduceti valoarea lui K ( numar natural intre [0,1000] si K > N ): "); scanf("%d", &K);
		printf("\n");
	}

	unsigned* Sir_de_numere = (unsigned*)calloc((N + K),  sizeof(unsigned)); // vectorul numerelor si la final cu pozitiile maximelor din fiecare subsir
	if (Sir_de_numere == NULL) {
		printf(" | ERROR | Nu s-a putut aloca memorie dinamica pentru vectorul \"Sir_de_numere\"! \n\n");
		exit(EXIT_FAILURE);
	}
	printf(" | INFO | S-a putut aloca memorie dinamica pentru vectorul \"Sir_de_numere\"! \n\n");

	for (int poz = 0; poz < N; poz++) { // luam fiecare numar
		int Elem;
		fscanf(f, "%d", &Elem);
		while (Elem < 0 || Elem >= 1000) {
			/* se verifica conditiile impuse de problema pentru element,
			   iar daca elementul este invalid, atunci se reciteste de la tastatura valoarea acestuia. */
			printf(" | ERROR | Reintroduceti elementul cu nr. %d ( initial: %d ) ( numar natural intre [0,1000] ): ", poz + 1, Elem); scanf("%d", &Elem);
			printf("\n");
		}
		Sir_de_numere[poz] = Elem; // se salveaza numarul
	}

	// afisarea elementelor din vector
	printf(" | DEBUG | Elementele din vector sunt: ");
	for (int poz = 0; poz < N; poz++)
		printf("%u ", Sir_de_numere[poz]);
	printf("\n\n");

	fclose(f);

	FILE* g = fopen("kmx.out", "w");
	if (g == NULL) {
		printf(" | ERROR | Nu s-a putut crea/ scrie in fisierul \"kmx.out\"!\n\n");
		exit(1);
	}
	printf(" | INFO | S-a putut crea/ scrie in fisierul \"kmx.out\"!\n\n");
	printf(" | DEBUG | Sirul impartit in exact K subsecvente astfel incat suma maximelor din subsecvente sa fie maxima este:\n");

	impartire_sir(Sir_de_numere,N,-1,0,N-1);
	index = 1;

	// afisare sir impartit
	printf(" ");
	for (int i = 0; i < N; i++){
		if (i != Sir_de_numere[N - 1 + (index)]){
			fprintf(g,"%u ", Sir_de_numere[i]);
			printf("%u ", Sir_de_numere[i]);
			if (i == N - 1){
				fprintf(g,"\n");
				printf("\n");
			}
		}
		else {
			fprintf(g, "%u ", Sir_de_numere[i]);
			printf("%u ", Sir_de_numere[i]);
			if (i >= N - 1 || index != K){
				fprintf(g,"\n");
				printf("\n");
				if (i != N - 1) {
					printf(" ");
				}
			}
			index++;
		}
	}

	// afisarea indicilor maximelor pe ecran pentru debugging
	printf("\n");
	printf(" | DEBUG | Indicii maximelor care au proprietatea ca suma lor sa dea maxima sunt: ");
	for (int i = N; i < N+K; i++)
		printf("%u ", Sir_de_numere[i]);
	printf("\n\n");

	// afisarea intregului vector pe ecran pentru debugging
	printf(" | DEBUG | Intregul vector in final este: ");
	for (int i = 0; i < N + K; i++)
		printf("%u ", Sir_de_numere[i]);
	printf("\n\n");

	fclose(g);
	free(Sir_de_numere); // Se dezaloca memoria alocata dinamic pentru sirul 'Sir_de_numere'
	system("pause"); // getch();
	return 0;
}