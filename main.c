#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "dades.h"


/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

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
	
	// Obrim fitxer escriptura
	
	fp = fopen(nom,"w"); 
	fwrite(premis, sizeof(int), nPremis, fp);
	fclose(fp);
		
		
	// Obrim fitxer de lectura
	/*
	fp = fopen(nom, "r"); 
	for (i=0; i<nPremis; i++) {  
		fread(premis, sizeof(int), nPremis, fp);      
		printf ("%05d\n", premis[i]);
	}
		
	fclose(fp);
	*/
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Main del programa                                    */

int main (void) {
	
	int format;
	
	idiomes();
	
	printf("Vols jugar sol o amb colla? (0 - SOL / 1 - COLLA): ");
	do {
		scanf("%d", &format);
		if (format == 0) {
			infoJugador();	
			generarPremis();
		} else if (format == 1) {
			colles();
		}
	} while (format != 0 && format != 1);
	
	return 0;
}

/*-------------------------------------------------------------*/


