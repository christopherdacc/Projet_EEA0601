#include "p30f4012.h"
#include "dsp.h"
#include "periph_adc.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la conversion AN
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/



// Description registres :

// -------------------------------
// ADCON1 : A/D Control Register 1 
// -------------------------------
/*
	bit 15 ADON: A/D Operating Mode bit
		1 = A/D converter module is operating
		0 = A/D converter is off

	bit 14 Unimplemented: Read as ‘0’

	bit 13 ADSIDL: Stop in Idle Mode bit
		1 = Discontinue module operation when device enters Idle mode
		0 = Continue module operation in Idle mode

	bit 12-10 Unimplemented: Read as ‘0’

	bit 9-8 FORM<1:0>: Data Output Format bits
		11 = Signed Fractional (DOUT = sddd dddd dd00 0000)
		10 = Fractional (DOUT = dddd dddd dd00 0000)
		01 = Signed Integer (DOUT = ssss sssd dddd dddd)
		00 = Integer (DOUT = 0000 00dd dddd dddd)

	bit 7-5 SSRC<2:0>: Conversion Trigger Source Select bits
		111 = Internal counter ends sampling and starts conversion (auto convert)
		110 = Reserved
		101 = Reserved
		100 = Reserved
		011 = Motor Control PWM interval ends sampling and starts conversion
		010 = GP Timer3 compare ends sampling and starts conversion
		001 = Active transition on INT0 pin ends sampling and starts conversion
		000 = Clearing SAMP bit ends sampling and starts conversion

	bit 4 Unimplemented: Read as ‘0’

	bit 3 SIMSAM: Simultaneous Sample Select bit (only applicable when CHPS = 01 or 1x)
		1 = Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
		or
		Samples CH0 and CH1 simultaneously (when CHPS = 01)
		0 = Samples multiple channels individually in sequence

	bit 2 ASAM: A/D Sample Auto-Start bit
		1 = Sampling begins immediately after last conversion completes. SAMP bit is auto set
		0 = Sampling begins when SAMP bit set

	bit 1 SAMP: A/D Sample Enable bit
		1 = At least one A/D sample/hold amplifier is sampling
		0 = A/D sample/hold amplifiers are holding
		When ASAM = 0, writing ‘1’ to this bit will start sampling
		When SSRC = 000, writing ‘0’ to this bit will end sampling and start conversion

	bit 0 DONE: A/D Conversion Status bit (Rev. B silicon or later)
		1 = A/D conversion is done
		0 = A/D conversion is NOT done
		Cleared by software or start of a new conversion
		Clearing this bit will not effect any operation in progress
*/


// -------------------------------
// ADCON2 : A/D Control Register 2
// -------------------------------

/*
	bit 15-13 VCFG<2:0>: Voltage Reference Configuration bits

	bit 12 Reserved: User should write ‘0’ to this location

	bit 11 Unimplemented: Read as ‘0’

	bit 10 CSCNA: Scan Input Selections for CH0+ S/H Input for MUX A Input Multiplexer Setting bit
		1 = Scan inputs
		0 = Do not scan inputs

	bit 9-8 CHPS<1:0>: Selects Channels Utilized bits
		1x = Converts CH0, CH1, CH2 and CH3
		01 = Converts CH0 and CH1
		00 = Converts CH0
	    When SIMSAM bit (ADCON1<3>) = 0 multiple channels sampled sequentially
        When SMSAM bit (ADCON1<3>) = 1 multiple channels sampled as in CHPS<1:0>

	bit 7 BUFS: Buffer Fill Status bit
		Only valid when BUFM = 1 (ADRES split into 2 x 8-word buffers).
		1 = A/D is currently filling buffer 0x8-0xF, user should access data in 0x0-0x7
		0 = A/D is currently filling buffer 0x0-0x7, user should access data in 0x8-0xF

	bit 6 Unimplemented: Read as ‘0’

	bit 5-2 SMPI<3:0>: Sample/Convert Sequences Per Interrupt Selection bits
		1111 = Interrupts at the completion of conversion for each 16th sample/convert sequence
		1110 = Interrupts at the completion of conversion for each 15th sample/convert sequence
		.....
		0001 = Interrupts at the completion of conversion for each 2nd sample/convert sequence
		0000 = Interrupts at the completion of conversion for each sample/convert sequence

	bit 1 BUFM: Buffer Mode Select bit
		1 = Buffer configured as two 8-word buffers ADCBUF(15...8), ADCBUF(7...0)
		0 = Buffer configured as one 16-word buffer ADCBUF(15...0.)

	bit 0 ALTS: Alternate Input Sample Mode Select bit
		1 = Uses MUX A input multiplexer settings for first sample, then alternate between MUX B and MUX A input
		multiplexer settings for all subsequent samples
		0 = Always use MUX A input multiplexer settings
*/



