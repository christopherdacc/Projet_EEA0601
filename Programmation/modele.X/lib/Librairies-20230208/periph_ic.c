/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Input Capture
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

/**********************************************************/
/*                    	 						          */
/*              Capture de fronts sur RB4 (IC7)           */
/*                                                        */
/**********************************************************/


#include "p30f4012.h"
#include "dsp.h"
#include "periph_ic.h"

// -------------------------------
// IC7CON: Input Capture Control Register
// -------------------------------

/*
	bit 15-14 Unimplemented: Read as ‘0’
	bit 13 ICSIDL: Input Capture Module Stop in Idle Control bit
		1 = Input capture module will halt in CPU Idle mode
		0 = Input capture module will continue to operate in CPU Idle mode

	bit 12-8 Unimplemented: Read as ‘0’

	bit 7 ICTMR: Input Capture Timer Select bits
		1 = TMR2 contents are captured on capture event
		0 = TMR3 contents are captured on capture event
		Note: Timer selections may vary. Refer to the device data sheet for details.

	bit 6-5 ICI<1:0>: Select Number of Captures per Interrupt bits
		11 = Interrupt on every fourth capture event
		10 = Interrupt on every third capture event
		01 = Interrupt on every second capture event
		00 = Interrupt on every capture event

	bit 4 ICOV: Input Capture Overflow Status Flag (Read Only) bit
		1 = Input capture overflow occurred
		0 = No input capture overflow occurred

	bit 3 ICBNE: Input Capture Buffer Empty Status (Read Only) bit
		1 = Input capture buffer is not empty, at least one more capture value can be read
		0 = Input capture buffer is empty

	bit 2-0 ICM<2:0>: Input Capture Mode Select bits
		111 = Input Capture functions as interrupt pin only, when device is in Sleep or Idle mode
		(Rising edge detect only, all other control bits are not applicable.)
		110 = Unused (module disabled)
		101 = Capture mode, every 16th rising edge
		100 = Capture mode, every 4th rising edge
		011 = Capture mode, every rising edge
		010 = Capture mode, every falling edge
		001 = Capture mode, every edge (rising and falling)
		(ICI<1:0> does not control interrupt generation for this mode.)
		000 = Input capture module turned off
*/




void IC7InterruptEnable(unsigned int edge)
{
IPC4bits.IC7IP=1;   // priorité interruption =1
IFS1bits.IC7IF=0;   // RAZ flag interruption
IEC1bits.IC7IE=1;   // autorisation interruption 
IC7CON=0;			// Timer 3, Interrupt on every capture event, capture off
IC7CONbits.ICM=edge; // capture event on every falling or rising edge
}

