#include "p30f4012.h"
#include "dsp.h"
#include "periph_adc_2.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la conversion AN
*
*                     D. CARTON, M. COLAS
*                      V 1.3 - Mars 2015
*                     (V 1.2 - Mars 2008)
************************************************************
***********************************************************/





// The SSRC<2:0>, ASAM, SIMSAM,
// SMPI<3:0>, BUFM and ALTS bits, as well
// as the ADCON3 and ADCSSL registers,
// must not be written to while ADON = 1.
// This would lead to indeterminate results.



// initialisation acquisition monovoie (AN0)
void InitADCChoice0toN(unsigned int N) {

  ADPCFG = 0b1111111111111111<<(N+1); // All PORTB = Digital(1), except RB0 to RBN = analog(0) 
                                      //
                                      // ADPCFG : A/D Port Configuration Register
                                      // ----------------------------------------
                                      // bit 15-0 : PCFG<15:0>: Analog Input Pin Configuration Control bits
                                      //             1 = Analog input pin in Digital mode, port read input enabled, 
                                      //                 A/D input multiplexer input connected to AV SS
                                      //             0 = Analog input pin in Analog mode, port read input disabled,
                                      //                 A/D samples pin voltag                                 

  ADCSSL = 0b0000000000000000;        // No input scan
                                      //
                                      // ADCSSL: A/D Input Scan Select Register
                                      // --------------------------------------
                                      // bit 15-0 : CSSL<15:0>: A/D Input Pin Scan Selection bits
                                      //             1 = Select ANx for input scan
                                      //             0 = Skip ANx for input scan
  // Réglage des modes de conversion
	ADCON1 = 0b0000000011101000;        // Pas d'auto start du sample
									                    // Échantillonnage simultané
									                    // Compteur interne pour start conversion
									                    // alignement droit du résultat
									                    // module off
                                      // ADON = 0; ADSIDL = 0; FORM = 00; SSRC  = 111; SISAM = 1; ASAM = 0; SAMP = 0; 

                                      // ADCON1 : A/D Control Register 1
                                      // -------------------------------
                                      // bit 15    : ADON: A/D Operating Mode bit
                                      //              1 = A/D converter module is operating
                                      //              0 = A/D converter is off
                                      // bit 14    : Unimplemented: Read as ‘0’
                                      // bit 13    : ADSIDL: Stop in Idle Mode bit
                                      //              1 = Discontinue module operation when device enters Idle mode
                                      //              0 = Continue module operation in Idle mode
                                      // bit 12-10 : Unimplemented: Read as ‘0’
                                      // bit 9-8   : FORM<1:0>: Data Output Format bits
                                      //               11 = Signed Fractional (DOUT = sddd dddd dd00 0000)
                                      //               10 = Fractional (DOUT = dddd dddd dd00 0000)
                                      //               01 = Signed Integer (DOUT = ssss sssd dddd dddd)
                                      //               00 = Integer (DOUT = 0000 00dd dddd dddd)
                                      // bit 7-5   : SSRC<2:0>: Conversion Trigger Source Select bits
                                      //              111 = Internal counter ends sampling and starts conversion (auto convert)
                                      //              110 = Reserved
                                      //              101 = Reserved
                                      //              100 = Reserved
                                      //              011 = Motor Control PWM interval ends sampling and starts conversion
                                      //              010 = GP Timer3 compare ends sampling and starts conversion
                                      //              001 = Active transition on INT0 pin ends sampling and starts conversion
                                      //              000 = Clearing SAMP bit ends sampling and starts conversion
                                      // bit 4     : Unimplemented: Read as ‘0’
                                      // bit 3     : SIMSAM: Simultaneous Sample Select bit (only applicable when CHPS = 01 or 1x)
                                      //              1 = Samples CH0, CH1, CH2, CH3 simultaneously (when CHPS = 1x)
                                      //              or
                                      //              Samples CH0 and CH1 simultaneously (when CHPS = 01)
                                      //              0 = Samples multiple channels individually in sequence
                                      // bit 2     : ASAM: A/D Sample Auto-Start bit
                                      //              1 = Sampling begins immediately after last conversion completes. SAMP bit is auto set
                                      //              0 = Sampling begins when SAMP bit set                                    
                                      // bit 1     : SAMP: A/D Sample Enable bit
                                      //              1 = At least one A/D sample/hold amplifier is sampling
                                      //              0 = A/D sample/hold amplifiers are holding
                                      //              When ASAM = 0, writing ‘1’ to this bit will start sampling
                                      //              When SSRC = 000, writing ‘0’ to this bit will end sampling and start conversion
                                      // bit 0     : DONE: A/D Conversion Status bit (Rev. B silicon or later)
                                      //              1 = A/D conversion is done
                                      //              0 = A/D conversion is NOT done
                                      //              Cleared by software or start of a new conversion
                                      //              Clearing this bit will not effect any operation in progress                                      
                                      
	// Réglage des entrées et sorties
	// convertisseur
	ADCON2 = 0b0000000000000000 ;       // Mode Multiplexage off
								                      // Un seul buffer 16 mots
                                      // interruption après chaque conversion (???)
							                        // pas de double buffer
								                      // conversion canal 0 (CH0)

                                      // ADCON2: A/D Control Register 2
                                      // ------------------------------
                                      // bit 15-13 : VCFG<2:0>: Voltage Reference Configuration bits
                                      //                  |--------------------|---------------------|
                                      //                  |      A/D VREFH     |      A/D VREF L     |
                                      //                  |--------------------|---------------------|
                                      //              000 |        AVDD        |         AVSS        |
                                      //              001 | External VREF+ pin |         AVSS        |
                                      //              010 |        AVDD        | External VREF - pin |
                                      //              011 | External VREF+ pin | External VREF - pin |
                                      //              1XX |        AVDD        |         AVSS        |
                                      //                  |--------------------|---------------------|
                                      // bit 12    : Reserved: User should write ‘0’ to this location
                                      // bit 11    : Unimplemented: Read as ‘0’
                                      // bit 10    : CSCNA: Scan Input Selections for CH0+ S/H Input for MUX A Input Multiplexer Setting bit
                                      //              1 = Scan inputs
                                      //              0 = Do not scan inputs
                                      // bit 9-8   : CHPS<1:0>: Selects Channels Utilized bits
                                      //              1x = Converts CH0, CH1, CH2 and CH3
                                      //              01 = Converts CH0 and CH1
                                      //              00 = Converts CH0
                                      //              When SIMSAM bit (ADCON1<3>) = 0 multiple channels sampled sequentially
                                      //              When SMSAM bit (ADCON1<3>) = 1 multiple channels sampled as in CHPS<1:0>
                                      // bit 7     : BUFS: Buffer Fill Status bit
                                      //              Only valid when BUFM = 1 (ADRES split into 2 x 8-word buffers).
                                      //              1 = A/D is currently filling buffer 0x8-0xF, user should access data in 0x0-0x7
                                      //              0 = A/D is currently filling buffer 0x0-0x7, user should access data in 0x8-0xF
                                      // bit 6     : Unimplemented: Read as ‘0’
                                      // bit 5-2   : SMPI<3:0>: Sample/Convert Sequences Per Interrupt Selection bits
                                      //              1111 = Interrupts at the completion of conversion for each 16th sample/convert sequence
                                      //              1110 = Interrupts at the completion of conversion for each 15th sample/convert sequence
                                      //              .....
                                      //              0001 = Interrupts at the completion of conversion for each 2nd sample/convert sequence
                                      //              0000 = Interrupts at the completion of conversion for each sample/convert sequence
                                      // bit 1     : BUFM: Buffer Mode Select bit
                                      //              1 = Buffer configured as two 8-word buffers ADCBUF(15...8), ADCBUF(7...0)
                                      //              0 = Buffer configured as one 16-word buffer ADCBUF(15...0.)
                                      // bit 0     : ALTS: Alternate Input Sample Mode Select bit
                                      //              1 = Uses MUX A input multiplexer settings for first sample, then alternate between MUX B and MUX A input
                                      //              multiplexer settings for all subsequent samples
                                      //              0 = Always use MUX A input multiplexer settings

  // Réglage des temps conversion
	ADCON3 = 0b0001111100111111;        // 32 TCy pour horloge.
								                      // System clck  
                                      // Attente 31 TAD pour stabilisation
                                      // SAMC = 11111; ADRC = 0; ADCS = 111111;
                                      //
                                      // ADCON3 : A/D Control Register 3
                                      // -------------------------------
                                      // bit 15-13 : Unimplemented: Read as ‘0’
                                      // bit 12-8  : SAMC<4:0>: Auto-Sample Time bits
                                      //              11111 = 31 TAD
                                      //              ·····
                                      //              00001 = 1 TAD
                                      //              00000 = 0 TAD (only allowed if performing sequential conversions using more than one S/H amplifier)
                                      // bit 7     : ADRC: A/D Conversion Clock Source bit
                                      //              1 = A/D internal RC clock
                                      //              0 = Clock derived from system clock
                                      // bit 6     : Unimplemented: Read as ‘0’
                                      // bit 5-0   : ADCS<5:0>: A/D Conversion Clock Select bits
                                      //              111111 = TCY/2 • (ADCS<5:0> + 1) = 32 • TCY
                                      //              ······
                                      //              000001 = TCY/2 • (ADCS<5:0> + 1) = TCY
                                      //              000000 = TCY/2 • (ADCS<5:0> + 1) = TCY/2

  // réglage des entrées bloqueur (échantillonneur)
	ADCHS = 0b0000000000000000;         // CH0=AN0
                                      //
                                      // ADCHS : A/D Input Select Register
                                      // ---------------------------------
                                      // bit 15-14 : CH123NB<1:0>: Channel 1, 2, 3 Negative Input Select for MUX B Multiplexer Setting bits
                                      //              Same definition as bits 6-7 (Note)
                                      // bit 13    : CH123SB: Channel 1, 2, 3 Positive Input Select for MUX B Multiplexer Setting bit
                                      //              Same definition as bit 5 (Note)
                                      // bit 12    : CH0NB: Channel 0 Negative Input Select for MUX B Multiplexer Setting bit
                                      //              Same definition as bit 4 (Note)
                                      // bit 11-8  : CH0SB<3:0>: Channel 0 Positive Input Select for MUX B Multiplexer Setting bits
                                      //              Same definition as bits 3-0 (Note)
                                      // bit 7-6   : CH123NA<1:0>: Channel 1, 2, 3 Negative Input Select for MUX A Multiplexer Setting bits
                                      //              11 = CH1 negative input is AN9, CH2 negative input is AN10, CH3 negative input is AN11
                                      //              10 = CH1 negative input is AN6, CH2 negative input is AN7, CH3 negative input is AN8
                                      //              0x = CH1, CH2, CH3 negative input is VREF -
                                      // bit 5     : CH123SA: Channel 1, 2, 3 Positive Input Select for MUX A Multiplexer Setting bit
                                      //              1 = CH1 positive input is AN3, CH2 positive input is AN4, CH3 positive input is AN5
                                      //              0 = CH1 positive input is AN0, CH2 positive input is AN1, CH3 positive input is AN2
                                      // bit 4     : CH0NA: Channel 0 Negative Input Select for MUX A Multiplexer Setting bit
                                      //              1 = Channel 0 negative input is AN1
                                      //              0 = Channel 0 negative input is VREF-
                                      // bit 3-0   : CH0SA<3:0>: Channel 0 Positive Input Select for MUX A Multiplexer Setting bits
                                      //              1111 = Channel 0 positive input is AN15
                                      //              1110 = Channel 0 positive input is AN14
                                      //              1101 = Channel 0 positive input is AN13
                                      //              ······
                                      //              0001 = Channel 0 positive input is AN1
                                      //              0000 = Channel 0 positive input is AN0

  IFS0bits.ADIF = 0;                  // Adc int flag Off
	IEC0bits.ADIE = 0;                  // Adc int Off
	ADCON1bits.ADON = 1;                // turn ADC ON
}


void StartADCChoice0toN(unsigned int channel, unsigned int* ADCValue) {

	ADCHSbits.CH0SA = channel;      // réglage des entrées bloqueur (échantillonneur) 
	ADCON1bits.SAMP = 1;            // start sampling then after 31Tad go to conversion
	while (!ADCON1bits.DONE);       // conversion done?
	*ADCValue = ADCBUF0;            // yes then get ADC value

}

