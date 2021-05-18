#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>



/*-------------------------------------------------------------*/
/*DEFINES                                                      */

#define CERT 1
#define FALS 0
#define PREU_DECIM 20
#define DECIM 10
#define NR_PREMIS_MENORS 1794
#define NR_PREMIS_MAJORS 13
#define N_PREMIS 1807
#define NOMBRE_NUMEROS 99999

/*IMPORTS DELS PREMIS*/

#define PRIMER_PREMI 4000000
#define SEGON_PREMI 1250000
#define TERCER_PREMI 500000
#define QUART_PREMI 200000
#define CINQUE_PREMI 60000
#define PREMI_MENOR 1000
#define APROXIMACIO1er 20000
#define APROXIMACIO2on 12500
#define APROXIMACIO3er 9600
#define REINTEGRAMENT 200
#define XIFRES_FINALS123 1000
#define CENTENES12344 1000

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*VARIABLES GLOBALS                                                      */

char linies[50][200], premis[10][200];

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




//--------------------------------------------------------------
//FUNCIO PER GENERAR UNA IMATGE INICIAL.

void imatgeInicial (void) {
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
	printf("||     *            *                       *             ||\n");
	printf("||             *       LOTERIA NADAL...         *         ||\n");
	printf("||  *            *                      *                 ||\n");
	printf("|| *             ...PER FERNANDO, ERIC I TONI  *          ||\n");
	printf("||             *      *            *               *      ||\n");
	printf("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
//--------------------------------------------------------------



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



//--------------------------------------------------------------
//FUNCIO PER MOSTRAR ELS NUMEROS PREMIATS

void mostrarPremiats () {
	int i, j=N_PREMIS/2, k, cont=0, mostrar=FALS;
	char nom_fitxer[20], linia[50];
	FILE *fp;
	
	do {
	    printf("  -> "); 
	    printf("Vols veure tots els numeros premiats? (1/SI - 0/NO): ");
        scanf("%d", &mostrar);
	} while (mostrar != 0 && mostrar != 1);
	
    if (mostrar == CERT) {
		
		snprintf(nom_fitxer, 100, "%d.dat", usuari1.any);
		fp = fopen(nom_fitxer, "r");
		while (!feof(fp)) {
			fgets(linia, 200, fp);
			strcpy(premis[i++], linia);
		}
		
    	printf("\n              %s\n", linies[10]);
    	printf("               ================================\n");
    	for (k = 0; k < N_PREMIS/2; k++) {
    	    printf("               || %05d       ||     %05d   ||\n", premis[k], premis[j]);
    	    j++;
    	    cont+=2;
    	}
    	printf("               || %05d       ||     %05d   ||\n", premis[N_PREMIS-2], premis[N_PREMIS-1]);
    	printf("               ================================\n");
    }
}
//--------------------------------------------------------------



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


