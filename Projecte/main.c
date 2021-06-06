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
int numPremis[1807];
int format;

/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
/*Funciones                                                      */
void comprovarPremiPetitColla();
void comprovarPremiColla();
void amics();

/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/
/*STRUCT                                                       */

struct usuaris {
	int nDecim;
	int pagat;
	int idioma;
	int any;
	int premi;
} usuari1;											   

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
	int premiTotal;
	int importTotal;
    char nomColla[LONGITUD];
} colla;

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
	char fitxer[10], ruta[50];
	FILE * fi;
	FILE * fp;

    fp = fopen("text/menuidioma.txt", "r");
    do {

        fgets(ruta, 60, fp);
        puts(ruta);

    }while(!feof (fp) ) ;
    fclose(fp);

	do {
		printf("\nSelecciona l'idioma: ");
		scanf("%d", &usuari1.idioma); 
		snprintf(fitxer, 100, "text/%d.txt", usuari1.idioma);

		fi = fopen(fitxer, "r");
		if (fi == NULL) {
			printf("\nIdioma no disponible\n\n");
			idioma = FALS;
		} else idioma = CERT;		
	} while (idioma == FALS);
	
	while (!feof(fi)) fgets(linies[i++], 200, fi);

	fclose(fi);
	
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void infoJugador(){
	int anyActual, mesActual, diaActual, error;
	printf("%s", linies[0]);
	do {
		scanf("%d", &usuari1.nDecim);
		if (usuari1.nDecim < 0 || usuari1.nDecim > 99999)
			printf("%s", linies[3]);
	} while (usuari1.nDecim < 0 || usuari1.nDecim > 99999);
	
	printf("%s", linies[1]);
	do {
		scanf("%d", &usuari1.pagat);
		if (usuari1.pagat < 0 || usuari1.pagat > 1720)
			printf("%s", linies[4]);
	} while (usuari1.pagat < 0 || usuari1.pagat > 1720);
	
	
	do{
            error=0;
            printf("%s", linies[2]); 
            scanf("%d", &usuari1.any);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            anyActual= tm.tm_year + 1900;
            mesActual= tm.tm_mon + 1;
            diaActual= tm.tm_mday;

            if((usuari1.any==anyActual && mesActual==12 && diaActual>=22) || (usuari1.any>1812 && usuari1.any<anyActual)){
                error=1;
            }
            else{
                printf("%s", linies[35]);

            }
        }while(!error);
	
}

/*-------------------------------------------------------------*/



/*-------------------------------------------------------------*/
/*FUNCIO: Demana l'informació de l'usuari                      */

void generarPremis(){
	
	int i, j, coincide, temp = 0, randomIndex = 0, mostrar = FALS;
    char nom[100];
    FILE *fp;
    
    if(format==0)
		snprintf(nom, 100, "%d.dat", usuari1.any);
	else
		snprintf(nom, 100, "%d.dat", colla.any);
    
	if( access( nom, F_OK ) == -1) {
    
		srand(time(NULL));
		
		//GENEREM L'ARRAY
			
		for (i = 0; i < N_PREMIS; i++) {
			numPremis[i] = rand()%99999;
			coincide=0;
			for (j = 0 ; j < i && !coincide; j++) {
				if (numPremis[i] == numPremis[j]) {
					coincide=1;
					i--;
				}
			}
		}
		 
		// ALEATORITZEM L'ARRAY
			
		for (int i = 0; i < N_PREMIS ; i++) {
			temp = numPremis[i];
			randomIndex = rand() % N_PREMIS;
		 
			numPremis[i] = numPremis[randomIndex];
			numPremis[randomIndex] = temp;
				
		}
		
		fp = fopen(nom,"wb"); // obrim fitxer escriptura
		fwrite(numPremis, sizeof(int), N_PREMIS, fp); // Escrivim al fitxer cada premi per ordre
		fclose(fp);
		
    } else {	//CARGA LA INFORMACIO DEL FITXER
		
		fp = fopen(nom, "rb"); // Obrim fitxer de lectura
		fread(numPremis, sizeof(int), N_PREMIS, fp); 
		fclose(fp);
	}
	
	//MOSTRA O NO ELS NUMEROS PREAMIATS
	
	do {
	    printf("%s", linies[7]);
        scanf("%d", &mostrar);
	} while (mostrar != 0 && mostrar != 1);
	
    if (mostrar == CERT) {
		
		printf ("\n\n     %s\n", linies[8]);
		for (i=0; i<N_PREMIS; i++) {    
			printf ("%05d    ", numPremis[i]);
		}
    }
    
}

