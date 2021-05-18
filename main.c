#include <stdio.h>
#include "dades.h"

/*-------------------------------------------------------------*/
/*FUNCIO: Main del programa                                    */

int main (void) {
	
	int format;
	
	idiomes();
	
	printf("\n%s", linies[7]);
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
