/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la conversion AN
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

#ifndef ADC_H
#define ADC_H

// initialisation des conversions analogiques-numériques
void InitADCx(void);
void InitADC0(void);
void InitADC0and1(void);
void InitADC4and5(void);
void InitADC0to3(void);
void InitADC0Seq0to4(void);
void InitADC0Seq0to5(void);

// lancement conversion analogique numérique
unsigned int StartADCx(unsigned char channel);
void StartADC0(unsigned int* ADCxValue0);
void StartADC0and1(unsigned int* ADCxValue0,unsigned int* ADCxValue1);
void StartADC0to3(unsigned int* ADCxValue0,unsigned int* ADCxValue1,unsigned int* ADCxValue2,unsigned int* ADCxValue3);
void StartADC4and5(unsigned int* ADCxValue0, unsigned int* ADCxValue1);
void StartADC0seq0to4(unsigned int* ADCxValue0, unsigned int* ADCxValue1, unsigned int* ADCxValue2, unsigned int* ADCxValue3, unsigned int* ADCxValue4);
void StartADC0seq0to5(unsigned int* ADCxValue0, unsigned int* ADCxValue1, unsigned int* ADCxValue2, unsigned int* ADCxValue3, unsigned int* ADCxValue4, unsigned int* ADCxValue5);


#endif
