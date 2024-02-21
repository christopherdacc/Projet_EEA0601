#ifndef PERIPH_TMR_2
#define PERIPH_TMR_2

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


// FQuartz = 7.7728 MHz     (Valeur utilisée sur la carte Dspic de EE0601)
// CoefPLL = 16             (Valeur utilisée sur la carte Dspic de EE0601)
// Fosc = FQuartz * CoefPLL
// Fcy = Fosc/4
// Tcy = 1/Fcy
// Ttmr = Tcy * prescaler   (sortie du prescaler : base de temps effective du compteur)


// Equivalence pour la sélection du prescaler
#define TMR_PS1   0
#define TMR_PS8   1
#define TMR_PS64  2
#define TMR_PS256 3

void Timer116Init(unsigned char prescaler, unsigned int periode);

void Timer116InterruptEnable(unsigned char priority);

void Timer116Start(void);

void Timer216Init(unsigned char prescaler, unsigned int periode);
void Timer216InterruptEnable(unsigned char priority);

void Timer216Start(void);

void Timer316Init(unsigned char prescaler, unsigned int periode);

void Timer316InterruptEnable(unsigned short priority);

void Timer316Start(void);

#endif
