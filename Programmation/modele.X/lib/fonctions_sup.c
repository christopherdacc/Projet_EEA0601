#include <xc.h>

#include <stdint.h>             /* Includes uint16_t definition               */
#include <stdbool.h>            /* Includes true/false definition             */
#include "periph_gen.h"
#include "periph_tmr.h"
#include "periph_pwm.h"
#include "LCDv3.h"
#include "fonctions_sup.h"

#define BUTTON1_PIN   PORTEbits.RE0  // Bouton 1 connecter a RE0
#define BUTTON2_PIN   PORTEbits.RE1  // Bouton 2 connecter a RE1
#define BUTTON3_PIN   PORTEbits.RE2  // Bouton 3 connecter a RE2

void menu_principale(int *contrast)
{
    int exit_menu=0;                                //exit_menu variable et condition poir la condition de sortie
    int count_bout_1=0;                             //du menu
    int ptrcontrast = *contrast;
    int choix=0;                                    //si choix = 1 donc changement de luminosite si 2 test de bouton
                                                    //et si 3 sorti du menu
    int presser=100;                                //presser=100 pour pouvoir appuyer
                                                    //plusieur fois sur le + et le - sans 
                                                    //avoir de nombres negatifes
    int operation1 = presser%2;                     //operation pour savoir si presser est paire ou impaire
                                                
    LCDClearDisplay();                              //PARTIE 1 MENU: (VISUEL)
    LCDWriteStr("XXXXXXXXXXXXXXXX");                //Cette partie de code est une initialiation
    LCDGoto(1,0);                                   //visuel au menue
    LCDWriteStr("XXXXX MENU XXXXX");
    LCDGoto(2,0);
    LCDWriteStr("XXXXXXXXXXXXXXXX");
    delay_en_s(1);
    //_wait10mus(500000);                             //FIN PARTIE 1 MENU
    LCDClearDisplay();                                                
    
    
    do
    {   
        do                                          //PARTIE 2 MENU: (SELECTION)
        {                                           
            if (detect_button_press(2)&&detect_button_press(3)){//si bouton 2 et 3 appuyer en meme temps 
                choix = 3;                                      //choix = 3 
                break;                                          //et on sort du menu
            }
            if(detect_button_press(1))              //lorsqu'on appuie sur le bouton 1 
            {                                       //count_bout_1 augmente de 1, ceci va nous permetre
                count_bout_1 += 1;                  //de selection une option du menu par rapport 
            }                                       //a la variable choix
            if(detect_button_press(2))              //lorsqu'on appuie sur le bouton 2
            {
                LCDClearDisplay();                  //presser diminue de 1
                presser = presser - 1;              //variable presser pour l'affichage du selectionneur 'X'
            }
            if(detect_button_press(3))              //lorsqu'on appuie sur le bouton 3
            {
                LCDClearDisplay();                  //presser augmente de 1
                presser += 1;                       //variable presser pour l'affichage du selectionneur 'X'
            }
            if((presser%2)==0)                       //le cas ou presser est paire on affiche le selecteur 'X'
            {                                       //a cote de l'option Luminosite
                LCDGoto(0,0);
                LCDWriteStr("1.Luminosite   X");
                LCDGoto(1,0);
                LCDWriteStr("2.Test Bouton   ");
                LCDGoto(2,0);
                LCDWriteStr("B1=OK/B2=-/B3=+ ");
                choix = 1;                          //et on donne a choix la valeur 1 qui nous permetra 
            }                                       //de dire que choix 1 = changement de luminosite
            if((presser%2)==1)                       //le cas ou presser est impaire on affiche le selecteur 'X'
            {                                       //a cote de l'option test de boutons
                LCDGoto(0,0);
                LCDWriteStr("1.Luminosite    ");
                LCDGoto(1,0);
                LCDWriteStr("2.Test Bouton  X");
                LCDGoto(2,0);
                LCDWriteStr("B1=OK/B2=-/B3=+ ");
                choix = 2;                          //et on donne a choix la valeur 2 qui nous permetra 
            }                                       //de dire que le choix 2 = test de bouons 
         
        }while(count_bout_1 < 1);                  //la boucle se termine lorsqu'on appuie sur le bouton 1
                                                    //qui est le bouton SET ou OK
        LCDClearDisplay();
                                                    //FIN PARTIE 2 MENU
        
        if(choix==2)                                 //PARTIE 3 MENU: (CAS DE TEST DE BOUTON)
            {                                       //si lorsque le bouton 1 a ete appuiyer presser etais impaire
                                                    //on passe au test de boutons
                do{                                 //boucle d'initiation de test
                    if(detect_button_press(1)||detect_button_press(2)||detect_button_press(3)) {//valide si 1 des
                                                                                                //3 boutons est appuyer
                        if(detect_button_press(1))  //si bouton 1 appuyer
                        {
                            LCDGoto(0,0);           
                            LCDWriteStr("Button 1 = X");//un 'X' sera afficher a cote de Bouton 1
                            //_wait10mus(300000);
                            delay_en_s(3);
                        }
                        if(detect_button_press(2))  //si bouton 2 appuyer
                        {
                            LCDGoto(1,0);
                            LCDWriteStr("Button 2 = X");//un 'X' sera afficher a cote de Bouton 2
                            //_wait10mus(300000);
                            delay_en_s(3);
                        }
                        if(detect_button_press(3))  //si bouton 3 appuyer
                        {
                            LCDGoto(2,0);
                            LCDWriteStr("Button 3 = X");//un 'X' sera afficher a cote de Bouton 3
                            //_wait10mus(300000);
                            delay_en_s(3);
                        }


                    }
                    else if(!detect_button_press(1)||!detect_button_press(2)||!detect_button_press(3)) {
                        LCDClearDisplay();          //si aucun bouton n'est appuyer on affiche 0
                        LCDGoto(0,0);               //a cote des 3 boutons 
                        LCDWriteStr("Button 1 = 0");
                        LCDGoto(1,0);
                        LCDWriteStr("Button 2 = 0");
                        LCDGoto(2,0);
                        LCDWriteStr("Button 3 = 0");

                        //_wait10mus(300000);
                        delay_en_s(3);
                    }//cetter boucle se repetra jusqu'a ce qu'on appui sur les 3 boutons en meme temps
                }while(detect_button_press(1)&&detect_button_press(2)&&detect_button_press(3));
                                                    //FIN PARTIE 3 MENU
            }
        if (choix==1)                                //PARTIE 4 MENU: (CAS LUMINOSITE)
        {        
            LCDClearDisplay();                      //contrats est une variable globale pour definir la 
            LCDGoto(0,0);                           //luminosite de default qui est de 52
            LCDWriteStr("Luminosite");              //ici on affiche 13 X pour indiquer que la luminosite 
            LCDGoto(1,0);                           //est a 52 (puisque 63 valeur max don il ya 64 differente
            LCDWriteStr("XXXXXXXXXXXXX");           //valeur de luminausite) puiqu'on a que 16 case on divise 
            LCDGoto(2,0);                           //64 par 16 on aura 4 ce qui definira chaque X 
            LCDWriteStr("B1=OK/B2=-/B3=+");
            do {
                if (detect_button_press(3)){        //si on appuie sur le bouton 3 on augmente la luminosite de 4
                    ptrcontrast +=4;                   
                    if (ptrcontrast>64){
                        ptrcontrast = 64;
                    }
                    loading_X_simulator(&ptrcontrast); //donc on va ajouter un X a l'aide de cette fonction
                }
                if (detect_button_press(2)){        //si on appuie sur le bouton 2 on diminue la luminosite de 4
                    ptrcontrast -=4;
                    if (ptrcontrast<0){
                        ptrcontrast = 0;
                    }
                    loading_X_simulator(&ptrcontrast); //donc on va retirer un X a l'aide de cette fonction
                }
            }while (detect_button_press(1));        //cette boucle restera valide jusqu'a ce qu'on appuie sur le 
                                                    //bouton 1 == SET/OK
            LCDContrastSet(ptrcontrast);               //apres avoir sorti de la boucle contrast a changer 
        }                                           //et la luminosite et mise a cette valeur
        
        if (choix == 3){                            //si on a appuyer sur les boutons 2 et 3 ensemble 
            exit_menu=1;                            //counter_men sera egale a 11 qui est
        }
        
                                                    //FIN PARTIE 4 MENU
    }while(exit_menu==0);                           //FIN DE LA FONCTION MENU
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

void loading_X_simulator(int *contrast){
    int num_of_X;
    num_of_X= *contrast/4;
    char chainedechar[] = "XXXXXXXXXXXXXXXX";
    for (int i=0;i<num_of_X;i++){
        LCDDataWrite(chainedechar[i]);
    }
}
void delay_en_s(int time) {
    
    int looper;
    looper = time*1000;
    for (int i = 0; i < looper; i++) { // Each iteration waits for 10ms
        _wait10mus(100); // 100 * 10 µs = 1000 µs = 1 ms
    }
}