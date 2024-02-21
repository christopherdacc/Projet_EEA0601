#include "p30f4012.h"
#include "dsp.h"
#include "LCDv2.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion du LCD EA DOG163
* en SPI (5V)
*           D. CARTON, M. COLAS - Mars 2013
*                        V 1.0
*
*
* ----------------------------------------------------------
*                 Exemple d'utilisation
* ----------------------------------------------------------  
*
*   #include "LCD.h"
*
*   void main(void){
*
*   InitLCD();
*   LCDWriteStr("Bonjour");
*   while(1);
*   }
*
*
*
************************************************************
***********************************************************/





void _wait10mus(unsigned int tenmus){
	int k;

	for(k=0;k<tenmus;k++){
		asm("REPEAT #295");
		asm("NOP");
	}
}


void _InitSPI(void){
	SPI1STATbits.SPIROV=0;
	SPI1CON=0b0000000001111001; 		// prescaler=32 : Fclk=921.5kHz
	SPI1STATbits.SPIEN=1;
	while(SPI1STATbits.SPITBF);
}


void _LCDCmdWrite(char c,unsigned int wait){
	_CSB=0;
	_wait10mus(5);
	_RS=0;
	_wait10mus(5);
	SPI1BUF=c;
	while(SPI1STATbits.SPITBF);
	_wait10mus(wait);
	_CSB=1;
}



/***********************************************************
              fonctions publiques
***********************************************************/

void InitLCD(void){
	// prog RS en sortie
	TRISBbits.TRISB0=0;
	// prog CSB en sortie
	TRISBbits.TRISB1=0;	
	// prog RESET en sortie
	TRISBbits.TRISB2=0;

	_InitSPI();

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
	SPI1BUF=c;
	while(SPI1STATbits.SPITBF);
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