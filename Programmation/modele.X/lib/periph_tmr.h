#ifndef PERIPH_TMR
#define PERIPH_TMR

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Timer
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/


// configuration des timers (T=periode x 33.6ns) 
void InitTimer3(unsigned long periode);

// demarrage timer+ autorisation interruption Timer3
void Timer3InterruptEnable(void);

// fonction d'attente sans timer
void wait(unsigned int timems);

#endif
