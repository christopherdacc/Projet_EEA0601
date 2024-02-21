/***********************************************************
************************************************************
*
* Fichier de configuration et de la liaison RS232
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/



#ifndef UART_H
#define UART_H

// initialisation de la liaison s�rie 
void SERIALinit(unsigned int baudrate);

// test caract�re pr�sent dans buffer 
unsigned int SERIALReadCharReceived();

// routine d'�criture d'un caract�re sur liaison s�rie 
void SERIALWrite(char c);

// routine de lecture d'un caract�re sur liaison s�rie 
char SERIALRead();




#endif
