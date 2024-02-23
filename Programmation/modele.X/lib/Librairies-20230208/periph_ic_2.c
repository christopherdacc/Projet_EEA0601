/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Input Capture
*
* Bibliotheque : periph_ic_2
*
*           D. CARTON, M. COLAS - Mars 2021
*                        V 1.0
************************************************************
***********************************************************/

#include "p30f4012.h"
#include "dsp.h"
#include "periph_ic_2.h"


void IC7Init(unsigned char timer, unsigned char mode) {
	IC7CON=0b0000000000000000;	// Interrupt on every capture event, capture off
	IC7CONbits.ICTMR=timer;		// Timer
	IC7CONbits.ICM=mode;		// Mode et démarrage
}

void IC7InterruptEnable2(unsigned char priority) {
	IPC4bits.IC7IP=priority;	// priorité interruption
	IFS1bits.IC7IF=0;  			// RAZ flag interruption
	IEC1bits.IC7IE=1;   		// autorisation interruption 
}

void IC8Init(unsigned char timer, unsigned char mode) {
	IC8CON=0b0000000000000000;	// Interrupt on every capture event, capture off
	IC8CONbits.ICTMR=timer;		// Timer
	IC8CONbits.ICM=mode;		// Mode et démarrage
}

void IC8InterruptEnable2(unsigned char priority) {
	IPC4bits.IC8IP=priority;	// priorité interruption
	IFS1bits.IC8IF=0;   		// RAZ flag interruption
	IEC1bits.IC8IE=1;			// autorisation interruption 
}

