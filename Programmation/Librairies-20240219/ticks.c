#include <xc.h>
#include <stdbool.h>
#include "ticks.h"
 
static Time timeCounter;
 
void __attribute__((__interrupt__,no_auto_psv)) _T2Interrupt(void){
	timeCounter++;

	IFS0bits.T2IF = 0;
}

 
void initTime(){
	timeCounter = 0;
	TMR2 = 0;
	PR2 = TIME_MS;
	T2CON = 0;			  //prescaler )= 1, Oscillateur interne
	IFS0bits.T2IF = 0;    // on s'assure qu'il n'y a pas de demande d'interruption en cours
	IEC0bits.T2IE = 1;    // on autorise les interruptions T1
	T2CONbits.TON=1;
}

Time getTime(){
	return timeCounter;
}

bool isTimeOver(Time origin,unsigned int duration){
	return (((unsigned int)(timeCounter - origin)) > duration) ;


}