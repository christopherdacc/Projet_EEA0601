/**
 *                       Librairie TICKS
 * ------------------------------------------------------------------
 * Description :
 * -----------
 * Librairie de gestion du temps. 
 * Permet de mesurer des durées en ms.
 * 
 * -----------------------------------------------------------------
 * Utilisation :
 * ----------- 
 * #include "ticks.h"
 * 
 * int main(void){
 *   Time tm = getTime();
 * 
 *   // attente 3 secondes après tm
 *   while(!isTimeOver(tm,3000)); 
 *   ...
 *   while(1);
 * }
 * 
 * -----------------------------------------------------------------
 * Effet de bord :
 * -------------
 * Cette librairie mobilise le timer 2
 * 
 */

#ifndef TIME_H
#define TIME_H

#include <stdbool.h>
#include "periph_gen.h"

#define TIME_MS (Fcy/1000)

typedef int Time;


/**
 * Initialisation du comptage de temps (unité à la ms)
 */
void initTime();
/**
 * Récupération de l'instant courant (de 0 à 65,535s)
 * @return instant courant en ms
 */
Time getTime();

/**
 * Indique un dépassement d'échéance fixée à origin+duration
 * @param origin instant initial
 * @param duration durée d'attente à partir de l'instant initial
 * @return vrai si l'échéance est dépassée
 */
bool isTimeOver(Time origin,unsigned int duration);


#endif