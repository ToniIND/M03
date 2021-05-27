#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>



/*-------------------------------------------------------------*/
/*DEFINES                                                      */

#define CERT 0
#define FALS 1
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
#define LONGITUD 200
/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*VARIABLES GLOBALS                                                      */

char linies[50][200];
int premis[1807];

/*-------------------------------------------------------------*/

void comprovarPremiColla();
void comprovarPremiPetitColla();
void generarPremiColla();

/*-------------------------------------------------------------*/
/*STRUCT                                                       */

struct usuaris {
	int nDecim;
	int pagat;
	int idioma;
	int any;
	int premi;
} usuari1;											   

struct premis {
	int nDecim;
	int cuantitat;
} p[13];


struct persones
{
    char nom[LONGITUD];
    int nDecim;
    int import;
	int premi;
};

struct colles
{
    struct persones persona[LONGITUD];
    int any;
    int numPersones;
	int importTotal;
    char nomColla[LONGITUD];
}colla;

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

	int idioma = FALS, i=0;
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
	
	while (!feof(fi)) {
		fgets(linia, 200, fi);
		strcpy(linies[i++], linia);
	}
	fclose(fi);
	
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void infoJugador(){
	int nBillet;
	printf("\n%s", linies[0]);
	do {
		scanf("%d", &nBillet);
		if (nBillet < 0 || nBillet > 99999)
			printf("%s", linies[3]);
		else 
			usuari1.nDecim = nBillet;
	} while (nBillet < 0 || nBillet > 99999);
	
	printf("%s", linies[1]);
	do {
		scanf("%d", &usuari1.pagat);
		if (usuari1.pagat < 0)
			printf("%s", linies[4]);
	} while (usuari1.pagat < 0);
	
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
	
	int i, j, coincide, temp = 0, randomIndex = 0, mostrar = FALS;
    char nom[100];
    FILE *fp;
    
    srand(time(NULL));
    
	//GENEREM L'ARRAY
		
	for (i = 0; i < N_PREMIS; i++) {
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
		
	for (int i = 0; i < N_PREMIS ; i++) {
		temp = premis[i];
		randomIndex = rand() % N_PREMIS;
	 
		premis[i] = premis[randomIndex];
		premis[randomIndex] = temp;
			
	}
	
	snprintf(nom, 100, "%d.dat", usuari1.any);
	
	if( access( nom, F_OK ) == -1) {
		fp = fopen(nom,"wb"); // obrim fitxer escriptura
		fwrite(premis, sizeof(int), N_PREMIS, fp); // Escrivim al fitxer cada premi per oirdre
		fclose(fp);
    }
	


	/*-----------------------------------------------------
	MOSTRAR INFORMACIO DELS FITXERS*/
	
	do {
	    printf("%s", linies[7]);
        scanf("%d", &mostrar);
	} while (mostrar != 0 && mostrar != 1);
	
    if (mostrar == CERT) {
		
		printf ("\n\n     %s\n", linies[8]);
		fp = fopen(nom, "rb"); // Obrim fitxer de lectura
		for (i=0; i<N_PREMIS; i++) {  
			fread(premis, sizeof(int), N_PREMIS, fp); // Afegim       
			printf ("%05d    ", premis[i]);
		}

		fclose(fp);

    }
    
    for (i = 0; i < 13; i++) {
		p[i].nDecim = premis[i];
	}

}

/*-------------------------------------------------------------*/



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR SI ÉS PREMI GRAN.

void comprovarPremi() {
	int j, posicioPremi, premiat = FALS;
    for (j = 0; j < 1807 && premiat == FALS; j++) {
    	if(premis[j] == usuari1.nDecim){
    		posicioPremi=j;
    		premiat=CERT;
    	}
    }
    
    if (premiat == CERT) {
    	switch(posicioPremi)
    	{
    		case 0:
    	   
    			printf("\n\n%s\n", linies[9]);
				usuari1.premi=usuari1.pagat*PRIMER_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = PRIMER_PREMI;
 
    			break;
    		case 1:
    		
    			printf("\n\n%s\n", linies[10]);
    			usuari1.premi=usuari1.pagat*SEGON_PREMI/DECIM/PREU_DECIM;
    			p[posicioPremi].cuantitat = SEGON_PREMI;
    			
    			break;
    		case 2:
    		
    			printf("\n\n%s\n", linies[11]);
    			usuari1.premi=usuari1.pagat*TERCER_PREMI/DECIM/PREU_DECIM;
    			p[posicioPremi].cuantitat = TERCER_PREMI;
    			
    			break;
    		case 3 ... 4:
    		
    			printf("\n\n%s\n", linies[12]);
        		usuari1.premi=usuari1.pagat*QUART_PREMI/DECIM/PREU_DECIM;
        		p[posicioPremi].cuantitat = QUART_PREMI;
    			
    			break;
    		case 5 ... 13:
    		
    			printf("\n\n%s\n", linies[13]);
    			usuari1.premi=usuari1.pagat*CINQUE_PREMI/DECIM/PREU_DECIM;
    			p[posicioPremi].cuantitat = PRIMER_PREMI;
    			
    			break;
    		case 14 ... 1807:
    		
    			printf("\n\n%s\n", linies[14]);
    			usuari1.premi=usuari1.pagat*PREMI_MENOR/DECIM/PREU_DECIM;
    			
    			break;
    	}
    } else {
    	printf("\n\n%s\n", linies[15]);
	}
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR ELL PREMIS PETITS

void comprovarPremiPetit () {
	
	//APROXIMACIONS (1r, 2n, 3r)
        if (usuari1.nDecim==p[0].nDecim+1 || usuari1.nDecim==p[0].nDecim-1) {
			
			printf("\n\n%s\n", linies[16]);
			usuari1.premi += usuari1.pagat*(APROXIMACIO1er/DECIM)/PREU_DECIM; 
			
        }
        if (usuari1.nDecim==p[1].nDecim+1 || usuari1.nDecim==p[1].nDecim-1) {
			printf("\n\n%s\n", linies[17]);
                usuari1.premi += usuari1.pagat*(APROXIMACIO2on/DECIM)/PREU_DECIM; 
        }
        if (usuari1.nDecim==p[2].nDecim+1 || usuari1.nDecim==p[2].nDecim-1) {
			printf("\n\n%s\n", linies[18]);
            usuari1.premi += usuari1.pagat*(APROXIMACIO3er/DECIM)/PREU_DECIM;
        }
        
        //DUES ULTIMES XIFRES (1r, 2n, 3r)
        
        if (p[0].nDecim%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[19]);

                usuari1.premi += usuari1.pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        if (p[1].nDecim%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[20]);

                usuari1.premi += usuari1.pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        if (p[2].nDecim%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[21]);

                usuari1.premi += usuari1.pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        
        //CENTENES (1r, 2n, 3r, 4t, 4t)
        
        if (p[0].nDecim/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[22]);

                usuari1.premi += usuari1.pagat*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[1].nDecim/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[23]);

                usuari1.premi += usuari1.pagat*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[2].nDecim/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[24]);

                usuari1.premi += usuari1.pagat*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[3].nDecim/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[25]);

                usuari1.premi += usuari1.pagat*(CENTENES12344/DECIM)/PREU_DECIM;
        }
        if (p[4].nDecim/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[25]);

                usuari1.premi += usuari1.pagat*(CENTENES12344/DECIM)/PREU_DECIM;
        }
        
        //REINTEGRAMENT (1r)
        
        if (p[0].nDecim%10 == usuari1.nDecim%10) {
			printf("\n\n%s\n", linies[26]);

                usuari1.premi += usuari1.pagat*(REINTEGRAMENT/DECIM)/PREU_DECIM;
        }
        
        if (usuari1.premi != 0) {
			printf("%d\n", usuari1.premi);
        } else {
            printf("%s\n", linies[27]);
        }
        
}
//--------------------------------------------------------------

