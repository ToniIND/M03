#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


/*-------------------------------------------------------------*/
/*DEFINES                                                      */

#define CERT 0
#define FALS 1

char linies[50][200];

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*STRUCT                                                       */

struct usuaris {
	int numeroBillet;
	int dinersJugats;
	int idioma;
	int any;
} usuari1;											   

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana al usuari l'idioma que utilitzara                      */

void idiomes(){

	int idioma = FALS, i;
	char fitxer[10], linia[200];
	FILE * fi;
	
	printf("Menu d'idiomes\n\n"); 
	printf(" 0.- Catala\n");
	printf(" 1.- Castellano\n");
	printf(" 2.- English\n\n");
	do {
		printf("Selecciona l'idioma: ");
		scanf("%d", &usuari1.idioma); 
		snprintf(fitxer, 100, "text/%d.txt", usuari1.idioma);

		fi = fopen(fitxer, "r");
		if (fi == NULL) {
			printf("\nIdioma no disponible\n\n");
			idioma = FALS;
		} else {
			idioma = CERT;
			printf("\n");
		}
		
	} while (idioma == FALS);
	
	snprintf(fitxer, 100, "text/%d.txt", usuari1.idioma);
	fi = fopen(fitxer, "r");
	while (!feof(fi)) {
		fgets(linia, 200, fi);
		strcpy(linies[i++], linia);
	}
	
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void infoJugador(){

	printf("\n%s", linies[0]);
	do {
		scanf("%d", &usuari1.numeroBillet);
		if (usuari1.numeroBillet < 0 || usuari1.numeroBillet > 99999)
			printf("%s", linies[3]);
	} while (usuari1.numeroBillet < 0 || usuari1.numeroBillet > 99999);
	
	printf("%s", linies[1]);
	do {
		scanf("%d", &usuari1.dinersJugats);
		if (usuari1.dinersJugats < 0)
			printf("%s", linies[4]);
	} while (usuari1.dinersJugats < 0);
	
	printf("%s", linies[2]);
	do {
		scanf("  %d", &usuari1.any);
		if (usuari1.any <= 1812 || usuari1.any >= 2021) 
			printf("%s", linies[5]);
	} while (usuari1.any <= 1812 || usuari1.any >= 2021);
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void generarPremis(){
	
	int i, j, coincide, temp = 0, randomIndex = 0, premis[99999], nPremis = 1807;
    char nom[100];
    
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
	
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Colles                                               */

void compPremi() {
		
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Colles                                               */

void colles() {
		
}

/*-------------------------------------------------------------*/


