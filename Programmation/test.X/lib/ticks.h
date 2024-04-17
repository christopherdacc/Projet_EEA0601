/**
 *                       Librairie TICKS
 * ------------------------------------------------------------------
 * Description :
 * -----------
 * Librairie de gestion du temps. 
 * Permet de mesurer des dur�es en ms.
 * 
 * -----------------------------------------------------------------
 * Utilisation :
 * ----------- 
 * #include "ticks.h"
 * 
 * int main(void){
 *   Time tm = getTime();
 * 
 *   // attente 3 secondes apr�s tm
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
 * Initialisation du comptage de temps (unit� � la ms)
 */
void initTime();
/**
 * R�cup�ration de l'instant courant (de 0 � 65,535s)
 * @return instant courant en ms
 */
Time getTime();

/**
 * Indique un d�passement d'�ch�ance fix�e � origin+duration
 * @param origin instant initial
 * @param duration dur�e d'attente � partir de l'instant initial
 * @return vrai si l'�ch�ance est d�pass�e
 */
bool isTimeOver(Time origin,unsigned int duration);


#endif