/*-------------------------------------------------------------*/
/*FUNCIONS: Colles                                               */

void collesCrear() {

	int diners=0, premi=0, i;
	char nom[400];
	FILE *fp;
	
	printf("Nom de la colla: ");
	scanf("%s", colla.nomColla);
	
	snprintf(nom, 400, "%s.txt", colla.nomColla);
	
	if( access( nom, F_OK ) == -1) {
		
		do {
			printf("\n  -> ");
			printf("Quants amics sou? (2/20): ");
			scanf("%d", &colla.numPersones);
			printf("\n  -> ");
			printf("Quin any voleu mirar? (1812 - 2021): ");
			scanf("%d", &colla.any);
			if (colla.numPersones < 2 || colla.numPersones > 20) printf("\nHeu de ser entre 2 i 20 amics...\n");
		} while (colla.numPersones < 2 || colla.numPersones > 20);
	
		fp = fopen(nom,"wb"); // obrim fitxer escriptura
				
		for (i = 1; i <= colla.numPersones; i++) {
			printf("Indica el nom de l'amic: ");
			scanf("%s", colla.persona[i].nom);
			printf("Indica el decim de l'amic: ");
			scanf("%d", &colla.persona[i].nDecim);
			printf("Indica l'import jugat de l'amic: ");
			scanf("%d", &colla.persona[i].import);
		}
		
		fwrite(&colla, sizeof(struct colles), 1, fp);
		
		fclose(fp);
    } else {
		fp = fopen(nom,"rb");
		fread(&colla, sizeof(struct colles), 1, fp);
		printf("%d", colla.numPersones);
		fclose(fp);
	}
	
	generarPremiColla();
	
	for (int i = 0; i<=colla.numPersones; i++) {
		diners += colla.persona[i].import;
		comprovarPremiColla(i);
		if (usuari1.premi == 0) {
			comprovarPremiPetitColla(i);
		}
		premi += colla.persona[i].premi;

	}
	

	
    
    printf("\n     +=======================================+\n");
	printf("     |  ANY  |  MEMBRES  |  DINERS  |  PREMI |\n");
	printf("     +---------------------------------------+\n");
	printf("     |   %d|        %d |   %d      | %d      |\n", colla.any, colla.numPersones, diners, premi);
	printf("     +=======================================+\n");
	printf("     +=======================================+\n");
	printf("     |  AMIC |  NUMERO   |  DINERS  |  PREMI |\n");
	for (i = 0; i <= colla.numPersones; i++) {
		printf("     |%s       |  %d        |   %d      |  %d     |\n", colla.persona[i].nom, colla.persona[i].nDecim, colla.persona[i].import, colla.persona[i].premi);
	}
	printf("     +=======================================+\n");
}


