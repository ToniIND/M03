#include <stdio.h>


/*-------------------------------------------------------------*/
/*DEFINES                                                      */

#define CERT 0
#define FALS 1

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
/*STRUCT                                                       */

void colles () {
		printf("\nColles");
}

/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/
/*FUNCIO: Demana al usuari l'idioma que utilitzara                      */

void idiomes(){

	int idioma = FALS;
	char fitxer[10];
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
}

/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void infoJugador(){

	int i=0;
	char fitxer[50], linia[200], linies[50][200];
	FILE * fi;
	
	snprintf(fitxer, 100, "text/%d.txt", usuari1.idioma);
	fi = fopen(fitxer, "r");
	while (!feof(fi)) {
		fgets (linia, 200, fi);
		strcpy (linies[i++], linia);
	}
	
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
