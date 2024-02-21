/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la PWM 
* 
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

#ifndef PWM_H
#define PWM_H



enum MOD_ENABLE
{
ON= 1,
OFF= 0
};


// Flags de configuration Pins
enum PWM_PIN_INIT_FLAGS 
{
	PEN1L = 0b11111111111111110,
	PEN2L = 0b11111111111111101,
	PEN3L = 0b11111111111111011,
	PEN4L = 0b11111111111110111,
	PEN1H = 0b11111111111101111,
	PEN2H = 0b11111111111011111,
	PEN3H = 0b11111111110111111,
	PEN4H = 0b11111111101111111,
	INDEP1= 0b11111111011111111,
	INDEP2= 0b11111110111111111,
	INDEP3= 0b11111101111111111,
	INDEP4= 0b11111011111111111,
};




// Tpwm=periode x 2.17 µs
void InitPWM(unsigned int periode,enum PWM_PIN_INIT_FLAGS init);
void PWMEnable(enum MOD_ENABLE onoff);

// Tpwm_on=Ton x 2.17 µs
void PWM1PulseWidth(unsigned int Ton);
void PWM2PulseWidth(unsigned int Ton);

#endif
