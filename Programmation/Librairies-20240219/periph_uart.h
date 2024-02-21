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

// initialisation de la liaison série 
void SERIALinit(unsigned int baudrate);

// test caractère présent dans buffer 
unsigned int SERIALReadCharReceived();

// routine d'écriture d'un caractère sur liaison série 
void SERIALWrite(char c);

// routine de lecture d'un caractère sur liaison série 
char SERIALRead();




#endif