// -------------------------------
// ADCON3: A/D Control Register 3
// -------------------------------
/*

	bit 15-13 Unimplemented: Read as ‘0’

	bit 12-8 SAMC<4:0>: Auto-Sample Time bits
		11111 = 31 TAD
		·····
		00001 = 1 TAD
		00000 = 0 TAD (only allowed if performing sequential conversions using more than one S/H amplifier)

	bit 7 ADRC: A/D Conversion Clock Source bit
		1 = A/D internal RC clock
		0 = Clock derived from system clock

	bit 6 Unimplemented: Read as ‘0’

	bit 5-0 ADCS<5:0>: A/D Conversion Clock Select bits
		111111 = TCY/2 • (ADCS<5:0> + 1) = 32 • TCY
		······
		000001 = TCY/2 • (ADCS<5:0> + 1) = TCY
		000000 = TCY/2 • (ADCS<5:0> + 1) = TCY/2
*/

// -------------------------------
// ADCHS: A/D Input Select Register
// -------------------------------
/*

	bit 15-14 CH123NB<1:0>: Channel 1, 2, 3 Negative Input Select for MUX B Multiplexer Setting bits
		Same definition as bits 6-7 (Note)

	bit 13 CH123SB: Channel 1, 2, 3 Positive Input Select for MUX B Multiplexer Setting bit
		Same definition as bit 5 (Note)

	bit 12 CH0NB: Channel 0 Negative Input Select for MUX B Multiplexer Setting bit
		Same definition as bit 4 (Note)

	bit 11-8 CH0SB<3:0>: Channel 0 Positive Input Select for MUX B Multiplexer Setting bits
		Same definition as bits 3-0 (Note)

	bit 7-6 CH123NA<1:0>: Channel 1, 2, 3 Negative Input Select for MUX A Multiplexer Setting bits
		11 = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11
		10 = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8
		0x = CH1, CH2, CH3 negative input is VREFbit
		5 CH123SA: Channel 1, 2, 3 Positive Input Select for MUX A Multiplexer Setting bit
		1 = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5
		0 = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2

	bit 4 CH0NA: Channel 0 Negative Input Select for MUX A Multiplexer Setting bit
		1 = Channel 0 negative input is AN1
		0 = Channel 0 negative input is VREFbit

	3-0 CH0SA<3:0>: Channel 0 Positive Input Select for MUX A Multiplexer Setting bits
		1111 = Channel 0 positive input is AN15
		1110 = Channel 0 positive input is AN14
		1101 = Channel 0 positive input is AN13
		||
		||
		||
		0001 = Channel 0 positive input is AN1
		0000 = Channel 0 positive input is AN0

Note: The analog input multiplexer supports two input setting configurations, denoted MUX A and MUX
B. ADCHS<15:8> determine the settings for MUX B, and ADCHS<7:0> determine the settings
for MUX A. Both sets of control bits function identically.
*/


// ---------------------------------------
// ADPCFG: A/D Port Configuration Register
// ---------------------------------------
/*
	bit 15-0 PCFG<15:0>: Analog Input Pin Configuration Control bits
		1 = Analog input pin in Digital mode, port read input enabled, A/D input multiplexer input connected to AVSS
		0 = Analog input pin in Analog mode, port read input disabled, A/D samples pin voltage
*/

// ---------------------------------------
// ADCSSL: A/D Input Scan Select Register
// ---------------------------------------

/*
	bit 15-0 CSSL<15:0>: A/D Input Pin Scan Selection bits
		1 = Select ANx for input scan
		0 = Skip ANx for input scan
*/


