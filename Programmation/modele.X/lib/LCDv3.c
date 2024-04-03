/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion du LCD EA DOG163
* en SPI (5V) sur MPLAB X
* D. CARTON, M. COLAS - Février 2023
* V 3.0
*
*
* ----------------------------------------------------------
* Exemple d'utilisation
* ----------------------------------------------------------
*
* #include <xc.h>
* #include "./lib/LCDv2.h"
* int main(void){
* 
* InitLCD();
* LCDWriteStr("Bonjour");
* LCDWriteStr(" le monde");
* while(1);
* return(0);
* }
*
*
*
************************************************************
***********************************************************/

#include <xc.h>
#include <stdbool.h>
#include "LCDv3.h"


static int data = 0;
static bool done = true;


void __attribute__(( __interrupt__ ,__auto_psv__ )) _T1Interrupt(void) {

    static int step = 15;
   
    if(step >= 0) {
        _DATA = (data>>step)&0x0001;
        _CLK = (0b0101010101010101>>step)&0x0001;
        step--;
    }
    else{
        IEC0bits.T1IE = 0;
        
        _DATA = 0;
        _CLK = 0;
        done = true;
        step = 15;
    }    
    
    IFS0bits.T1IF = 0;
}



void _wait10mus(unsigned int tenmus){

    int k;

    for(k=0;k<tenmus;k++){
        asm("REPEAT #295");
        asm("NOP");
    }
}


/**
* Emulation SPI : initialisation
*
*/
void _InitSPIEmu(void){
    T1CON = 0;
    TMR1 = 0;
    PR1 = 737;              // 40kHz -> 25µs
    _CLK = 0;               // clear clock
    _DATA = 0;              // clear data
    TRISE&=~0x18;           // RB3 & 4 as output    11000
    T1CONbits.TON = 1;      // Timer 1 on
}


void _WriteToSpi(char c){

    int i;

    data = 0;
    for(i=0;i<8;i++){
    //data=data| ((c>>i)&1)<<(2*i) | (((c>>i)&1)<<(2*i+1));
        data<<=2;
        if(c&(1<<(7-i))) data|=3;
    }
    done = false;
    TMR1 = 0;
    IEC0bits.T1IE = 1; // autorisation It timer et de l'envoi du caractère
}


bool _SPIWritten(){
    return done;
}



void _LCDCmdWrite(char c,unsigned int wait){
    _CSB=0;
    _wait10mus(5);
    _RS=0;
    _wait10mus(5);
    _WriteToSpi(c);
    while(!_SPIWritten());
    _wait10mus(wait);
    _CSB=1;
}


/***********************************************************
fonctions publiques
***********************************************************/

void InitLCD(void){

    TRISEbits.TRISE0=0; // prog RS en sortie
    TRISEbits.TRISE1=0; // prog CSB en sortie
    TRISEbits.TRISE2=0; // prog RESET en sortie

    _InitSPIEmu();

    _LCDCmdWrite(_FUNCTIONSET,25);
    _LCDCmdWrite(_FUNCTIONSET,25);
    _LCDCmdWrite(_BIASSET,25);
    _LCDCmdWrite(_CONTRASTSET+7,25);
    _LCDCmdWrite(_POWERCONTROL+2,25);
    _LCDCmdWrite(_FOLLOWERCONTROL,3000);
    _LCDCmdWrite(_CLEARDISPLAY,500);
    _LCDCmdWrite(_DISPLAYON,25);
    _LCDCmdWrite(_ENTRYMODESET,25);
    _LCDCmdWrite(_HOME,500);
}


void LCDDataWrite(char c){
    _CSB=0;
    _wait10mus(5);
    _RS=1;
    _wait10mus(5);
    _WriteToSpi(c);
    while(!_SPIWritten());
    _wait10mus(25);
    _CSB=1;
}

void LCDWriteStr(char * str){
    
    int i=0;
    
    while(str[i]!=0) LCDDataWrite(str[i++]);
}


void LCDGoto( unsigned int r, unsigned int c){
    if((r>2)||(c>15)) return;
    _LCDCmdWrite((char)(0x80|(r*16+c)),25);
}

void LCDContrastSet(unsigned int c){
    if(c>63) return;
    _LCDCmdWrite((char)(_POWERCONTROL|((c>>4)&3)),25);
    _LCDCmdWrite((char)(_CONTRASTSET|(c&0xF)),25);
}