/*-------------------------------------------------------------*/



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR SI ÉS PREMI GRAN.

void comprovarPremi() {
	int i, posicioPremi, premiat=FALS;
    for (i = 0; i < 1807 && premiat == FALS; i++) {
    	if(numPremis[i] == usuari1.nDecim){
    		posicioPremi=i;
    		premiat=CERT;
    	}

    }
    if (premiat == CERT) {
    	switch(posicioPremi)
    	{
    		case 0:
    	   
				usuari1.premi=(PRIMER_PREMI/DECIM)*usuari1.pagat;
				printf("\n\n%s %d\n", linies[9], usuari1.premi);
 
    			break;
    		case 1:
    		
    			usuari1.premi=(SEGON_PREMI/DECIM)*usuari1.pagat;
     			printf("\n\n%s %d\n", linies[10], usuari1.premi);
    			
    			break;
    		case 2:
    		
    			usuari1.premi=(TERCER_PREMI/DECIM)*usuari1.pagat;
    			printf("\n\n%s %d\n", linies[11], usuari1.premi);
    			
    			break;
    		case 3 ... 4:
    		
        		usuari1.premi=(QUART_PREMI/DECIM)*usuari1.pagat;
    			printf("\n\n%s %d\n", linies[12], usuari1.premi);
    			
    			break;
    		case 5 ... 13:
    		
    			usuari1.premi=(CINQUE_PREMI/DECIM)*usuari1.pagat;
    			printf("\n\n%s %d\n", linies[13], usuari1.premi);
    			
    			break;
    		case 14 ... 1807:
    		
    			usuari1.premi=(PREMI_MENOR/DECIM)*usuari1.pagat;
    			printf("\n\n%s %d\n", linies[14], usuari1.premi);
    			
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
	
	usuari1.premi=0;
	
	//APROXIMACIONS (1r, 2n, 3r)
        if (usuari1.nDecim==numPremis[0]+1 || usuari1.nDecim==numPremis[0]-1) {
			printf("\n\n%s\n", linies[16]);
			usuari1.premi = (APROXIMACIO1er/DECIM)*usuari1.pagat; 
        }
        if (usuari1.nDecim==numPremis[1]+1 || usuari1.nDecim==numPremis[1]-1) {
			printf("\n\n%s\n", linies[17]);
            usuari1.premi += (APROXIMACIO2on/DECIM)*usuari1.pagat; 
        }
        if (usuari1.nDecim==numPremis[2]+1 || usuari1.nDecim==numPremis[2]-1) {
			printf("\n\n%s\n", linies[18]);
            usuari1.premi += (APROXIMACIO3er/DECIM)*usuari1.pagat;
        }
        
        //DUES ULTIMES XIFRES (1r, 2n, 3r)
        
        if (numPremis[0]%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[19]);
            usuari1.premi += (XIFRES_FINALS123/DECIM)*usuari1.pagat;
        }
        if (numPremis[1]%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[20]);
            usuari1.premi += (XIFRES_FINALS123/DECIM)*usuari1.pagat;      
        }
        if (numPremis[2]%100 == usuari1.nDecim%100) {
			printf("\n\n%s\n", linies[21]);
            usuari1.premi += (XIFRES_FINALS123/DECIM)*usuari1.pagat;
        }
        
        //CENTENES (1r, 2n, 3r, 4t, 4t)
        
        if (numPremis[0]/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[22]);
            usuari1.premi += (CENTENES12344/DECIM)*usuari1.pagat;
        }
        if (numPremis[1]/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[23]);
            usuari1.premi += (CENTENES12344/DECIM)*usuari1.pagat;
        }
        if (numPremis[2]/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[24]);
            usuari1.premi += (CENTENES12344/DECIM)*usuari1.pagat;            
        }
        if (numPremis[3]/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[25]);
            usuari1.premi += (CENTENES12344/DECIM)*usuari1.pagat;
        }
        if (numPremis[4]/100 == usuari1.nDecim/100) {
			printf("\n\n%s\n", linies[25]);
            usuari1.premi += (CENTENES12344/DECIM)*usuari1.pagat;
        }
        
        //REINTEGRAMENT (1r)
        
        if (numPremis[0]%10 == usuari1.nDecim%10) {
			printf("\n\n%s\n", linies[26]);
			usuari1.premi += (REINTEGRAMENT/DECIM)*usuari1.pagat;
        }
        
        //TOTAL
        
        if (usuari1.premi != 0) {
			printf("%d\n", usuari1.premi);
        } else {
            printf("%s\n", linies[27]);
        }
        
}
//--------------------------------------------------------------