/*-------------------------------------------------------------*/




//--------------------------------------------------------------
//FUNCIO PER COMPROVAR SI ÉS PREMI GRAN.

void generarPremiColla() {
	int i, j, coincide, temp = 0, randomIndex = 0;
    char nom[100];
    FILE *fp;
    
    srand(time(NULL));
    
	//GENEREM L'ARRAY
		
	for (i = 0; i < N_PREMIS; i++) {
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
		
	for (int i = 0; i < N_PREMIS ; i++) {
		temp = premis[i];
		randomIndex = rand() % N_PREMIS;
	 
		premis[i] = premis[randomIndex];
		premis[randomIndex] = temp;
			
	}
	
	snprintf(nom, 100, "%d.dat", colla.any);
	
	if( access( nom, F_OK ) == -1) {
		fp = fopen(nom,"wb"); // obrim fitxer escriptura
		fwrite(premis, sizeof(int), N_PREMIS, fp); // Escrivim al fitxer cada premi per oirdre
		fclose(fp);
    }
    
    
    printf ("\n\n     %s\n", linies[8]);
	fp = fopen(nom, "rb"); // Obrim fitxer de lectura
	for (i=0; i<N_PREMIS; i++) {  
		fread(premis, sizeof(int), N_PREMIS, fp); // Afegim       
	}

	fclose(fp);
    
        
    for (i = 0; i < 13; i++) {
		p[i].nDecim = premis[i];
	}
    
}
//--------------------------------------------------------------




//--------------------------------------------------------------
//FUNCIO PER COMPROVAR SI ÉS PREMI GRAN.

void comprovarPremiColla(int amic) {
	int i, posicioPremi, premiat = FALS;
	for (i = 0; i < 1807 && premiat == FALS; i++) {
		if(premis[i] == colla.persona[amic].nDecim){
			posicioPremi=i;
			premiat=CERT;
		}
	}
		
	if (premiat == CERT) {
		switch(posicioPremi)
		{
			case 0:
			   
				colla.persona[amic].premi=colla.persona[i].import*PRIMER_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = PRIMER_PREMI;
	 
				break;
			case 1:
				
				colla.persona[amic].premi=colla.persona[i].import*SEGON_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = SEGON_PREMI;
					
				break;
			case 2:
				
				colla.persona[amic].premi=colla.persona[i].import*TERCER_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = TERCER_PREMI;
					
				break;
			case 3 ... 4:
				
				colla.persona[amic].premi=colla.persona[i].import*QUART_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = QUART_PREMI;
					
				break;
			case 5 ... 13:
				
				colla.persona[amic].premi=colla.persona[i].import*CINQUE_PREMI/DECIM/PREU_DECIM;
				p[posicioPremi].cuantitat = PRIMER_PREMI;
					
				break;
			case 14 ... 1807:
				
				colla.persona[amic].premi=colla.persona[i].import*PREMI_MENOR/DECIM/PREU_DECIM;
					
				break;
		}
	} 
}

//--------------------------------------------------------------




//--------------------------------------------------------------
//FUNCIO PER COMPROVAR ELL PREMIS PETITS

void comprovarPremiPetitColla (int i) {
	
	//APROXIMACIONS (1r, 2n, 3r)
        if (colla.persona[i].nDecim==p[0].nDecim+1 || colla.persona[i].nDecim==p[0].nDecim-1) {
			usuari1.premi += colla.persona[i].import*(APROXIMACIO1er/DECIM)/PREU_DECIM; 
			
        }
        if (colla.persona[i].nDecim==p[1].nDecim+1 || colla.persona[i].nDecim==p[1].nDecim-1) {
                usuari1.premi += colla.persona[i].import*(APROXIMACIO2on/DECIM)/PREU_DECIM; 
        }
        if (colla.persona[i].nDecim==p[2].nDecim+1 || colla.persona[i].nDecim==p[2].nDecim-1) {
            usuari1.premi += colla.persona[i].import*(APROXIMACIO3er/DECIM)/PREU_DECIM;
        }
        
        //DUES ULTIMES XIFRES (1r, 2n, 3r)
        
        if (p[0].nDecim%100 == colla.persona[i].nDecim%100) {

                usuari1.premi += colla.persona[i].import*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        if (p[1].nDecim%100 == colla.persona[i].nDecim%100) {

                usuari1.premi += colla.persona[i].import*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        if (p[2].nDecim%100 == colla.persona[i].nDecim%100) {

                usuari1.premi += colla.persona[i].import*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
            
        }
        
        //CENTENES (1r, 2n, 3r, 4t, 4t)
        
        if (p[0].nDecim/100 == colla.persona[i].nDecim/100) {

                usuari1.premi += colla.persona[i].import*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[1].nDecim/100 == colla.persona[i].nDecim/100) {

                usuari1.premi += colla.persona[i].import*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[2].nDecim/100 == colla.persona[i].nDecim/100) {

                usuari1.premi += colla.persona[i].import*(CENTENES12344/DECIM)/PREU_DECIM;
            
        }
        if (p[3].nDecim/100 == colla.persona[i].nDecim/100) {

                usuari1.premi += colla.persona[i].import*(CENTENES12344/DECIM)/PREU_DECIM;
        }
        if (p[4].nDecim/100 == colla.persona[i].nDecim/100) {

                usuari1.premi += colla.persona[i].import*(CENTENES12344/DECIM)/PREU_DECIM;
        }
        
        //REINTEGRAMENT (1r)
        
        if (p[0].nDecim%10 == colla.persona[i].nDecim%10) {

                usuari1.premi += colla.persona[i].import*(REINTEGRAMENT/DECIM)/PREU_DECIM;
        }
        
        
}
//--------------------------------------------------------------




/*-------------------------------------------------------------*/
/*FUNCIO: Main del programa                                    */

int main (void) {
	
	int format;
	imatgeInicial();
	idiomes();
	
	printf("\n%s", linies[6]);
	do {
		scanf("%d", &format);
		if (format == 0) {
			infoJugador();	
			generarPremis();
			comprovarPremi();
			if (usuari1.premi == 0) {
				comprovarPremiPetit();
			}
		} else if (format == 1) {
			collesCrear();
		}
	} while (format != 0 && format != 1);
	
	return 0;
}

/*-------------------------------------------------------------*/
