/*
Per cada sèrie hi ha els premis següents:
- 1 primer premi de 4.000.000 €
    + 2 aproximacions de 20.000 € (números anterior i posterior al primer premi)
    + 9.999 reintegraments de 200 € a l’última xifra del primer premi
- 1 segon premi de 1.250.000 €
    + 2 aproximacions de 12.500 € (números anterior i posterior al segon premi)
- 1 tercer premi de 500.000 €
    + 2 aproximacions de 9.600 (números anterior i posterior al tercer premi)
      > 2.997 de 1.000 € a les dues xifres finals del primer, segon i tercer premis
- 2 quarts premis de 200.000 €
      > 495 de 1.000 € a les centenes del primer, segon, tercer i dos quarts premis
- 8 cinquès premis de 60.000 €
- 1.794 premis menors, de 1.000 € cada un
*/

/*
PALETA DE COLORS

    Negre 

    Vermell 

    Verd 

    Groc 

    Blau 

    Lila 

    Cyan 

    Blanc 
    
*/

/*LLIBRERIES*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

/*DEFINES*/

#define CERT 1
#define FALS 0
#define PREU_DECIM 20
#define DECIM 10
#define NR_PREMIS_MENORS 1794
#define NR_PREMIS_MAJORS 13
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



//--------------------------------------------------------------
//ESTRUCTURES

struct usuari {
    int nAmic;
    char nom[20];
    int nDecim;
    float pagat;
    float premi;
} usuari[20];

struct premis {
    int nDecim;
} p[5];



//--------------------------------------------------------------



//--------------------------------------------------------------
//DECLAREM LES FUNCIONS

void generarNumero(int premis[], int nPremis);

void imatgeInicial();

void mostrarPremiats(int premis[], int nPremis);

void amics(int premis[], int nPremis);

void inserirDades();

void comprovarPremi(int premis[], int nPremis, int nUsuari);
 
void comprovarPremiPetit(int nUsuari); 

void continuar(int * repetir);

double fmod(double x, double y);
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER GENERAR ELS NUMEROS QUE SERAN PREMIATS.

