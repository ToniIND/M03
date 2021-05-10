#include <stdio.h>
#include <time.h>

struct usuari {
	int nom;
	int any;
};

int main()
{
	int anyActual, mesActual, diaActual, error;
	struct usuari usuari1;
	do{
		error=0;
		printf("Año: "); scanf("%d", &usuari1.any);
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		anyActual= tm.tm_year + 1900;
		mesActual= tm.tm_mon + 1;
		diaActual= tm.tm_mday;
		
		if((usuari1.any==anyActual && mesActual==12 && diaActual>=22) || (usuari1.any>1812 && usuari1.any<anyActual)){
			error=1;
		}
	}while(!error);
} 
