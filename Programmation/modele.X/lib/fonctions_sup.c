#include <xc.h>
#include <stdio.h>
#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "periph_gen.h"
#include "periph_tmr.h"
#include "periph_pwm.h"
#include "LCDv3.h"
#include "fonctions_sup.h"
#include "ticks.h"

#define OPERATION(moyenne) moyenne%3
#define OPERATION2(distcount) distcount%10
#define OPERATION3(moyenne) moyenne%4

#define ACTIONS "Actions        "
#define PARAMETRES "Parametres     "
#define AFFETAT "Aff. Etat      "
#define MALENTE "Marche Lente   "
#define MARAPIDE "Marche Rapide  "
#define MOMANUEL "Mode Manuel    "
#define RETOUR "Retour         "
#define DEOBST "Detection Obst"
#define REGPID "Reglage PID"
#define VITESSE "Vitesse"
#define GAUCHE "Gauche"
#define DROITE "Droite"

#define BUTTON1_PIN   PORTBbits.RB0  // Bouton 1 connecter a RB0
#define BUTTON2_PIN   PORTBbits.RB1  // Bouton 2 connecter a RB1
#define BUTTON3_PIN   PORTBbits.RB2  // Bouton 3 connecter a RB2


int gauche=0,droite=0,regP=0,regI=0,regD=0,distObs=0,maxG=0,maxD=0;
int *distObsptr=&distObs,*regPptr=&regP,*regIptr=&regP,*regDptr=&regD,*maxGptr=&maxG,*maxDptr=&maxD;
Menu rootMenu,actionMenu,paramMenu,affetatMenu,manuMenu,detecMenu,PIDMenu,vitMenu;


