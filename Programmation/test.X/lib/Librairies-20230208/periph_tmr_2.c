/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Timer
*
* Bibliotheque : periph_tmr_2
*
*           D. CARTON, M. COLAS - Mars 2021
*                        V 1.0
************************************************************
***********************************************************/


#include "p30f4012.h"
#include "dsp.h"
#include "periph_tmr_2.h"

void Timer116Init(unsigned char prescaler, unsigned int periode) {	// timer de type A                              ****** A tester
  T1CON = 0b0000000000000000;			
  T1CONbits.TCKPS = prescaler;  // prescaler 
  TMR1 = 0;
  PR1 = periode;                // 16 bits
}

void Timer116InterruptEnable(unsigned char priority) {
  IPC0bits.T1IP = priority;     // priorité interruption
  IFS0bits.T1IF = 0;            // RAZ flag interruption
  IEC0bits.T1IE = 1;            // autorisation interruption 
}

void Timer116Start(void) {
  T1CONbits.TON = 1;            // mise en route du timer
}

void Timer216Init(unsigned char prescaler, unsigned int periode) {	// timer de type B                              ****** A tester
  T2CON = 0b0000000000000000;   // mode 16 bits, entraine la mise au format 16 bits du timer 3
  T2CONbits.TCKPS = prescaler;  // prescaler 
  TMR2 = 0;
  PR2 = periode;                // 16 bits
}

void Timer216InterruptEnable(unsigned char priority) {
  IPC1bits.T2IP = priority;     // priorité interruption
  IFS0bits.T2IF = 0;            // RAZ flag interruption
  IEC0bits.T2IE = 1;            // autorisation interruption 
}

void Timer216Start(void) {
  T2CONbits.TON = 1;            // mise en route du timer
}

void Timer316Init(unsigned char prescaler, unsigned int periode) {
  // Timer de type C (mode 16bits)
  
  T2CONbits.T32 = 0;            // mode 16 bits, entraine la mise au format 16 bits du timer 2

  T3CON = 0b0000000000000000;   // Remise à zéro de T3CON (état normalement à l'initialisation)
                                //
                                // T3CON : Timer 3 Control Register
                                // --------------------------------
                                // bit 15   : TON: Timer On Control bit :
                                //             1 = Starts the timer
                                //             0 = Stops the timer
                                // bit 14   : Unimplemented: Read as ‘0’
                                // bit 13   : TSIDL: Stop in Idle Mode bit
                                //             1 = Discontinue timer operation when device enters Idle mode
                                //             0 = Continue timer operation in Idle mode
                                // bit 12-7 : Unimplemented: Read as ‘0’
                                // bit 6    : TGATE: Timer Gated Time Accumulation Enable bit
                                //             1 = Gated time accumulation enabled
                                //             0 = Gated time accumulation disabled
                                //             (TCS must be set to ‘0’ when TGATE = 1. Reads as ‘0’ if TCS = 1)
                                // bit 5-4  : TCKPS<1:0>: Timer Input Clock Prescale Select bits
                                //             11 = 1:256 prescale value
                                //             10 = 1:64 prescale value
                                //             01 = 1:8 prescale value
                                //             00 = 1:1 prescale value
                                // bit 3    : Unimplemented: Read as ‘0’
                                // bit 2    : TSYNC: Timer External Clock Input Synchronization Select bit
                                //             When TCS = 1:
                                //              1 = Synchronize external clock input
                                //              0 = Do not synchronize external clock input
                                //             When TCS = 0:
                                //              This bit is ignored. Read as ‘0’. Timer1 uses the internal clock when TCS = 0.
                                // bit 1    : TCS: Timer Clock Source Select bit
                                //             1 = External clock from pin TxCK
                                //             0 = Internal clock (F OSC /4)
                                // bit 0    : Unimplemented: Read as ‘0’

  T3CONbits.TCKPS = prescaler;  // Réglage du prescaler

  TMR3 = 0;                     // Mise à zéro "contenu" du Timer
  
  PR3 = periode;                // Réglage de la valeur du "contenu" du Timer qui correspond à la période : unsigned int : 16 bits
}

void Timer316InterruptEnable(unsigned short priority) {
  IPC1bits.T3IP = priority;     // priorité interruption
  IFS0bits.T3IF = 0;            // RAZ flag interruption
  IEC0bits.T3IE = 1;            // autorisation interruption 
}

void Timer316Start(void) {
  T3CONbits.TON = 1;            // mise en route du timer
}