// initialisation générique acquisition monovoie pour appel StartADCx()
void InitADCx(void)
 {
  ADPCFG = 0xFFFF;    // all PORTB = Digital 
  ADCSSL = 0X0000;	  // no input scan
  ADCON1 = 0x00E8;    // Pas d'autostart, Echantillonnage voies multiples simultanées, alignement droit non signé, module off
  ADCON2 = 0x0000;    // multiplexage off, un seul buffer 16 bits, interruption après chaque conversion, conversion sur channel 0 uniquement
  ADCON3 = 0x1F3F;    // 32 TCy pour horloge
                      // System Clock
					  // attente 31 TAD pour stabilisation.
  ADCHS = 0x0000;     // voie 0 par défaut
  
  IFS0bits.ADIF = 0;      // Adc int flag Off
  IEC0bits.ADIE = 0;      // Adc int Off
  ADCON1bits.ADON = 1;      // turn ADC ON
}



// initialisation acquisition monovoie (AN0)
void InitADC0(void)
 {

  ADPCFG = 0b1111111111111110;    // all PORTB = Digital(1), RB0 = analog(0) 
  
  ADCSSL = 0b0;				      // no input scan

// réglage des modes de conversion
  ADCON1 = 0b0000000011101000;   // Pas d'auto start du sample
								 // Echantillanage simultané
  								 // Compteur interne pour start conversion
                                 // alignement droit du résultat
                                 // module off

// réglage des entrées et sorties
// convertisseur
  ADCON2 = 0b0000000000000000 ; // Mode Multiplexage off
								 // Un seul buffer 16 mots
                                 // interruption aprés chaque conversion
							     // pas de double buffer
								 // conversion canal 0 (CH0)

// réglage des temps conversion
  ADCON3 = 0b0001111100111111;  // 32 TCy pour horloge.
								// System clck  
                                // Attente 31 TAD pour stabilisation

 // réglage des entrées bloqueur (échantillonneur)
  ADCHS = 0b0000000000000000;    // CH0=AN0

  IFS0bits.ADIF = 0;      // Adc int flag Off
  IEC0bits.ADIE = 0;      // Adc int Off
  ADCON1bits.ADON = 1;      // turn ADC ON





}

void InitADC0and1(void)
{
  ADPCFG = 0b1111111111111100;    // all PORTB = Digital(1), RB0 = analog(0) 
  
  ADCSSL = 0b0;				      // no input scan

// réglage des modes de conversion
  ADCON1 = 0b0000000011101000;   // Pas d'auto start du sample
								 // Echantillanage simultané
  								 // Compteur interne pour start conversion
                                 // alignement droit du résultat
                                 // module off

// réglage des entrées et sorties
// convertisseur
  ADCON2 = 0b0000001100000000 ; // Mode Multiplexage off
								 // Un seul buffer 16 mots
                                 // interruption aprés chaque conversion
							     // pas de double buffer
								 // conversion canal 1, 2, 3 et 4(CH0-3)

// réglage des temps conversion
  ADCON3 = 0b0001111100111111;  // 32 TCy pour horloge.
								// System clck  
                                // Attente 31 TAD pour stabilisation

 // réglage des entrées bloqueur (échantillonneur)
  ADCHS = 0b0000000000000000;    // CH0=CH1=AN0 et CH2=AN1, CH3=AN2

  IFS0bits.ADIF = 0;      // Adc int flag Off
  IEC0bits.ADIE = 0;      // Adc int Off
  ADCON1bits.ADON = 1;      // turn ADC ON



}


