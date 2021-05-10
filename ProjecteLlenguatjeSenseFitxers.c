#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct usuaris {
	int numeroBillet;
	int dinersJugats;
	int idioma;
	int any;
};

int rand();

struct usuaris usuari1;

void infoJugador(){

	printf("Menu d'idiomes\n\n"); 
	printf(" 1.- Catala\n");
	printf(" 2.- Castellanom\n");
	printf(" 3.- English\n\n");
	do {
		printf("Selecciona l'idioma: ");
		scanf("%d", &usuari1.idioma); 
		
		switch (usuari1.idioma){
			
			case 1:
				printf("\n  -> ");
				printf("Indica el numero del decim a comprobar: ");
				scanf("%d", &usuari1.numeroBillet);
				printf("\n  -> ");
				printf("Indica l'import jugat: ");
				scanf("%d", &usuari1.dinersJugats);
				do {
					printf("\n  -> ");
					printf("Indica l'any que vols mirar: ");
					scanf("%d", &usuari1.any);
				} while (usuari1.any <= 1812 || usuari1.any >= 2021);
			break;
			
			case 2:
				printf("\n  -> ");
				printf("Indica el numero del decimo a comprobar ");
				scanf("%d", &usuari1.numeroBillet);
				printf("\n  -> ");
				printf("Indica el importe jugado: ");
				scanf("%d", &usuari1.dinersJugats);
				do {
					printf("\n  -> ");
					printf("Indica el año que quieres mirar: ");
					scanf("%d", &usuari1.any);
				} while (usuari1.any <= 1812 || usuari1.any >= 2021);
			break;
			
			case 3:
				printf("\n  -> ");
				printf("Indicate the tenth number you want to check: ");
				scanf("%d", &usuari1.numeroBillet);
				printf("\n  -> ");
				printf("Indicate the amount played: ");
				scanf("%d", &usuari1.dinersJugats);
				do {
					printf("\n  -> ");
					printf("Indicate the year you want to check: ");
					scanf("%d", &usuari1.any);
				} while (usuari1.any <= 1812 || usuari1.any >= 2021);
			break;
			
			default:
				printf("\nIndica un dels idiomes disponibles\n\n");
		}
	} while (usuari1.idioma != 1 && usuari1.idioma != 2 && usuari1.idioma != 3);
}
	
void generarPremis(){
	
	int i, j, coincide, temp = 0, randomIndex = 0, premis[99999], nPremis = 1807;
    char nom[100];
    FILE * fp;
    
    srand(time(NULL));
    
	//GENEREM L'ARRAY
		
	for (i = 0; i < nPremis; i++) {
		premis[i] = rand()%99999;
		coincide=0;
		for (j = 0 ; j < i && !coincide; j++) {
			if (premis[i] == premis[j]) {
				coincide=1;
				i--;
			}
		}
	}
	 
	// ALEATORITZEM L'ARRAY
		
	for (int i = 0; i < nPremis ; i++) {
		temp = premis[i];
		randomIndex = rand() % nPremis;
	 
		premis[i] = premis[randomIndex];
		premis[randomIndex] = temp;
			
	}
	snprintf(nom, 100, "%d.dat", usuari1.any);
	fp = fopen(nom,"w"); // obrim fitxer escriptura
	fwrite(premis, sizeof(int), nPremis, fp); // Escrivim al fitxer cada premi per oirdre
	fclose(fp);
		
	/*-----------------------------------------------------
	MOSTRAR INFORMACIO DELS FITXERS*/
		
	fp = fopen(nom, "r"); // Obrim fitxer de lectura
	for (i=0; i<nPremis; i++) {  
		fread(premis, sizeof(int), nPremis, fp); // Afegim       
		printf ("%05d\n", premis[i]);
	}
		
	fclose(fp);
	/*-----------------------------------------------------*/
}

	
int main (void) {
	
	infoJugador();	
	
	generarPremis();
	
	return 0;
}


