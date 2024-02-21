/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion Input Capture
*
* Bibliotheque : periph_ic_2
*
*           D. CARTON, M. COLAS - Mars 2021
*                        V 1.0
************************************************************
***********************************************************/

#ifndef PERIPH_IC_2
#define PERIPH_IC_2

// Equivalences pour la sélection du mode
#define IC_FRONTS_MONTANTS_ET_DESCENDANTS 1
#define IC_FRONTS_DESCENDANTS             2
#define IC_FRONTS_MONTANTS                3
#define IC_4_FRONTS_MONTANTS              4
#define IC_16_FRONTS_MONTANTS             5

// Equivalences pour la sélection du timer
#define IC_TIMER2 1
#define IC_TIMER3 0


void IC7Init(unsigned char timer, unsigned char mode);

void IC7InterruptEnable2(unsigned char priority);

void IC8Init(unsigned char timer, unsigned char mode);

void IC8InterruptEnable2(unsigned char priority);

#endif