void generarNumero (int premis[], int nPremis) { //array premis[] donde estan los numeros premiados
  	int i, j, coincide, temp = 0, randomIndex = 0;
  	
  	srand(time(NULL));
  	
  	//GENEREM L'ARRAY
  	
  	for (i = 0; i < nPremis; i++) {
          premis[i] = rand()%NOMBRE_NUMEROS;
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
	
	p[0].nDecim = premis[0]; 
	p[1].nDecim = premis[1]; 
	p[2].nDecim = premis[2]; 
	p[3].nDecim = premis[3]; 
	p[4].nDecim = premis[4]; 
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER GENERAR UNA IMATGE INICIAL.

void imatgeInicial (void) {
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
	printf("||     *            *                       *             ||\n");
	printf("||             *    𝗟𝗢𝗧𝗘𝗥𝗜𝗔 𝗗𝗘 𝗡𝗔𝗗𝗔𝗟 𝟮𝟬𝟮𝟭...       *      ||\n");
	printf("||  *            *            *          *                ||\n");
	printf("|| *             ...𝙋𝙀𝙍 𝙁𝙀𝙍𝙉𝘼𝙉𝘿𝙊, 𝙀𝙍𝙄𝘾 𝙄 𝙏𝙊𝙉𝙄   *        ||\n");
	printf("||             *      *            *               *      ||\n");
	printf("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER MOSTRAR ELS NUMEROS PREMIATS

void mostrarPremiats (int premis[], int nPremis) {
	int i, j=nPremis/2, cont=0, mostrar=FALS;
	
	do {
	    printf("  -> "); 
	    printf("Vols veure tots els numeros premiats? (1/SI - 0/NO): ");
        scanf("%d", &mostrar);
	} while (mostrar != 0 && mostrar != 1);
	
    if (mostrar == CERT) {
    	printf("\n                NUMEROS PREMIATS LOTERIA 2021\n");
    	printf("               ================================\n");
    	for (i = 0; i < nPremis/2; i++) {
    	    printf("               || %05d       ||     %05d   ||\n", premis[i], premis[j]);
    	    j++;
    	    cont+=2;
    	}
    	printf("               || %05d       ||     %05d   ||\n", premis[nPremis-2], premis[nPremis-1]);
    	printf("               ================================\n");
    }
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR LA PART EXTRA DEL PROJECTE

void amics(int premis[], int nPremis) {
	
	int i, j=0, temp, randomIndex, nAmics, posicio[20];
	float sumaPagat=0, sumaPremi=0;
	const char * nombres[20] = {"Toni","Fer","Eric","Pol","Luis","Manuela","Carmen","Gerard","Quim","Pep","Motumbo","Julio","Kike","Jenifer","Mauro","Max","David","Marta","Luisa","Peponsio"};
	
	do {
	    printf("\n  -> ");
	    printf("Quants amics sou? (2/20): ");
	    scanf("%d", &nAmics);
	    if (nAmics < 2 || nAmics > 20) printf("\nHeu de ser entre 2 i 20 amics...\n");
	} while (nAmics < 2 || nAmics > 20);
	
	for(i=0; i < nAmics; i++)   posicio[i]=i;
	
	for (int i = 0; i < nAmics ; i++) {
		temp = posicio[i];
		randomIndex = rand() % nAmics;

		posicio[i] = posicio[randomIndex];
		posicio[randomIndex] = temp;
	}
	
	for (i = 1; i <= nAmics; i++) {
	    strcpy(usuari[i].nom, nombres[posicio[j]]);
	    usuari[i].nDecim = rand()%NOMBRE_NUMEROS;
	    do {
	        usuari[i].pagat = rand()%65+1; 
	    } while (fmod(usuari[i].pagat,5) != 0.0 && usuari[i].pagat > 0.0);
	    comprovarPremi(premis, nPremis, i);
	    if (!usuari[i].premi) {
	        comprovarPremiPetit(i);
	    }
	    sumaPagat+=usuari[i].pagat;
	    sumaPremi+=usuari[i].premi;
	    j++;
    }
    
    printf("\n     +=======================================+\n");
	printf("     |  ANY  |  MEMBRES  |  DINERS  |  PREMI |\n");
	printf("     +---------------------------------------+\n");
	printf("     |   2021|        %d |   %.2f | %.2f |\n", nAmics, sumaPagat, sumaPremi);
	printf("     +=======================================+\n");
	printf("     +=======================================+\n");
	printf("     |  AMIC |  NUMERO   |  DINERS  |  PREMI |\n");
	for (i = 1; i <= nAmics; i++) {
	    printf("     |%s     |  %05d    |   %.2f  | %.2f|\n", usuari[i].nom, usuari[i].nDecim, usuari[i].pagat, usuari[i].premi);
	}
	printf("     +=======================================+\n");
}

//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER DEMANAR DADES
void inserirDades() {
	
	int nDecim, decimCorrecte;
    float pagat; 
	
	do  {
		printf("\n  -> ");
		printf("Introdueix el número del teu dècim: ");
		scanf("%d", &nDecim);
		usuari[0].nDecim=nDecim;
		if (nDecim >= 0 && nDecim <= 99999) {
			decimCorrecte=CERT;
		} else {
			printf("El dècim introduït és incorrecte, ha d'estar entre el 00000 i el 99999.\n");
		}
	} while (!decimCorrecte);
	
	printf("  -> ");
	printf("Indica quants diners has posat en aquest número: ");
	scanf("%f", &pagat);
	usuari[0].pagat=pagat;
	printf("\n");
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR SI ÉS PREMI GRAN.

void comprovarPremi(int premis[], int nPremis, int nUsuari) {
	int j, posicioPremi, premiat = FALS;
	
    for (j = 0; j < nPremis && !(premiat); j++) {
    	if(premis[j] == usuari[nUsuari].nDecim){
    		posicioPremi=j;
    		premiat=CERT;
    	}
    }
    
    if (premiat) {
    	switch(posicioPremi)
    	{
    		case 0:
    	        
    	        for (j = 0; j < 2; j++) {
    			    printf("          !!!!!!!!!!!!!!!\n");
    			    sleep(1);
    			}
    			
    			if (usuari[nUsuari].nAmic == 0) { 
    			    printf("\n     Has guanyat el primer premi: %d\n", PRIMER_PREMI);
    			    usuari[nUsuari].premi=usuari[nUsuari].pagat*PRIMER_PREMI/DECIM/PREU_DECIM;
    			    printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    			}
    			usuari[nUsuari].premi=usuari[nUsuari].pagat*PRIMER_PREMI/DECIM/PREU_DECIM;
    			
    			for (j = 0; j < 2; j++) {
    				sleep(1);
    			    printf("          !!!!!!!!!!!!!!!\n");
    			}
    			
    			break;
    		case 1:
    			if (usuari[nUsuari].nAmic == 0) {
    			    printf("     Has guanyat el segon premi: %d\n", SEGON_PREMI);
    			    usuari[nUsuari].premi=usuari[nUsuari].pagat*SEGON_PREMI/DECIM/PREU_DECIM;
    			    printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    	        }
    			usuari[nUsuari].premi=usuari[nUsuari].pagat*SEGON_PREMI/DECIM/PREU_DECIM;
    			break;
    		case 2:
    		    if (usuari[nUsuari].nAmic == 0) {
    			    printf("     Has guanyat el tercer premi: %d\n", TERCER_PREMI);
    			    usuari[nUsuari].premi=usuari[nUsuari].pagat*TERCER_PREMI/DECIM/PREU_DECIM;
    			    printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    		    }
    			usuari[nUsuari].premi=usuari[nUsuari].pagat*TERCER_PREMI/DECIM/PREU_DECIM;
    			break;
    		case 3 ... 4:
    		    if (usuari[nUsuari].nAmic == 0) {
        			printf("     Has guanyat el quart premi: %d\n", QUART_PREMI);
        			usuari[nUsuari].premi=usuari[nUsuari].pagat*QUART_PREMI/DECIM/PREU_DECIM;
        			printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    		    }
    		    usuari[nUsuari].premi=usuari[nUsuari].pagat*QUART_PREMI/DECIM/PREU_DECIM;
    			break;
    		case 5 ... 13:
    		    if (usuari[nUsuari].nAmic == 0) {
    			    printf("     Has guanyat el cinque premi: %d\n", CINQUE_PREMI);
    			    usuari[nUsuari].premi=usuari[nUsuari].pagat*CINQUE_PREMI/DECIM/PREU_DECIM;
    			    printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    		    }
    		    usuari[nUsuari].premi=usuari[nUsuari].pagat*CINQUE_PREMI/DECIM/PREU_DECIM;
    			break;
    		default:
    		    if (usuari[nUsuari].nAmic == 0) {
    			    printf("     El numero esta premiat amb 1000 euros.\n");
    			    usuari[nUsuari].premi=usuari[nUsuari].pagat*PREMI_MENOR/DECIM/PREU_DECIM;
    			    printf("     Has jugat %.2f euros, aixi que de premi final et queda %.2f\n", usuari[nUsuari].pagat, usuari[nUsuari].premi);
    		    }
    			usuari[nUsuari].premi=usuari[nUsuari].pagat*PREMI_MENOR/DECIM/PREU_DECIM;
    			break;
    	}
    }
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER COMPROVAR ELL PREMIS PETITS

void comprovarPremiPetit (int nUsuari) {
	
	//APROXIMACIONS (1r, 2n, 3r)
        if (usuari[nUsuari].nDecim==p[0].nDecim+1 || usuari[nUsuari].nDecim==p[0].nDecim-1) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens la aproximació del primer premi.\n");
                printf("     PREMI = %05d\n", p[0].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO1er/DECIM)/PREU_DECIM; 
                printf("     Has jugat %.2f , de l'aproximació et toca: %.2f\n\n", usuari[nUsuari].pagat,usuari[nUsuari].pagat*(APROXIMACIO1er/DECIM)/PREU_DECIM); 
            } else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO1er/DECIM)/PREU_DECIM; }
        }
        if (usuari[nUsuari].nDecim==p[1].nDecim+1 || usuari[nUsuari].nDecim==p[1].nDecim-1) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens la aproximació del segon premi.\n");
                printf("     PREMI = %05d\n", p[1].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO2on/DECIM)/PREU_DECIM; 
                printf("     Has jugat %.2f , de l'aproximació et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(APROXIMACIO2on/DECIM)/PREU_DECIM); 
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO2on/DECIM)/PREU_DECIM;}   
        }
        if (usuari[nUsuari].nDecim==p[2].nDecim+1 || usuari[nUsuari].nDecim==p[2].nDecim-1) {
            if (usuari[nUsuari].nAmic == 0) {
            printf("     Tens la aproximació del tercer premi.\n");
            printf("     PREMI = %05d\n", p[2].nDecim);
            printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
            usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO3er/DECIM)/PREU_DECIM;
            printf("     Has jugat %.2f , de l'aproximació et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(APROXIMACIO3er/DECIM)/PREU_DECIM); 
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(APROXIMACIO3er/DECIM)/PREU_DECIM;}
        }
        
        //DUES ULTIMES XIFRES (1r, 2n, 3r)
        
        if (p[0].nDecim%100 == usuari[nUsuari].nDecim%100) {
            if (usuari == 0) {
                printf("     Tens les dues ultimes xifres iguals al primer premi.\n");
                printf("     PREMI = %05d\n", p[0].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de les dues ultimes xifres, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;}
        }
        if (p[1].nDecim%100 == usuari[nUsuari].nDecim%100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens les dues ultimes xifres iguals al segon premi.\n");
                printf("     PREMI = %05d\n", p[1].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de les dues ultimes xifres, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM; }      
        }
        if (p[2].nDecim%100 == usuari[nUsuari].nDecim%100) {
            if (usuari == 0) {
                printf("     Tens les dues últimes xifres iguals al tercer premi.\n");
                printf("     PREMI = %05d\n", p[2].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de les dues ultimes xifres, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM);
            }    
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(XIFRES_FINALS123/DECIM)/PREU_DECIM;}
        }
        
        //CENTENES (1r, 2n, 3r, 4t, 4t)
        
        if (p[0].nDecim/100 == usuari[nUsuari].nDecim/100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens l'aproximació a centenes del primer número.\n");
                printf("     PREMI = %05d\n", p[0].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de l'aproximació a les centenes, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;}
        }
        if (p[1].nDecim/100 == usuari[nUsuari].nDecim/100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens l'aproximació a centenes del segon número.\n");
                printf("     PREMI = %05d\n", p[1].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de l'aproximació a les centenes, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;}
        }
        if (p[2].nDecim/100 == usuari[nUsuari].nDecim/100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens l'aproximació a centenes del tercer número.\n");
                printf("     PREMI = %05d\n", p[2].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de l'aproximació a les centenes, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;}
        }
        if (p[3].nDecim/100 == usuari[nUsuari].nDecim/100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens l'aproximació a centenes del quart número.\n");
                printf("     PREMI = %05d\n", p[3].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de l'aproximació a les centenes, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;}
        }
        if (p[4].nDecim/100 == usuari[nUsuari].nDecim/100) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens l'aproximació a centenes del quart número.\n");
                printf("     PREMI = %05d\n", p[4].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, de l'aproximació a les centenes, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(CENTENES12344/DECIM)/PREU_DECIM;}
        }
        
        //REINTEGRAMENT (1r)
        
        if (p[0].nDecim%10 == usuari[nUsuari].nDecim%10) {
            if (usuari[nUsuari].nAmic == 0) {
                printf("     Tens el reintegrament ja que l'últim número del teu dècim coincideix amb l'últim del primer premi.\n");
                printf("     PREMI = %05d\n", p[0].nDecim);
                printf("     DECIM = %05d\n", usuari[nUsuari].nDecim);
                usuari[nUsuari].premi += usuari[nUsuari].pagat*(REINTEGRAMENT/DECIM)/PREU_DECIM;
                printf("     Has jugat %.2f, del reintegrament, et toca: %.2f\n\n", usuari[nUsuari].pagat, usuari[nUsuari].pagat*(REINTEGRAMENT/DECIM)/PREU_DECIM);
            }
            else { usuari[nUsuari].premi += usuari[nUsuari].pagat*(REINTEGRAMENT/DECIM)/PREU_DECIM; }
        }
        if (usuari[nUsuari].nAmic == 0) {
            if (usuari[nUsuari].premi != 0) {
                printf("     El premi final a pagar és de %.2f\n", usuari[nUsuari].premi);
            } else {
                printf("     \033[5;31mHo sentim, el teu dècim no està premiat.\n");
            }
        }
}
//--------------------------------------------------------------



//--------------------------------------------------------------
//FUNCIO PER VEURE SI VOL INTRODUIR UN NOU VALOR

void continuar(int * repetir) {
    
    do {
        printf("\n  -> ");
        printf("Vols continuar comprobant? (1/SI - 0/NO): ");
    	scanf("%d", &(*repetir));
    	if (*repetir == 0) {
    	    printf("\n   ==============================================\n");
    	    printf("   || Gracies per utilitzar el nostre programa ||\n");
    	    printf("   || By: Fernando, Eric i Toni                ||\n");
    	    printf("   ==============================================");
    	} else {
    	    usuari[0].premi = 0;
    	}
    } while (*repetir != 1 && *repetir != 0);
    
}

//--------------------------------------------------------------



//--------------------------------------------------------------
// MAIN DEL PROGRAMA

int main() {
    int nPremis = NR_PREMIS_MENORS + NR_PREMIS_MAJORS,  
	premis[nPremis],
	opcio,
	repetir=FALS;

	generarNumero(premis, nPremis);
    
	imatgeInicial();
	
    mostrarPremiats(premis, nPremis);
    
    do {
        do {
            
            printf("\n  -> ");
            printf("Vols comprovar amb amics o sol? (1/AMICS - 2/SOL): "); scanf("%d", &opcio);
            
        } while (opcio != 1 && opcio != 2);
        
        if (opcio == 1) {
            
            amics(premis, nPremis);
            
        } else {

            inserirDades();
            	    
            comprovarPremi(premis, nPremis, 0);
                    
            if (usuari[0].premi==0) {
                comprovarPremiPetit(0); 
            }
        }
        
        continuar(&repetir);
        
    } while (repetir);
    
  return 0;
}
//--------------------------------------------------------------