void InitADC0to3(void)
{
ADPCFG = 0b1111111111110000;    // all PORTB = Digital(1), RB0 = analog(0),RB1 = analog(1),RB2 = analog(2),RB3 = analog(3)  

ADCSSL = 0b0;				      // no input scan

// réglage des modes de conversion
ADCON1 = 0b0000000011101000;     // Pas d'auto start du sample
								 // Echantillanage simultané
  								 // Compteur interne pour start conversion
                                 // alignement droit du résultat
                                 // module off


// réglage des entrées et sorties
// convertisseur
  ADCON2 = 0b0000001100000000 ; // Mode Multiplexage off
								 // Un seul buffer 16 mots
                                 // interruption aprés chaque conversion
							     // pas de double buffer
								 // conversion canal 1, 2, 3 et 4(CH0-3)


// réglage des temps conversion
  ADCON3 = 0b0001111100111111;  // 32 TCy pour horloge.
								// System clck  
                                // Attente 31 TAD pour stabilisation


// réglage des entrées bloqueur (échantillonneur)
  ADCHS = 0b0000001100000011;    // CH1=AN0 et CH2=AN1, CH3=AN2, CH0=AN3

  IFS0bits.ADIF = 0;      // Adc int flag Off
  IEC0bits.ADIE = 0;      // Adc int Off
  ADCON1bits.ADON = 1;      // turn ADC ON


}




void InitADC4and5(void)
{
ADPCFG = 0b1111111111001111;    // all PORTB = Digital(1), RB3 = analog(3),RB4 = analog(4),

ADCSSL = 0b0;				      // no input scan

// réglage des modes de conversion
ADCON1 = 0b0000000011101000;     // Pas d'auto start du sample
								 // Echantillanage simultané
  								 // Compteur interne pour start conversion
                                 // alignement droit du résultat
                                 // module off


// réglage des entrées et sorties
// convertisseur
  ADCON2 = 0b0000001100000000 ; // Mode Multiplexage off
								 // Un seul buffer 16 mots
                                 // interruption aprés chaque conversion
							     // pas de double buffer
								 // conversion canal 1, 2, 3 et 4(CH0-3)


// réglage des temps conversion
  ADCON3 = 0b0001111100111111;  // 32 TCy pour horloge.
								// System clck  
                                // Attente 31 TAD pour stabilisation


// réglage des entrées bloqueur (échantillonneur)
  ADCHS = 0b0010000000100000;    // CH2=AN4 et CH3=AN5

  IFS0bits.ADIF = 0;      // Adc int flag Off
  IEC0bits.ADIE = 0;      // Adc int Off
  ADCON1bits.ADON = 1;      // turn ADC ON


}




void InitADC0Seq0to4(void)
 {

  ADPCFG = 0b1111111111100000;		// RB0 (AN0) à RB4 (AN4) en mode analogique, le reste du PORTB en numérique 
  ADCSSL = 0b0000000000011111;	 	// Input scan des pattes AN0 à AN4
  ADCON1 = 0b0000000011100000;		// réglage des modes de conversion
		   //5432109876543210			// Pas d'auto start du sample
		   						 		// Echantillanage simultané
  								 		// Compteur interne pour start conversion
                                 		// alignement droit du résultat
                                 		// module off
										// Samples multiple channels individually in sequence
  ADCON2 = 0b0000010000010100;		// réglage des entrées et sorties du convertisseur
		   //5432109876543210			// Scan inputs
		    	 						// Un seul buffer 16 mots
                                 		// Interrupts at the completion of conversion for each 5th sample/convert sequence
							     		// pas de double buffer
								 		// conversion canal 0 (CH0)
  ADCON3 = 0b0001111100111111;		// réglage des temps conversion
		   //5432109876543210   		// 32 TCy pour horloge.
										// System clck  
                                		// Attente 31 TAD pour stabilisation

  ADCHS = 0b0000000000000000;		// réglage des entrées bloqueur (échantillonneur)
      	  //5432109876543210   			// CH0=AN0
  IFS0bits.ADIF = 0;      			// Adc int flag Off
  IEC0bits.ADIE = 0;      			// Adc int Off
  ADCON1bits.ADON = 1;      		// turn ADC ON
}


