/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la conversion AN
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

#ifndef PERIPH_ADC_2
#define PERIPH_ADC_2

// initialisation des conversions analogiques-numériques
void InitADCChoice0toN(unsigned int N);

// lancement conversion analogique numérique
void StartADCChoice0toN(unsigned int n, unsigned int* ADCxValue);


#endif
