/*============================================================================*/
/* Programme de test de la carte microcontrôleur dspic30f4012                 */
/* ----------------------------------------------------------                 */
/* Environnement : IDE : MPLAX X                                              */
/*                 Compilateur C : XC16                                       */
/* Le programme :                                                             */
/*   - utilise un mécanisame d'interruption lié au timer 3 pour faire         */
/*     osciller la patte RB0 du port B ;                                      */
/*   - utilise le module PWM pour générer un signal impulsion sur la patte    */
/*      RE0 du port E.                                                        */
/*                                                                            */
/* 2023.02.08                                                                 */
/* DRHC & MC                                                     */
/*============================================================================*/

/******************************************************************************/
/* DSPIC30F4012 Configuration Bit Settings                                    */
/******************************************************************************/

// FOSC
#pragma config FPR = XT_PLL16          // Primary Oscillator Mode (XT w/PLL 16x)
#pragma config FOS = PRI               // Oscillator Source (Primary Oscillator)
#pragma config FCKSMEN = CSW_FSCM_OFF  // Clock Switching and Monitor (Sw 
                                       // Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active 
                                        // High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active
                                        // High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with 
                                        // PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect 
                                        // (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection 
                                        // (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and
                                        // PGD/EMUD)

// #pragma config statements should precede project file includes.


/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#include <xc.h>

#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "./lib/periph_gen.h"
#include "./lib/periph_tmr.h"
#include "./lib/periph_pwm.h"
#include "./lib/LCDv3.h"

/******************************************************************************/
/* Définition des équivalences                                                */
/******************************************************************************/

#define TIMEBASE (Fcy/1000)

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/


/******************************************************************************/
/* Routines d'interruptions                                                   */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Routine d'interruption du timer 3                                          */
/*----------------------------------------------------------------------------*/

void __attribute__((__interrupt__,no_auto_psv)) _T3Interrupt( void )
{
  // Déclaration des variables de la routine d'interruption
  // Par exemple : static unsigned int i = 0;

  // Code de la routine d'interruption
  PORTBbits.RB0 = ~PORTBbits.RB0;  
    
  // Acquitement de l'interruption
  IFS0bits.T3IF=0;  //raz flag

} // Fin du code de la routine d'interruption


/******************************************************************************/
/* Programme principal (main program)                                         */
/******************************************************************************/

//chat gpt code 1
#define BUTTON1_PIN   PORTEbits.RE0  // Button 1 connected to RE0
#define BUTTON2_PIN   PORTEbits.RE1  // Button 2 connected to RE1
#define BUTTON3_PIN   PORTEbits.RE2  // Button 3 connected to RE2
//end chat gpt code 1
//chat gpt code 2
void init_pins() {
    TRISEbits.TRISE0 = 1; // Configure RE0 as an input for button 1
    TRISEbits.TRISE1 = 1; // Configure RE1 as an input for button 2
    TRISEbits.TRISE2 = 1; // Configure RE2 as an input for button 3
    //LATEbits.LATE0 = 1;   // Enable pull-up resistor for RE0
    //LATEbits.LATE1 = 1;   // Enable pull-up resistor for RE1
    //LATEbits.LATE2 = 1;   // Enable pull-up resistor for RE2
}
//end chat gpt code 2
//chat gpt code 3
int detect_button_press(int button) {
    switch(button) {
        case 1:
            return !BUTTON1_PIN; // If pin RE0 is low, then button 1 is pressed
        case 2:
            return !BUTTON2_PIN; // If pin RE1 is low, then button 2 is pressed
        case 3:
            return !BUTTON3_PIN; // If pin RE2 is low, then button 3 is pressed
        default:
            return 0; // Invalid button number
    }
}
//end chat gpt code 3

int16_t main(void)
{
    /* -----------------------------------------------------------------------*/
    /* Configurations (notamment des périphériques)                           */
    /* -----------------------------------------------------------------------*/

    // Configuration du port B
    ADPCFG = 0xFFFF;     // Configuration des pattes du port B comme entrées
                         // sorties numériques (par défaut entrées analogiques)
    TRISB = 0b11111110;  // Initialisation de la patte RB0 du port B en sortie, 
                         // les autres en entrées 
    PORTB = 0;           // Mise à zéro des pattes en sorties du port B
    
    //Configurqtion du port E
    
    
    
    // Initialisation timer 3 - interruption à la milliseconde
    //InitTimer3(TIMEBASE);    // Initialisation du timer 3
   // Timer3InterruptEnable(); // Autorisation de l'interruption liée au timer 3

    // Initialisation de la PWM : 1ms
    //InitPWM(461,PEN1L);  // Initialisation du module PWM      
    //PWMEnable(ON);       // Mise en route de la PWM
    //PWM1PulseWidth(115); // Réglage du rapport cyclique
    
    /* -----------------------------------------------------------------------*/
    /* Code principal de l'application                                                  */
    /* -----------------------------------------------------------------------*/
    init_pins();
    InitLCD();
 
    
    LCDDisplayOn();
    
    char chainedechar[] = "Bonjour le monde!!";         //affichage de bonjour le monde lentement
    for (int i=0;i<18;i++){
        _wait10mus(300000);
        LCDDataWrite(chainedechar[i]);
    }
    
    while(1) {
        if(detect_button_press(1)||detect_button_press(2)||detect_button_press(3)) {
            if(detect_button_press(1))
            {
                LCDGoto(0,0);
                LCDWriteStr("Button 0 = X");
                _wait10mus(300000);
            }
            if(detect_button_press(2))
            {
                LCDGoto(1,0);
                LCDWriteStr("Button 1 = X");
                _wait10mus(300000);
            }
            if(detect_button_press(3))
            {
                LCDGoto(2,0);
                LCDWriteStr("Button 2 = X");
                _wait10mus(300000);
            }
            
            
        }
        else if(!detect_button_press(1)||!detect_button_press(2)||!detect_button_press(3)) {
            LCDClearDisplay();
            LCDGoto(0,0);
            LCDWriteStr("Button 0 = 0");
            LCDGoto(1,0);
            LCDWriteStr("Button 1 = 0");
            LCDGoto(2,0);
            LCDWriteStr("Button 2 = 0");
            
            _wait10mus(300000);
        }
    }
    
    while(1)
    {
        
    }
    
}