void InitADC0Seq0to5(void)
 {

  ADPCFG = 0b1111111111000000;		// RB0 (AN0) à RB5 (AN5) en mode analogique, le reste du PORTB en numérique 
  ADCSSL = 0b0000000000111111;	 	// Input scan des pattes AN0 à AN5
  ADCON1 = 0b0000000011100000;		// réglage des modes de conversion
		   //5432109876543210			// Pas d'auto start du sample
		   						 		// Echantillanage simultané
  								 		// Compteur interne pour start conversion
                                 		// alignement droit du résultat
                                 		// module off
										// Samples multiple channels individually in sequence
  ADCON2 = 0b0000010000010100;		// réglage des entrées et sorties du convertisseur
		   //5432109876543210			// Scan inputs
		    	 						// Un seul buffer 16 mots
                                 		// Interrupts at the completion of conversion for each 5th sample/convert sequence
							     		// pas de double buffer
								 		// conversion canal 0 (CH0)
  ADCON3 = 0b0001111100111111;		// réglage des temps conversion
		   //5432109876543210   		// 32 TCy pour horloge.
										// System clck  
                                		// Attente 31 TAD pour stabilisation

  ADCHS = 0b0000000000000000;		// réglage des entrées bloqueur (échantillonneur)
      	  //5432109876543210   			// CH0=AN0
  IFS0bits.ADIF = 0;      			// Adc int flag Off
  IEC0bits.ADIE = 0;      			// Adc int Off
  ADCON1bits.ADON = 1;      		// turn ADC ON
}





unsigned int StartADCx(unsigned char num)
{
if(num>5) num=5;
ADPCFG = ~(1<<num);    		// bit num de port B analog.
ADCHSbits.CH0SA=num; 
ADCON1bits.SAMP = 1; 		// start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
							// after 31Tad go to conversion
while (!ADCON1bits.DONE);   // conversion done?
return ADCBUF0;

}


void StartADC0(unsigned int* ADCxValue0)
{
	ADCON1bits.SAMP = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	*ADCxValue0 = ADCBUF0; // yes then get ADC value
}


void StartADC0and1(unsigned int* ADCxValue0, unsigned int* ADCxValue1)
{
	ADCON1bits.SAMP = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	*ADCxValue0 = ADCBUF1; // yes then get ADC value
	*ADCxValue1 = ADCBUF2; // yes then get ADC value
}


void StartADC0to3(unsigned int* ADCxValue0, unsigned int* ADCxValue1,unsigned int* ADCxValue2,unsigned int* ADCxValue3)
{
	ADCON1bits.SAMP = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	*ADCxValue0 = ADCBUF1; // yes then get ADC value
	*ADCxValue1 = ADCBUF2; // yes then get ADC value
    *ADCxValue2 = ADCBUF3; // yes then get ADC value
	*ADCxValue3= ADCBUF0; // yes then get ADC value

}


void StartADC4and5(unsigned int* ADCxValue0, unsigned int* ADCxValue1)
{
	ADCON1bits.SAMP = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	*ADCxValue0 = ADCBUF2; // yes then get ADC value
	*ADCxValue1 = ADCBUF3; // yes then get ADC value
}


void StartADC0seq0to4(unsigned int* ADCxValue0, unsigned int* ADCxValue1, unsigned int* ADCxValue2, unsigned int* ADCxValue3, unsigned int* ADCxValue4)
{
	ADCON1bits.ASAM = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	ADCON1bits.ASAM = 0; // stop sampling then ...
	*ADCxValue0 = ADCBUF0; // yes then get ADC value
	*ADCxValue1 = ADCBUF1; // yes then get ADC value
    *ADCxValue2 = ADCBUF2; // yes then get ADC value
	*ADCxValue3 = ADCBUF3; // yes then get ADC value
	*ADCxValue4 = ADCBUF4; // yes then get ADC value
}

void StartADC0seq0to5(unsigned int* ADCxValue0, unsigned int* ADCxValue1, unsigned int* ADCxValue2, unsigned int* ADCxValue3, unsigned int* ADCxValue4, unsigned int* ADCxValue5)
{
	ADCON1bits.ASAM = 1; // start sampling then ...                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	// after 31Tad go to conversion
	while (!ADCON1bits.DONE); // conversion done?
	ADCON1bits.ASAM = 0; // stop sampling then ...
	*ADCxValue0 = ADCBUF0; // yes then get ADC value
	*ADCxValue1 = ADCBUF1; // yes then get ADC value
    *ADCxValue2 = ADCBUF2; // yes then get ADC value
	*ADCxValue3 = ADCBUF3; // yes then get ADC value
	*ADCxValue4 = ADCBUF4; // yes then get ADC value
	*ADCxValue5 = ADCBUF5; // yes then get ADC value
}
