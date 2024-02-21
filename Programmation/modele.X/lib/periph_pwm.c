#include "p30f4012.h"
#include "dsp.h"
#include "periph_pwm.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la PWM
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/





void InitPWM(unsigned int val,enum PWM_PIN_INIT_FLAGS PIN_Init)
{
/*
PTCON : PWM Time Base Control register
bit 15 PTEN: PWM Time Base Timer Enable bit
		1 = PWM time base is ON
		0 = PWM time base is OFF
bit 14 Unimplemented: Read as ‘0’
bit 13 PTSIDL: PWM Time Base Stop in Idle Mode bit
		1 = PWM time base halts in CPU Idle mode
		0 = PWM time base runs in CPU Idle mode
bit 12-8 Unimplemented: Read as ‘0’
bit 7-4 PTOPS<3:0>: PWM Time Base Output Postscale Select bits
		1111 = 1:16 Postscale
		•
		•
		0001 = 1:2 Postscale
		0000 = 1:1 Postscale
bit 3-2 PTCKPS<1:0>: PWM Time Base Input Clock Prescale Select bits
		11 = PWM time base input clock period is 64 TCY (1:64 prescale)
		10 = PWM time base input clock period is 16 TCY (1:16 prescale)
		01 = PWM time base input clock period is 4 TCY (1:4 prescale)
		00 = PWM time base input clock period is TCY (1:1 prescale)
bit 1-0 PTMOD<1:0>: PWM Time Base Mode Select bits
		11 = PWM time base operates in a continuous up/down mode with interrupts for double PWM updates
		10 = PWM time base operates in a continuous up/down counting mode
		01 = PWM time base operates in single event mode
		00 = PWM time base operates in a free running mode
*/
PTCON=0b00000000000001100;	  // prescaler=64	
		

						
/*  PTMR: PWM Time Base register
bit 15 Unimplemented: Read as ‘0’
bit 14-0 PTPER<14:0>: PWM Time Base Period Value bits
*/
PTPER=val; 				//PWM Time Base Period register


/* PWMCON1 :PWM Control register 1

bit 15-12 Unimplemented: Read as ‘0’
bit 11-8 PMOD4:PMOD1: PWM I/O Pair Mode bits
		1 = PWM I/O pin pair is in the independent output mode
		0 = PWM I/O pin pair is in the complementary output mode
bit 7-4 PEN4H-PEN1H: PWMxH I/O Enable bits(1)
		1 = PWMxH pin is enabled for PWM output
		0 = PWMxH pin disabled. I/O pin becomes general purpose I/O
bit 3-0 PEN4L-PEN1L: PWMxL I/O Enable bits(1)
		1 = PWMxL pin is enabled for PWM output
		0 = PWMxL pin disabled. I/O pin becomes general purpose I/O
Note 1: Reset condition of the PENxH and PENxL bits depend on the value of the PWM/PIN device
configuration bit in the FBORPOR Device Configuration Register.
*/
//PWMCON1=0b0000000000110000;			//PEN2H+PEN1H ;
PWMCON1=~PIN_Init;

/* PWMCON2 : PWM Control register 2

bit 15-12 Unimplemented: Read as ‘0’
bit 11-8 SEVOPS<3:0>: PWM Special Event Trigger Output Postscale Select bits
		1111 = 1:16 Postscale
		•
		•
		0001 = 1:2 Postscale
		0000 = 1:1 Postscale
bit 7-2 Unimplemented: Read as ‘0’
bit 2 IUE: Immediate Update Enable bit(1)
		1 = Updates to the active PDC registers are immediate
		0 = Updates to the active PDC registers are synchronized to the PWM time base
bit 1 OSYNC: Output Override Synchronization bit
		1 = Output overrides via the OVDCON register are synchronized to the PWM time base
		0 = Output overrides via the OVDCON register occur on next TCY boundary
bit 0 UDIS: PWM Update Disable bit
		1 = Updates from duty cycle and period buffer registers are disabled
		0 = Updates from duty cycle and period buffer registers are enabled
Note 1: IUE bit is not implemented on the dsPIC30F6010 device.



*/

PWMCON2=0b0000000000000000;			// postscaler=1, synchronized update, 

DTCON1=0;									//DTCON1: Dead Time Control register #1
FLTACON=0;									//FLTACON: Fault A Control register
}


// routine d'activation et de desactivation de la PWM
void PWMEnable(enum MOD_ENABLE onoff){
PTCONbits.PTEN=onoff;
}


// routine de réglage du rapport cyclique
/*
PDC1: PWM Duty Cycle Register 1
bit 15-0 PDC1<15:0>: PWM Duty Cycle #1 Value bits
*/
void PWM1PulseWidth(unsigned int Ton){
PDC1=2*Ton;
}

void PWM2PulseWidth(unsigned int Ton){
PDC2=2*Ton;
}


