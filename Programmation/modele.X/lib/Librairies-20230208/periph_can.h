/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion bus CAN 
* 
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

#ifndef CAN_H
#define CAN_H


#include "periph_gen.h"

//*******************
// modes opératoires
//*******************

enum CAN_OP_MODE
{
    CAN_OP_MODE_NORMAL    = 0b000,
    CAN_OP_MODE_DISABLE   = 0b001,
    CAN_OP_MODE_LOOPBACK  = 0b010,
    CAN_OP_MODE_LISTEN    = 0b011,
    CAN_OP_MODE_CONFIG    = 0b100,
	CAN_OP_MODE_LISTEN_ALL= 0b111
};

void CANSetOperationMode(enum CAN_OP_MODE mode);



//*****************************************
// débit binaire et synchronisation symbole
//*****************************************

// masques de configuration 
enum CAN_CONFIG_FLAGS
{
    CAN_CONFIG_DEFAULT          = 0b1111111111111111,  // par défaut configuration des TQ,SAMPLE THRICE, XTD, CARE, DBL BUFF   

    CAN_CONFIG_PHSEG2_PRG_BIT   = 0b0000000010000000,  // configuration du SEG2
    CAN_CONFIG_PHSEG2_PRG_ON    = 0b1111111111111111,   
    CAN_CONFIG_PHSEG2_PRG_OFF   = 0b1111111101111111,   

    CAN_CONFIG_LINE_FILTER_BIT  = 0b0100000000000000,  // place le filtre passe-bas sur la ligne de réception permettant d'éviter les wakeup intempestifs.  
    CAN_CONFIG_LINE_FILTER_ON   = 0b1111111111111111,   
    CAN_CONFIG_LINE_FILTER_OFF  = 0b1011111111111111,   

    CAN_CONFIG_SAMPLE_BIT       = 0b0000000001000000, // configuration du mode d'échantillonnage
    CAN_CONFIG_SAMPLE_THRICE    = 0b1111111111111111,   
    CAN_CONFIG_SAMPLE_ONCE      = 0b1111111110111111,   

    CAN_CONFIG_MSG_TYPE_BIT     = 0b0000000000000001, // configuration des types identifiant (filtre réception)
    CAN_CONFIG_STD_MSG          = 0b1111111111111110,   
    CAN_CONFIG_XTD_MSG          = 0b1111111111111111,
   
	CAN_CONFIG_MSG_TYPE_CARE_BIT= 0b0001000000000000, // configuration du masque (filtrage selon type STD ou XTD ou pas)
	CAN_CONFIG_MSG_TYPE_CARE	= 0b1111111111111111,
	CAN_CONFIG_MSG_TYPE_NOT_CARE= 0b1110111111111111,
	
    CAN_CONFIG_DBL_BUFFER_BIT   = 0b0000000000000100, // configuration double buffer
    CAN_CONFIG_DBL_BUFFER_OFF   = 0b1111111111111111,
    CAN_CONFIG_DBL_BUFFER_ON    = 0b1111111111111011,

	CAN_CONFIG_CAPTURE_BIT      = 0b1000000000000000, //configuration du bit de capture 
	CAN_CONFIG_CAPTURE_ON       = 0b1111111111111111, //(impulsion de largeur 1 bit sur IC2 en fin de trame reçue)
	CAN_CONFIG_CAPTURE_OFF      = 0b0111111111111111,

	CAN_CONFIG_MASTER_CLOCK     = 0b0000100000000000, //configuration FCAN
	CAN_CONFIG_MASTER_CLOCK_FCY = 0b1111111111111111,
	CAN_CONFIG_MASTER_CLOCK_4FCY= 0b1111011111111111,

	CAN_CONFIG_IDLE_BIT			= 0b0010000000000000, // comportement du module lorsque le CPU entre en idle 
	CAN_CONFIG_DISC_ON_IDLE		= 0b1111111111111111, 
	CAN_CONFIG_CONT_ON_IDLE		= 0b1101111111111111,  

};