/*-------------------------------------------------------------*/
/*FUNCIONS: amics                                               */

void amics() {

    char nom[400];
    int i, anyActual, mesActual, diaActual, error;
    FILE *fp;

    printf("%s", linies[31]);
    scanf("%s", colla.nomColla);

    snprintf(nom, 400, "%s.dat", colla.nomColla);

    if( access( nom, F_OK ) == -1) {

        do {
            printf("%s", linies[32]);
            scanf("%d", &colla.numPersones);
            if (colla.numPersones < 2) printf("%s\n", linies[33]);
        } while (colla.numPersones < 2);

        do{
            error=0;
            printf("%s", linies[34]); scanf("%d", &colla.any);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            anyActual= tm.tm_year + 1900;
            mesActual= tm.tm_mon + 1;
            diaActual= tm.tm_mday;

            if((colla.any==anyActual && mesActual==12 && diaActual>=22) || (colla.any>1812 && colla.any<anyActual)){
                error=1;
            }
            else{
                printf("%s", linies[35]);

            }
        }while(!error); 

		colla.importTotal=0;

        for (i = 0; i < colla.numPersones; i++) {
            printf("%s", linies[36]);
            scanf("%s", colla.persona[i].nom);
            printf("%s", linies[37]);
            do {
                scanf("%d", &colla.persona[i].nDecim);
				if (colla.persona[i].nDecim < 0 || colla.persona[i].nDecim > 99999)
					printf("%s", linies[3]);
            } while (colla.persona[i].nDecim < 0 || colla.persona[i].nDecim > 99999);
            printf("%s", linies[38]);
            do {
                scanf("%d", &colla.persona[i].import);
				if (colla.persona[i].import < 5 || colla.persona[i].import > 60 || colla.persona[i].import%5!=0)
					printf("%s", linies[4]);
            } while (colla.persona[i].import < 5 || colla.persona[i].import > 60 || colla.persona[i].import%5!=0);
            
            colla.importTotal += colla.persona[i].import;
            colla.persona[i].premi = 0;
        }
        colla.premiTotal=0;

        fp = fopen(nom,"wb");
        fwrite(&colla, sizeof(struct colles), 1, fp);
        fclose(fp);

    } else {
        fp = fopen(nom,"r+b");
        fread(&colla, sizeof(struct colles), 1, fp);
        fclose(fp);
	}
    
    generarPremis(); //Generem el premis o els carguem si l'any ja existeix
    
	for (i = 0; i < colla.numPersones; i++) {
		comprovarPremiColla(i);
		if (colla.persona[i].premi == 0) 
			comprovarPremiPetitColla(i);
		colla.premiTotal += colla.persona[i].premi;
	}
        
    printf("\n     +=======================================+\n");
    printf("     |  ANY  |  MEMBRES  |  DINERS  |  PREMI |\n");
    printf("     +---------------------------------------+\n");
    printf("     |   %d|        %d |   %d      | %d      |\n", colla.any, colla.numPersones, colla.importTotal, colla.premiTotal);
    printf("     +=======================================+\n");
    printf("     +=======================================+\n");
    printf("     |  AMIC |  NUMERO   |  DINERS  |  PREMI |\n");
    for (int i = 0; i < colla.numPersones; i++) {
        printf("     |%s       |  %05d        |   %d      |  %d     |\n", colla.persona[i].nom, colla.persona[i].nDecim, colla.persona[i].import, colla.persona[i].premi);
    }
    printf("     +=======================================+\n");
    }

/*-------------------------------------------------------------*/

