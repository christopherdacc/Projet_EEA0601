#include <xc.h>
#include <stdio.h>
#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "periph_gen.h"
#include "periph_tmr.h"
#include "periph_pwm.h"
#include "LCDv3.h"
#include "fonctions_sup.h"

#define BUTTON1_PIN   PORTBbits.RB0  // Bouton 1 connecter a RB0
#define BUTTON2_PIN   PORTBbits.RB1  // Bouton 2 connecter a RB1
#define BUTTON3_PIN   PORTBbits.RB2  // Bouton 3 connecter a RB2

Menu menuPrinc,menuAction,menuParam,menuAffEtat,menuManuel,menuDetObs,menuPID,menuVitesse;
Menu *menuPrincptr=&menuPrinc,*menuActionptr,*menuParamptr,*menuAffEtatptr,*menuManuelptr,*menuDetObsptr,*menuPIDptr,*menuVitesseptr;

MenuItem menuItem1,menuItem2,menuItem3,menuItem4;
MenuItem *menuItem1ptr,*menuItem2ptr,*menuItem3ptr,*menuItem4ptr;

MenuValue *menuValue;



void initStructMenuItem(){
    //Menu Principale:
    menuPrincptr->root=NULL;
    menuPrincptr->title=NULL;
    //Menu Action:
    menuActionptr->root=menuPrincptr;
    menuActionptr->title=NULL;
    
    menuItem1ptr->label="Actions"; 
    menuItem2ptr->label="Parametre";
    menuItem3ptr->label="Aff. Etat";
    
    
    
}



void menu_principale(Keyboard *keyboard)
{
    int choix_men=0;
    int selector=0;
    int boucle_test=0;
    LCDClearDisplay();
    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XXXXX Menu XXXXX");
    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    delay_en_s(1);
    LCDClearDisplay();
    //boucle menu principale
    
    do{
        if (keyboard->enterState==1){
            choix_men+=1; delay_en_s(0.2);
        }
        else if (keyboard->upState==1){selector+=1;delay_en_s(0.2);}
        else if (keyboard->downState==1){selector-=1;delay_en_s(0.2);}
        
        
    }while(boucle_test==0);
    
    
    
    
    LCDClearDisplay();
    LCDWriteStr(" Configurations ");
    LCDGoto(1,0);
    LCDWriteStr("  Mises a Jour  ");
}


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


void delay_en_s(float time) {
    
    int looper;
    looper = time*1000;
    for (int i = 0; i < looper; i++) { // Each iteration waits for 10ms
        _wait10mus(100); // 100 * 10 µs = 1000 µs = 1 ms
    }
}