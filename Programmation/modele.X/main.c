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
#include "p30f4012.h"
#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "./lib/periph_gen.h"
#include "./lib/periph_tmr.h"
#include "./lib/periph_pwm.h"
#include "./lib/LCDv3.h"
#include "./lib/fonctions_sup.h"
#include "./lib/ticks.h"

/******************************************************************************/
/* Définition des équivalences                                                */
/******************************************************************************/

#define TIMEBASE (Fcy/1000)

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
#define CONTRAST 35 //0 pour faible et 63 pour max
Keyboard *myKeyboardptr;
Keyboard myKeyboard;


/******************************************************************************/
/* Routines d'interruptions                                                   */
/******************************************************************************/

void initCN(void)
{
    //tris deja fait
    CNEN1bits.CN2IE=1;
    CNEN1bits.CN3IE=1;
    CNEN1bits.CN4IE=1;
}

void CNInterruptEnable(void)
{
    IFS0bits.CNIF=0;   // RAZ flag interruption
    IEC0bits.CNIE=1;   // autorisation interruption 
}
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

/*----------------------------------------------------------------------------*/
/* Routine d'interruption du timer 3                                          */
/*----------------------------------------------------------------------------*/

void __attribute__(( __interrupt__ ,__auto_psv__ )) _CNInterrupt(void) {
    
    if(detect_button_press(1))
    {
        myKeyboardptr->upEdge=1;
        myKeyboardptr->upState=1;
    }
    else if(!detect_button_press(1))
    {
        myKeyboardptr->upEdge=0;
        myKeyboardptr->upState=0;
    }
    if(detect_button_press(2))
    {
        myKeyboardptr->downEdge=1;
        myKeyboardptr->downState=1;
    }
    else if(!detect_button_press(2))
    {
        myKeyboardptr->downEdge=0;
        myKeyboardptr->downState=0;
    }
    if(detect_button_press(3))
    {
        myKeyboardptr->enterEdge=1;
        myKeyboardptr->enterState=1;
    }
    else if(!detect_button_press(3))
    {
        myKeyboardptr->enterEdge=0;
        myKeyboardptr->enterState=0;
    }
  
    
    IFS0bits.CNIF=0;
}



// Fin du code de la routine d'interruption

/******************************************************************************/
/* Programme principal (main program)                                         */
/******************************************************************************/

//initialisation des pates RE0, RE1 et RE2 aux boutons 1, 2 et 3
#define BUTTON1_PIN   PORTBbits.RB0  // Bouton 1 connecter a RE0
#define BUTTON2_PIN   PORTBbits.RB1  // Bouton 2 connecter a RE1
#define BUTTON3_PIN   PORTBbits.RB2  // Bouton 3 connecter a RE2

//fonction d'initialisation des pins RE0, RE1, RE2
void init_pins() {
    TRISBbits.TRISB0 = 1; // Configure RE0 comme une entree du bouton 1
    TRISBbits.TRISB1 = 1; // Configure RE1 comme une entree du bouton 2
    TRISBbits.TRISB2 = 1; // Configure RE2 comme une entree du bouton 3
    //les 3 lignes de code suivantes sont utiliser pour activer les pull up resistors pour RE0, RE1 et RE2
    CNPU1bits.CN2PUE = 1;       // Enable pull-up resistor for RB0
    CNPU1bits.CN3PUE = 1;       // Enable pull-up resistor for RB1
    CNPU1bits.CN4PUE = 1;       // Enable pull-up resistor for RB2  
}

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
    initTime();
    init_pins();                        //initialisation des pins
    InitLCD();                          //initialisation de l'ecran
    LCDDisplayOn();                     //on allume l'ecran
    LCDContrastSet(CONTRAST);           //on defini la luminosite avec contrast 
    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XX Demarrage! XX");
    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    delay_en_s(1);                         //pause de 5s    
    int xxx=1;
    //fonction de declanchement de l'interface du menu
    
    //fin de la fonction menu
    
     //debut init de l'interruption de CN
    initCN();
    IFS0bits.CNIF=0;
    CNInterruptEnable();
    myKeyboardptr=&myKeyboard;
    menu_principale(myKeyboardptr);
     //fin init de l'interruption de CN
    LCDClearDisplay();
    
    do{                                 //boucle d'initiation de test
        Time tm7 = getTime();
        while (myKeyboardptr->enterEdge==1)
        {
            LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("Button 1 = 1");
        }
        while (myKeyboardptr->upEdge==1 && myKeyboardptr->downEdge==1){
            LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("XXXXXXXX");
            LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("XXXXXXXX");
            LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("XXXXXXXX");
        }
        while (myKeyboardptr->downEdge==1)
        {
            LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("Button 2 = 1");
        }  
        while (myKeyboardptr->upEdge==1)
        { 
            LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("Button 3 = 1");
            
            while(isTimeOver(tm7,2000)&&detect_button_press(1)){
                LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr("Button 3 = 2");     
            }   
        }
        while(myKeyboardptr->downEdge==0&&myKeyboardptr->upEdge==0&&myKeyboardptr->enterEdge==0)
        {
            LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
            LCDWriteStr("Button 1 = 0");
            LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
            LCDWriteStr("Button 2 = 0");
            LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
            LCDWriteStr("Button 3 = 0");
        }
        
      }while(xxx==1);
    
    LCDClearDisplay();
    LCDWriteStr(" Configurations ");
    LCDGoto(1,0);
    LCDWriteStr("  Mises a Jour  ");
    
 
    while(1)
    {
    }
}



//watch this for simulations
//https://www.youtube.com/watch?v=O4IpwgWhqLY&ab_channel=BinderTronics