void comprovarPremiColla(int amic) {
	int i, posicioPremi, premiat=FALS;
	for (i = 0; i < 1807 && premiat == FALS; i++) {
		if(numPremis[i] == colla.persona[amic].nDecim){
			posicioPremi=i;
			premiat=CERT;
		}
	}

    if (premiat == CERT) {
    	switch(posicioPremi)
    	{
    		case 0:
    		
				colla.persona[amic].premi= (PRIMER_PREMI/DECIM)/(PREU_DECIM/colla.persona[amic].import);
				printf("\n\n%s %d\n", linies[9], colla.persona[amic].premi);
 
    			break;
    		case 1:
    		
    			colla.persona[amic].premi= (SEGON_PREMI/DECIM)/(PREU_DECIM/colla.persona[amic].import);
    			printf("\n\n%s %d\n", linies[10], colla.persona[amic].premi);
    			
    			break;
    		case 2:
    		
    			colla.persona[amic].premi= (TERCER_PREMI/DECIM)/(PREU_DECIM/colla.persona[amic].import);
    			printf("\n\n%s %d\n", linies[11], colla.persona[amic].premi);
    			
    			break;
    		case 3 ... 4:
    		
        		colla.persona[amic].premi= (QUART_PREMI/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        		printf("\n\n%s %d\n", linies[12], colla.persona[amic].premi);
    			
    			break;
    		case 5 ... 13:
    		
				colla.persona[amic].premi= (CINQUE_PREMI/DECIM)/(PREU_DECIM/colla.persona[amic].import);
    			printf("\n\n%s %d\n", linies[13], colla.persona[amic].premi);
    			
    			break;
    		case 14 ... 1807:
    		
				colla.persona[amic].premi= (PREMI_MENOR/DECIM)/(PREU_DECIM/colla.persona[amic].import);
    			printf("\n\n%s %d\n", linies[14], colla.persona[amic].premi);
    			
    			break;
    	}
    } else {
    	printf("\n\n%s\n", linies[15]);
	}
}
//--------------------------------------------------------------

//--------------------------------------------------------------
//FUNCIO PER COMPROVAR ELL PREMIS PETITS

void comprovarPremiPetitColla (int amic) {
	
	//APROXIMACIONS (1r, 2n, 3r)
        if (colla.persona[amic].nDecim==numPremis[0]+1 || colla.persona[amic].nDecim==numPremis[0]-1) {
			colla.persona[amic].premi = (APROXIMACIO1er/DECIM)/(PREU_DECIM/colla.persona[amic].import);		
        }
        if (colla.persona[amic].nDecim==numPremis[1]+1 || colla.persona[amic].nDecim==numPremis[1]-1) {
            colla.persona[amic].premi += (APROXIMACIO2on/DECIM)/(PREU_DECIM/colla.persona[amic].import); 
        }
        if (colla.persona[amic].nDecim==numPremis[2]+1 || colla.persona[amic].nDecim==numPremis[2]-1) {
            colla.persona[amic].premi += (APROXIMACIO3er/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        
        //DUES ULTIMES XIFRES (1r, 2n, 3r)
        
        if (numPremis[0]%100 == colla.persona[amic].nDecim%100) {
            colla.persona[amic].premi += (XIFRES_FINALS123/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        if (numPremis[1]%100 == colla.persona[amic].nDecim%100) {
			colla.persona[amic].premi += (XIFRES_FINALS123/DECIM)/(PREU_DECIM/colla.persona[amic].import); 
        }
        if (numPremis[2]%100 == colla.persona[amic].nDecim%100) {
			colla.persona[amic].premi += (XIFRES_FINALS123/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        
        //CENTENES (1r, 2n, 3r, 4t, 4t)
        
        if (numPremis[0]/100 == colla.persona[amic].nDecim/100) {
			colla.persona[amic].premi += (CENTENES12344/DECIM)/(PREU_DECIM/colla.persona[amic].import); 
        }
        if (numPremis[1]/100 == colla.persona[amic].nDecim/100) {
			colla.persona[amic].premi += (CENTENES12344/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        if (numPremis[2]/100 == colla.persona[amic].nDecim/100) {
            colla.persona[amic].premi += (CENTENES12344/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        if (numPremis[3]/100 == colla.persona[amic].nDecim/100) {
            colla.persona[amic].premi += (CENTENES12344/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        if (numPremis[4]/100 == colla.persona[amic].nDecim/100) {
			colla.persona[amic].premi += (CENTENES12344/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }
        
        //REINTEGRAMENT (1r)
        
        if (numPremis[0]%10 == colla.persona[amic].nDecim%10) {
            colla.persona[amic].premi += (REINTEGRAMENT/DECIM)/(PREU_DECIM/colla.persona[amic].import);
        }     
        
}
//--------------------------------------------------------------


/*-------------------------------------------------------------*/
/*FUNCIO: Main del programa                                    */

int main (void) {
	
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
			amics();
		}
	} while (format != 0 && format != 1);
	
	return 0;
}

/*-------------------------------------------------------------*/

//14409    01199    20014    01990    25189    25037    06576    20174    03616    13887    16191    19578    12476    19950