// débit binaire
void CANSetBaudRate(BYTE SJW,
                     BYTE BRP,
                     BYTE PHSEG1,
                     BYTE PHSEG2,
                     BYTE PROPSEG,
                     enum CAN_CONFIG_FLAGS flags);



//*****************************************
// masque de filtre
//*****************************************

enum CAN_BUFFER_MASK
{
     CAN_MASK_B1,
     CAN_MASK_B2
};


void CANSetMask(enum CAN_BUFFER_MASK code,
                 unsigned long val,
                 enum CAN_CONFIG_FLAGS type);



//*****************************************
// filtre
//*****************************************

enum CAN_FILTER
{
    CAN_FILTER_B1_F1,
    CAN_FILTER_B1_F2,
    CAN_FILTER_B2_F1,
    CAN_FILTER_B2_F2,
    CAN_FILTER_B2_F3,
    CAN_FILTER_B2_F4
};


 void CANSetFilter(enum CAN_FILTER code,
                    unsigned long val,
                    enum CAN_CONFIG_FLAGS type);



//*****************************************
// Initialisation CAN
//*****************************************
void CANInitialize(BYTE SJW,
                   BYTE BRP,
                   BYTE PHSEG1,
                   BYTE PHSEG2,
                   BYTE PROPSEG,
                    enum CAN_CONFIG_FLAGS config);



//*****************************************
// Transmission de trame
//*****************************************

 enum CAN_TX_MSG_FLAGS
 {
    CAN_TX_DEFAULT		= 0b1111111111111111,	// priorité buffer

    CAN_TX_PRIORITY_BITS= 0b0000000000000011,	// priorité buffer
    CAN_TX_PRIORITY_0   = 0b1111111111111100,   
    CAN_TX_PRIORITY_1   = 0b1111111111111101,   
    CAN_TX_PRIORITY_2   = 0b1111111111111110,   
    CAN_TX_PRIORITY_3   = 0b1111111111111111,   

    CAN_TX_FRAME_BIT    = 0b0000000000001000,	// choix type à émettre
    CAN_TX_STD_FRAME    = 0b1111111111111111,   
    CAN_TX_XTD_FRAME    = 0b1111111111110111,   

    CAN_TX_RTR_BIT      = 0b0000000000010000,	// remote transmission request
    CAN_TX_NO_RTR_FRAME = 0b1111111111111111,   
    CAN_TX_RTR_FRAME    = 0b1111111111101111    
};

BOOL CANSendMessage(unsigned long id,
                     BYTE* Data,
                     BYTE DataLen,
                     enum CAN_TX_MSG_FLAGS MsgFlags);



//*****************************************
// Réception de trame
//*****************************************


enum CAN_RX_MSG_FLAGS
{
    CAN_RX_FILTER_BITS  = 0b0000000000000111,   // Use this to access filter
                                   			    // bits
    CAN_RX_FILTER_1     = 0b0000000000000000,
    CAN_RX_FILTER_2     = 0b0000000000000001,
    CAN_RX_FILTER_3     = 0b0000000000000010,
    CAN_RX_FILTER_4     = 0b0000000000000011,
    CAN_RX_FILTER_5     = 0b0000000000000100,
    CAN_RX_FILTER_6     = 0b0000000000000101,

    CAN_RX_RTR     		= 0b0000000000001000,   // Set if Remote transfert request else
                         		               // cleared

    CAN_RX_INVALID_MSG  = 0b0000000000010000,   // Set if invalid else
                                		        // cleared

    CAN_RX_XTD_FRAME    = 0b0000000000100000,   // Set if XTD message else
                                        		// cleared

    CAN_RX_RTR_FRAME    = 0b0000000001000000,   // Set if RTR message else
                                       			// cleared

