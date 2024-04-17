#include <xc.h>

#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "periph_gen.h"
#include "periph_tmr.h"
#include "periph_pwm.h"
#include "LCDv3.h"
#include "fonctions_sup.h"
#include "ticks.h"

#define OPERATION(moyenne) moyenne%3

#define BUTTON1_PIN   PORTBbits.RB0  // Bouton 1 connecter a RB0
#define BUTTON2_PIN   PORTBbits.RB1  // Bouton 2 connecter a RB1
#define BUTTON3_PIN   PORTBbits.RB2  // Bouton 3 connecter a RB2
void menu_principale(Keyboard *keyboard)
{
    initTime();
    int choix_men=0;
    int exiter=0;
    long int moyenne=201;
    int distance=5;
    LCDClearDisplay();
    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XXXXX Menu XXXXX");
    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    delay_en_s(1);
    LCDClearDisplay();
    int damenu=0;
    //boucle menu principale
    //operation=OPERATION(moyenne);
    do{
        exiter=0;
        do{
            if(keyboard->enterEdge==1){choix_men+=1;delay_en_s(0.2);}
            else if(keyboard->downEdge==1){moyenne+=1;delay_en_s(0.2);}
            else if(keyboard->upEdge==1){moyenne-=1;delay_en_s(0.2);}
            else if(OPERATION(moyenne)==0)
            {
                LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(">Actions");
                LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(" Parametres");
                LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(" Aff. Etat");
            }
            else if (OPERATION(moyenne)==1)
            {
                LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(" Actions");
                LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(">Parametres");
                LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(" Aff. Etat");
            }
            else if (OPERATION(moyenne)==2)
            {
                LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(" Actions");
                LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(" Parametres");
                LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(">Aff. Etat");
            } 
        }while(choix_men==0);
        LCDClearDisplay();
        if(OPERATION(moyenne)==0)                            //Action
        {
            moyenne = 201;
            do{
                if(keyboard->enterEdge==1){choix_men+=1;}
                else if(keyboard->downEdge==1){moyenne+=1;delay_en_s(0.2);}
                else if(keyboard->upEdge==1){moyenne-=1;delay_en_s(0.2);}
                else if (OPERATION(moyenne)==0)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(">Marche Lente");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Marche Rapide");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Mode Manuel");
                }
                else if  (OPERATION(moyenne)==1)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(" Marche Lente");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">Marche Rapide");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Mode Manuel");
                }
                else if (OPERATION(moyenne)==2)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(" Marche Lente");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Marche Rapide");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">Mode Manuel");
                }
                
                if(keyboard->upEdge==1 && keyboard->downEdge==1)
                {
                    choix_men=choix_men-1;
                    if (choix_men==0){choix_men=0;}
                    LCDClearDisplay();
                }

            }while(choix_men==1);
        }
        else if (OPERATION(moyenne)==1)                  //Parametres
        {
            moyenne = 201;
            do{ 
                if(keyboard->enterEdge==1){choix_men+=1;delay_en_s(0.2);}
                else if(keyboard->downEdge==1){moyenne+=1;delay_en_s(0.2);}
                else if(keyboard->upEdge==1){moyenne-=1;delay_en_s(0.2);}
                else if (OPERATION(moyenne)==0)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(">Detection Obs");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Reglage PID");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Vitesse");
                }
                else if (OPERATION(moyenne)==1)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(" Detection Obs");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">Reglage PID");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Vitesse");
                }
                else if (OPERATION(moyenne)==2)
                {
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(" Detection Obs");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" Reglage PID");
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">Vitesse");
                }
              
                if (keyboard->upEdge==1 && keyboard->downEdge==1)
                {
                    choix_men-=1;
                    if (choix_men==0){choix_men=0;}
                    LCDClearDisplay();
                }

            }while(choix_men==1);
            moyenne = 201;
            LCDClearDisplay();
            if (OPERATION(moyenne)==0){
                
                do{
                    if(keyboard->enterEdge==1){choix_men+=1;delay_en_s(0.2);}
                    else if(keyboard->downEdge==1){distance+=1;delay_en_s(0.2);}
                    else if(keyboard->upEdge==1){distance-=1;delay_en_s(0.2);}
                    
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr("[Detection Obs]");
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr("Dis: ");
                    LCDDataWrite(distance);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr("Enter: Retour");
                    
                    
                }while(choix_men==2);
            }
            
        }
        
        else if (OPERATION(moyenne)==2)              //Affich etat
        {
            do{
                if (exiter==0){
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("Distance obs");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Dist: ");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Exit");
                        exiter++;
                    Time tm = getTime();
                    while(!isTimeOver(tm,2000)){
                        if (keyboard->enterEdge==1){
                            choix_men=0;
                            exiter=10;
                        }
                    };
                    LCDClearDisplay();
                }
                else if (exiter==1){
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("Vit. Moteurs");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("G:  % D:  %");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Exit");
                        exiter++;
                    Time tm1 = getTime();
                    while(!isTimeOver(tm1,2000)){
                        if (keyboard->enterEdge==1){
                            choix_men=0;
                            exiter=10;
                        }
                    };
                    LCDClearDisplay();
                }
                else if (exiter==2){
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("Com. Moteurs");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("G:  % D:  %");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Exit");
                        exiter++;
                    Time tm2 = getTime();
                    while(!isTimeOver(tm2,2000)){
                        if (keyboard->enterEdge==1){
                            choix_men=0;
                            exiter=10;
                        }
                    };
                    LCDClearDisplay();
                }
                else if (exiter==3){
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("Capteur IR");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("00X00 : +00");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Exit");
                        exiter=0;
                    Time tm3 = getTime();    
                    while(!isTimeOver(tm3,2000)){
                        if (keyboard->enterEdge==1){
                            choix_men=0;
                            exiter=10;
                        }
                    };
                    LCDClearDisplay();
                }
                else{
                    choix_men=0;
                }
            }while(choix_men==1);
            
        }
        
    }while(choix_men<3);
    
    
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