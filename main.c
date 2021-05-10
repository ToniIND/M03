#include <stdio.h>
#include "dades.h"

/*-------------------------------------------------------------*/
/*FUNCIO: Main del programa                                    */

int main (void) {
	
	idiomes();
	
	infoJugador();
	
	if (usuari1.colla == 0) {
		generarPremis();
	} else {
		colles();
	}
	
	return 0;
}

/*-------------------------------------------------------------*/