    CAN_RX_DBL_BUFFERED = 0b0000000010000000,   // Set if this message was
                                        		// hardware double-buffered

    CAN_RX_OVERFLOW     = 0b0000000100000000    // Set if Overflowed else
                         		                // cleared

};


BOOL CANReceiveMessage(unsigned long *id,
                        BYTE *Data,
                        BYTE *DataLen,
                        enum CAN_RX_MSG_FLAGS *MsgFlags);



/*********************************************************************
 * Macro:           BYTE CANGetTxErrorCount()
 *
 * PreCondition:    Aucune
 *
 * Entrée:          Aucune
 *
 * Sortie:          Nombre d'erreurs de transmission courant
 *
 * Effets de bord:  Aucun
 *
 ********************************************************************/
#define CANGetTxErrorCount()    ((BYTE) (C1EC>>8))



/*********************************************************************
 * Macro:           BYTE CANGetRxErrorCount()
 *
 * PreCondition:    Aucune
 *
 * Entrée:          Aucune
 *
 * Sortie:          Nombre d'erreurs de réception courant
 *
 * Effets de bord:    Aucun
 *
 ********************************************************************/
#define CANGetRxErrorCount()    ((BYTE) (C1EC&0x00FF))



/*********************************************************************
 * Macro:           BOOL CANIsBusOff()
 *
 * PreCondition:    None
 *
 * Entrées:         None
 *
 * Sortie:          TRUE lorsque le module est éteint du fait d'un nombre d'erreurs excessif
 *                  FALSE sinon.
 *
 * Effets de bord:  Aucun
 *
 ********************************************************************/
#define CANIsBusOff()           (C1INTFbits.TXBO)



/*********************************************************************
 * Macro:           BOOL CANIsTxPassive()
 *
 * PreCondition:    None
 *
 * Entrées:         None
 *
 * Sortie:          TRUE si le module d'émission est en error passive du fait de l'émission
 *                  (Compteur d'erreur d'émission supérieur à 127)
 *
 * Effets de bord:    None
 *
 ********************************************************************/
#define CANIsTxPassive()        (C1INTFbits.TXEP)



/*********************************************************************
 * Macro:           BYTE CANIsRxPassive()
 *
 * PreCondition:    None
 *
 * Entrées:         None
 *
 * Sortie:          TRUE si le module d'émission est en error passive du fait de la réception
 *                  (Compteur d'erreur de réception émission supérieur à 127)
 *
 * Effets de bord:    None
 *
 ********************************************************************/
#define CANIsRxPassive()        (C1INTFbits.RXEP)



/*********************************************************************
 * Macro:           void CANAbortAll()
 *
 * PreCondition:    Aucun
 *
 * Entrées:         Aucun
 *
 * Sortie:          Aucun
 *
 * Effets de bord:  Aucun
 *
 * Action:          Annule les transmissions en cours
 ********************************************************************/
#define CANAbortAll()           (C1CTRLbits.ABAT = 1)



/*********************************************************************
 * Macro:           BOOL  CANIsRxReady()
 *
 * PreCondition:    Aucune
 *
 * Entrées:         Aucune
 *
 * Sortie:          TRUE si au moins un des buffers de réception est vide.
 *
 * Effets de bord:  Aucun
 *
 ********************************************************************/
#define CANIsRxReady()          (C1RX0CONbits.RXFUL || C1RX1CONbits.RXFUL)



/*********************************************************************
 * Macro:           BOOL CANIsTxReady()
 *
 * PreCondition:    Aucun
 *
 * Entrées:         Aucun
 *
 * Sortie:          TRUE si au moins une des buffer d'émission est vide
 *
 * Effets de bord:  Aucun
 *
 ********************************************************************/
#define CANIsTxReady()          (!C1TX0CONbits.TXREQ || \
                                 !C1TX1CONbits.TXREQ || \
                                 !C1TX2CONbits.TXREQ )
#endif