void menu_principale(Keyboard *keyboard)
{
    initTime();
    int choix_men=0;
    int exiter=0;
    int savedist1=0;
    int savedist2=0;
    char distance[100] = {'0','1','2','3','4','5','6','7','8','9'}; 
    int distcount=0, Pcount=0, Dcount=0, Icount=0, rapidecount=0, lentcount=0;
    //testing start
    MenuValue manuValue[]={{0,0,0,100,0},{0,0,0,100,0}};
    MenuValue distValue[]={{0,0,0,100,1}};
    MenuValue pidValue[]={{0,0,0,100,1},{0,0,0,100,1},{0,0,0,100,1}};
    MenuValue viteValue[]={{0,0,0,100,1},{0,0,0,100,1}};
    // déclarer les items
    MenuItem rootItems []={{ACTIONS,&actionMenu,2,0},{PARAMETRES,&paramMenu,2,0},{AFFETAT,&affetatMenu,2,0}};
    MenuItem actionItems []={{MALENTE,NULL,1,1},{MARAPIDE,NULL,1,1},{MOMANUEL,&manuMenu,2,0},{RETOUR,&rootMenu,2,0}};
    MenuItem paramItems []={{DEOBST,&detecMenu,2,0},{REGPID,&PIDMenu,2,0},{VITESSE,&vitMenu,2,0},{RETOUR,&rootMenu,2,0}};
    MenuItem manuItems []={{GAUCHE,manuValue,3,0},{DROITE,manuValue,3,0},{RETOUR,&actionMenu,2,0}};
    MenuItem detObsItems[]={{"Dist: ",distValue,3,0},{RETOUR,&paramMenu,2,0}};
    MenuItem PIDItems[]={{"P: ",pidValue,3,0},{"I: ",pidValue,3,0},{"D: ",pidValue,3,0},{RETOUR,&paramMenu,2,0}};
    MenuItem vitItems[]={{"Rapide: ",viteValue,3,0},{"Lent: ",viteValue,3,0},{RETOUR,&paramMenu,2,0}};
    // déclarer les menus
    //Menu Principale
    rootMenu.title = NULL;
    rootMenu.root =NULL;
    rootMenu.items = rootItems;
    rootMenu.selected = 0;
    rootMenu.offset = 0;
    //Menu Action
    actionMenu.title = NULL;
    actionMenu.root = &rootMenu;
    actionMenu.items = actionItems;
    actionMenu.selected = 0;
    actionMenu.offset = 0;
    //Menu Parametres
    paramMenu.title = NULL;
    paramMenu.root = &rootMenu;
    paramMenu.items = paramItems;
    paramMenu.selected = 0;
    paramMenu.offset = 0;
    //Menu Affiche Etat
    affetatMenu.title = NULL;
    affetatMenu.root = &rootMenu;
    //affetatMenu.items = ;
    affetatMenu.selected = 0;
    affetatMenu.offset = 0;
    //Menu Mode Manuel
    manuMenu.title = "[Manuel]";
    manuMenu.root = &actionMenu;
    manuMenu.items = manuItems;
    manuMenu.selected = 0;
    manuMenu.offset = 0;
    //Menu Detection Obstacles
    detecMenu.title = "[Detec. Obs.]";
    detecMenu.root = &paramMenu;
    detecMenu.items = detObsItems;
    detecMenu.selected = 0;
    detecMenu.offset = 0;
    //Menu PID
    PIDMenu.title = "[Reglage PID]";
    PIDMenu.root = &paramMenu;
    PIDMenu.items = PIDItems;
    PIDMenu.selected = 0;
    PIDMenu.offset = 0;
    //Menu Vitesse
    vitMenu.title = "[Vitesse]";
    vitMenu.root = &paramMenu;
    vitMenu.items = vitItems;
    vitMenu.selected = 0;
    vitMenu.offset = 0;
    //testin end
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
    //operation=OPERATION(moyenne);
    do{
        
        exiter=0;
        do{
            if(keyboard->enterEdge==1){choix_men+=1;delay_en_s(0.2);}
            else if(keyboard->downEdge==1){
                rootMenu.selected+=1;
                if (rootMenu.selected>2){
                    rootMenu.selected=0;
                }
                delay_en_s(0.2);
            }
            else if(keyboard->upEdge==1){
                rootMenu.selected-=1;
                if (rootMenu.selected<0){
                    rootMenu.selected=2;
                }
                delay_en_s(0.2);
            }
            else if(rootMenu.selected==0)
            {
                LCDGoto(0,0);
                LCDWriteStr(">");
                LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(rootItems[0].label);
                LCDGoto(1,0); 
                LCDWriteStr(" ");
                LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[1].label);
                LCDGoto(2,0); 
                LCDWriteStr(" ");
                LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[2].label);
            }
            else if (rootMenu.selected==1)
            {
                LCDGoto(0,0); 
                LCDWriteStr(" ");
                LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(rootItems[0].label);
                LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(">");
                LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[1].label);
                LCDGoto(2,0); 
                LCDWriteStr(" ");
                LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[2].label);
            }
            else if (rootMenu.selected==2)
            {
                LCDGoto(0,0); 
                LCDWriteStr(" ");
                LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                LCDWriteStr(rootItems[0].label);
                LCDGoto(1,0); 
                LCDWriteStr(" ");
                LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[1].label);
                LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(">");
                LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                LCDWriteStr(rootItems[2].label);
            } 
        }while(choix_men==0);
        LCDClearDisplay();
        
        if(rootMenu.selected==0)                            //Action
        {
            do{
                if(keyboard->enterEdge==1){
                    if (actionMenu.selected==3){
                        actionMenu.selected=0;
                        choix_men=0;
                        delay_en_s(0.2);
                    }
                    else {
                        choix_men+=1;
                        delay_en_s(0.2);
                    } 
                }
                else if(keyboard->downEdge==1){
                    actionMenu.selected+=1;
                    if (actionMenu.selected>3){
                        actionMenu.selected=0;
                    }
                    delay_en_s(0.2);
                }
                else if(keyboard->upEdge==1){
                    actionMenu.selected-=1;
                    if (actionMenu.selected<0){
                        actionMenu.selected=3;
                    }
                    delay_en_s(0.2);
                }
                else if (actionMenu.selected==0)
                {
                    actionMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(">");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(actionItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(actionItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[2].label);
                }
                else if  (actionMenu.selected==1)
                {
                    actionMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(actionItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[2].label);
                }
                else if (actionMenu.selected==2)
                {
                    actionMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(actionItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[2].label);
                }
                else if (actionMenu.selected==3)
                {
                    actionMenu.offset=1;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(actionItems[1].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[2].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(actionItems[3].label);
                }
                
            }while(choix_men==1);
            choix_men=0;
        }
        else if (rootMenu.selected==1)                  //Parametres
        {
            do{ 
                if(keyboard->enterEdge==1){
                    if (paramMenu.selected==3){
                        paramMenu.selected=0;
                        choix_men=0;
                        delay_en_s(0.2);
                    }
                    else {
                        choix_men+=1;
                        delay_en_s(0.2);
                    }
                }
                else if(keyboard->downEdge==1){
                    paramMenu.selected+=1;
                    if (paramMenu.selected>3){
                        paramMenu.selected=0;
                    }
                    delay_en_s(0.2);
                }
                else if(keyboard->upEdge==1){
                    paramMenu.selected-=1;
                    if (paramMenu.selected<0){
                        paramMenu.selected=3;
                    }
                    delay_en_s(0.2);
                }
                else if (paramMenu.selected==0)
                {
                    paramMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(">");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(paramItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(paramItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[2].label);
                }
                else if (paramMenu.selected==1)
                {
                    paramMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(paramItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[2].label);
                }
                else if (paramMenu.selected==2)
                {
                    paramMenu.offset=0;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(paramItems[0].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[1].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[2].label);
                }
                else if (paramMenu.selected==3)
                {
                    paramMenu.offset=1;
                    LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(0,1);                       //Commence a ecrire sur l'ecran a la case 0,0
                    LCDWriteStr(paramItems[1].label);
                    LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(" ");
                    LCDGoto(1,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[2].label);
                    LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(">");
                    LCDGoto(2,1);                       //Commence a ecrire sur l'ecran a la case 1,0
                    LCDWriteStr(paramItems[3].label);
                }
                
            }while(choix_men==1);
            
            if (paramMenu.selected==0){
                do{
                    if(keyboard->enterEdge==1){LCDClearDisplay();choix_men-=1;delay_en_s(0.2);}
                    else if(keyboard->downEdge==1){distcount-=1;delay_en_s(0.2);}
                    else if(keyboard->upEdge==1){distcount+=1;delay_en_s(0.2);}
                    if (distcount<0){
                        LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("!Warning No Neg!");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("  !!!Values!!!  ");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("                ");
                        delay_en_s(1.5);
                        distcount=0;
                    }
                    else if (distcount<10){
                        LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("[Detection Obs] ");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Dis:            ");
                        LCDGoto(1,5);
                        LCDDataWrite(distance[distcount]);
                        LCDGoto(1,8);
                        LCDWriteStr("cm       ");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Retour");
                    }
                    
                    else if (distcount>9){
                        LCDGoto(0,0);                       //Commence a ecrire sur l'ecran a la case 0,0
                        LCDWriteStr("[Detection Obs] ");
                        LCDGoto(1,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Dis: ");
                        savedist1=distcount/10;
                        savedist2 = OPERATION2(distcount);
                        LCDGoto(1,5);
                        LCDDataWrite(distance[savedist1]);
                        LCDGoto(1,6);
                        LCDDataWrite(distance[savedist2]);
                        LCDGoto(1,8);
                        LCDWriteStr("cm       ");
                        LCDGoto(2,0);                       //Commence a ecrire sur l'ecran a la case 1,0
                        LCDWriteStr("Enter: Retour");
                    }
                      
                }while(choix_men==2);
            }
            
        }
            else if (rootMenu.selected==2)              //Affich etat
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
                choix_men=0;
            }
            
            LCDClearDisplay();
            
            
           
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

