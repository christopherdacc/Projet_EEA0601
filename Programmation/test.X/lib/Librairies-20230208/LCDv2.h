/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion du LCD EA DOG163
* en SPI (5V)
*           D. CARTON, M. COLAS - Mars 2013
*                        V 1.0
************************************************************
***********************************************************/

#ifndef LCD_H
#define LCD_H

// définitions locales

#define _RS					PORTBbits.RB0
#define _CSB				PORTBbits.RB1
#define _RESET				PORTBbits.RB2

#define _FUNCTIONSET		0x39				// 001	  N(1) DH (0) IS2:1 (01)
#define _BIASSET			0x1D				// 00001 BS(1) 1 0 FX(1)
#define _POWERCONTROL 		0x50				// 0101 ION(0) BON(0) C5:4 (00) 
#define _FOLLOWERCONTROL 	0x69				// 0110 FON(1) Rab2:0 (100)	
#define _CONTRASTSET		0x70	            // 0111 C4:1 (0000)
#define _DISPLAYON 			0x0C
#define _DISPLAYOFF 		0x08
#define _CLEARDISPLAY 		0x01
#define _ENTRYMODESET 		0x06
#define _HOME		 		0x02

void _LCDCmdWrite(char c,unsigned int wait);




// Définitions et fonctions publiques

#define	LCDHome()			_LCDCmdWrite(_HOME,500)
#define	LCDDisplayOn()		_LCDCmdWrite(_DISPLAYON,25)
#define	LCDDisplayOff()		_LCDCmdWrite(_DISPLAYOFF,25)
#define	LCDClearDisplay()	_LCDCmdWrite(_CLEARDISPLAY,500)


// initialisation du LCD
void InitLCD(void);

// affichage d'un caractère
void LCDDataWrite(char c);

// affichage d'une chaîne de caractère
void LCDWriteStr(char * str);

// modification de la position curseur. (0,0) : ligne 1 et colonne 1.
void LCDGoto(unsigned int r, unsigned int c);

// modification du contraste (0 à 63)
void LCDContrastSet(unsigned int c);

#endif
