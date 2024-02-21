/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Timer
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/


#include "p30f4012.h"
#include "dsp.h"
#include "periph_tmr.h"


/**************************************************************/
/*                  										  */
/*                Timer 3 (32bits)                            */
/*                                                            */
/**************************************************************/


// Description registres :

// -------------------------------
// T2CON: Time Base Register
// -------------------------------
/*
	bit 15 TON: Timer On Control bit
		1 = Starts the timer
		0 = Stops the timer

	bit 14 Unimplemented: Read as ‘0’

	bit 13 TSIDL: Stop in Idle Mode bit
		1 = Discontinue timer operation when device enters Idle mode
		0 = Continue timer operation in Idle mode

	bit 12-7 Unimplemented: Read as ‘0’

	bit 6 TGATE: Timer Gated Time Accumulation Enable bit
		1 = Gated time accumulation enabled
		0 = Gated time accumulation disabled
		(TCS must be set to ‘0’ when TGATE = 1. Reads as ‘0’ if TCS = 1)

	bit 5-4 TCKPS<1:0>: Timer Input Clock Prescale Select bits
		11 = 1:256 prescale value
		10 = 1:64 prescale value
		01 = 1:8 prescale value
		00 = 1:1 prescale value

	bit 3 T32 : 32 bit timer mode (type B) otherwise read as 0

	bit 2 TSYNC: Timer External Clock Input Synchronization Select bit
		When TCS = 1:
		1 = Synchronize external clock input
		0 = Do not synchronize external clock input
		When TCS = 0:
		This bit is ignored. Read as ‘0’. Timer1 uses the internal clock when TCS = 0.

	bit 1 TCS: Timer Clock Source Select bit
		1 = External clock from pin TxCK
		0 = Internal clock (FOSC/4)

	bit 0 Unimplemented: Read as ‘0’
*/





// periode N : T=N*33.6ns (jusque 134s)
void InitTimer3(unsigned long periode)
{
T3CON=0;							// pas de prescaler
T2CON=0;			// idem
TMR2=0;
TMR3=0;

PR3=periode>>16;
PR2=periode&0x0000ffff;
T2CONbits.T32=1;				// mode 32 bits

}


void Timer3InterruptEnable(void)
{
IPC1bits.T3IP=1;   // priorité interruption =1
IFS0bits.T3IF=0;   // RAZ flag interruption
IEC0bits.T3IE=1;   // autorisation interruption 
T2CONbits.TON=1;   // mise en route du timer
}

