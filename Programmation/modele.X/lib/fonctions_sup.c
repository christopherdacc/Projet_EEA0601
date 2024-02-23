#include <xc.h>
#include <stdbool.h>
#include "fonctions_sup.h"

void menu_principale(int *choix)
{
    int counter_men=1, count_bout_1=0, count_bout_2=0, count_bout_3=0, presser=1;
    int *choix=0;
    do
    {
        LCDClearDisplay();
        LCDWriteStr("   Bienvenue   ");
        LCDGoto(1,0);
        LCDWriteStr("       au       ");
        LCDGoto(2,0);
        LCDWriteStr("      menu      ");
        _wait10mus(500000);
        LCDClearDisplay();
        do
        {
            if(detect_button_press(1))
            {
                count_bout_1 += 1;
            }
            if(detect_button_press(2))
            {
                presser=count_bout_2 + 1;
            }
            if(detect_button_press(3))
            {
                presser=count_bout_3 + 1;
            }
            
            if(presser%2=1)
            {
                LCDClearDisplay();
                LCDWriteStr("1.Luminosite   X");
                LCDGoto(1,0);
                LCDWriteStr("2.Test Bouton");
                choix = 1;
                
            }
            if(count_bout_3%2=0)
            {
                LCDClearDisplay();
                LCDWriteStr("1.Luminosite");
                LCDGoto(1,0);
                LCDWriteStr("2.Test Bouton  X");
                choix = 2;
            }
         
        }while(count_bout_1 == 1);
        
        
        
        
    }while(counter_men>10);
    
    
}