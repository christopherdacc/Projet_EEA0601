#include "p30f4012.h"
#include "dsp.h"
#include "periph_can.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion bus CAN
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/





//routine d'interruption traitement �v�nements CAN sur C1
// d�masquer les bits de C1INTE pour activer les �v�nements correspondant
// ainsi que IEC1bits.C1IE
void __attribute__((__interrupt__,no_auto_psv)) _C1Interrupt(void){
//Traitement transmission buffer0
if (C1INTFbits.TX0IF) C1INTFbits.TX0IF=0;

//Traitement transmission buffer1
if (C1INTFbits.TX1IF) C1INTFbits.TX1IF=0;

//Traitement transmission buffer2
if (C1INTFbits.TX2IF) C1INTFbits.TX2IF=0;

//Traitement r�ception buffer0
if (C1INTFbits.RX0IF) 
	{
	C1INTFbits.RX0IF=0;
	C1RX0CONbits.RXFUL=0;
	}

//Traitement r�ception buffer1
if (C1INTFbits.RX1IF) 
	{
	C1INTFbits.RX1IF=0;
	C1RX1CONbits.RXFUL=0;
	}

//Traitement Wakeup
if (C1INTFbits.WAKIF) 
	{
	C1INTFbits.WAKIF=0;
	}

//Traitement Erreurs
if (C1INTFbits.ERRIF) 
	{
	C1INTFbits.ERRIF=0;
	}

//Traitement Message re�u invalide
if (C1INTFbits.IVRIF) 
	{
	C1INTFbits.IVRIF=0;
	}

// Acquittement d'interruption si plus aucune pr�sente
if((C1INTF & C1INTE)==0) IFS1bits.C1IF=0;

}



//Fonction d'initialisation

/*********************************************************************
 * Fonction:        void CANSetOperationMode(CAN_OP_MODE mode)
 *
 * PreCondition:    aucune
 *
 * Entr�e:           mode    - mode op�ratoire de
 *                             enum CAN_OP_MODES
 *
 * sortie:          MCU est plac� dans le mode requis
 *
 * Effets de bord:    None
 *
 * Overview:        L'octet de mode est copi� dans C1CTRLbits.REQOP
 *                  puis on attend que le module soit effectivement dans 
 *                  le mode requis.
 *
 * Note:            Appel bloquant : sorite uniquement lorsque le mode est 
 *	                chang�.
 ********************************************************************/
void CANSetOperationMode(enum CAN_OP_MODE mode)
{
     // Request desired mode.
     C1CTRLbits.REQOP = mode;

    // Wait till desired mode is set.
    while( (C1CTRLbits.OPMODE) != mode );
}






/*********************************************************************
 * Fonction:        void CANSetBaudRate(BYTE SJW,
 *                                      BYTE BRP,
 *                                      BYTE PHSEG1,
 *                                      BYTE PHSEG2,
 *                                      BYTE PROPSEG,
 *                                      enum CAN_CONFIG_FLAGS flags)
 *
 * PreCondition:    La fonction n'est prise en compte que lorsque le module est 
 *                  en mode configuration. Elle est ignor�e sinon.
 *
 * Entr�e:          SJW     - SJW : pas de re-synchronisation (entre 1 et 4TQ)                              
 *                  BRP     - BRP : prescaler (1 � 64). TQ=2*BRP*Tcan.
 *                            (Tcan=Tcy/4 si CANCKS=1 dans C1CTRL)
 *                             
 *                  PHSEG1  - PHSEG1 : dur�e de phase 1
 *                              (entre 1 et 8TQ)
 *                  PHSEG2  - PHSEG2 : dur�e de phase 2
 *                               (entre 1 et 8TQ)
 *                  PROPSEG - PROPSEG : temps de propagation
 *                               (entre 1 et 8TQ)
 *                  flags   - Value of type enum CAN_CONFIG_FLAGS
 *
 * Sortie :         R�gle le d�bit binaire et la synchronisation symbole.
 *
 * Effets de bord:  None
 *
 * Action:        
 *
 ********************************************************************/
 void CANSetBaudRate(BYTE SJW,
                     BYTE BRP,
                     BYTE PHSEG1,
                     BYTE PHSEG2,
                     BYTE PROPSEG,
                     enum CAN_CONFIG_FLAGS flags)
 {
     // Translation pour correspondance valeur r�elle - valeur registre
     SJW--;
     BRP--;
     PHSEG1--;
     PHSEG2--;
     PROPSEG--;


	C1CFG1=0;
	C1CFG2=0;

    
    C1CFG1bits.SJW = SJW;
    C1CFG1bits.BRP=BRP;
	C1CFG2bits.SEG1PH=PHSEG1;
	C1CFG2bits.PRSEG=PROPSEG;

 
 	C1CTRL|=(flags&CAN_CONFIG_MASTER_CLOCK);

    if (flags & CAN_CONFIG_SAMPLE_BIT)
        C1CFG2bits.SAM = 1;

    if ( flags & CAN_CONFIG_PHSEG2_PRG_BIT )
		C1CFG2bits.SEG2PHTS = 1;
    C1CFG2bits.SEG2PH = PHSEG2;

    if ( flags & CAN_CONFIG_LINE_FILTER_BIT )
        C1CFG2bits.WAKFIL = 1;

}





/*********************************************************************
 * Fonction:        void CANIDToRegs(BYTE* ptr,
 *                                      unsigned long val,
 *                                      enum CAN_CONFIG_FLAGS type)
 *
 * PreCondition:    aucune
 *
 * Entr�e:          ptr     - Adresse du buffer � modifier
 *                  val     - Valeur 32 bits � convertir
 *                  type    - Type de message CAN_CONFIG_XTD_MSG ou CAN_CONFIG_STD_MSG
 *
 * Sortie:          Ajustement du buffer CAN du 30F4012 point�
 *
 * Effets de bord:  Aucun
 *
 * Action:          Fonction Priv�e. En fonction du type, val (repr�sentant un masque ou un filtre)
 *                  est inscrit dans les registres C1RXZnEIDH ou L ou C1RXZnSID
 *					Z=F pour filtre et M pour masque, n repr�sente le num�ro de buffer (d�pend de ptr)
 *
 ********************************************************************/
static void CANIDToRegs(WORD* ptr,
                        unsigned long val,
                        enum CAN_CONFIG_FLAGS type)
{

	WORD * Value;


  //  CAN_MESSAGE_ID *Value;

    Value =  (WORD *)&val;

    if ( (type & CAN_CONFIG_MSG_TYPE_BIT)==0)
        // Standard Identifier
		*ptr=(Value[1]&0b0000011111111111)<<2;
    else
	{
        // Extended Identifier
		*ptr=(Value[1]&0b0000111111111110)<<1;
		*ptr |= 1;                     			// EXIDEN (message �tendu) ou MIDE (type care) activ�
		ptr++;									// Registre suivant (C1RXZnEIDH)

		*ptr=(Value[1]&0b1)<<11;

        *ptr |= (Value[0]>>6);

		ptr++;									// Registre suivant (C1RXZnEIDL)
        *ptr = (Value[0]&0b0000000000111111)<<10;
    }
}






/*********************************************************************
 * Fonction:        void RegsToCANID(BYTE *ptr,
 *                                      unsigned long *val,
 *                                      enum CAN_CONFIG_FLAGS type)
 *
 * PreCondition:    None
 *
 * Entr�e:          ptr     - Adresse registres du buffer
 *
 * Sorties par ad:  val     - Identifiant
*                  type     - Type de message (modifi� en fonction de
 *                            CAN_CONFIG_XTD_MSG ou CAN_CONFIG_STD_MSG)
  
*
 * Sortie:          Ajustement de 'val' en fonction du contenu du buffer CAN du 30F4012 point�
 *
 * Effet de bord:    aucun
 *
 * Action:          Fonction priv�e. En fonction du type, l'identifiant de message 
 *                  est retourn� dans val
 *
 ********************************************************************/
static void RegsToCANID(WORD* ptr,
                        unsigned long *val,
                        enum CAN_CONFIG_FLAGS *type)
{
    WORD *Value;
	*val=0;
    Value = (WORD*)val;

    if ( ((*ptr)&0x0001)==0)
    {
        // Standard Identifier
		Value[0]=((*ptr)&0b0001111111111100)>>2;
		(*type)&=(~CAN_CONFIG_MSG_TYPE_BIT);
    }
    else
    {

		Value[0]=((*ptr)&0b0001111111111100)>>1;
		ptr++;
		Value[0]|=((*ptr)&0b0000100000000000)>>10;
		Value[1]=((*ptr)&0b0000011111111111)<<6;
		ptr++;
		Value[1]|=((*ptr)&0b1111110000000000)>>10;
		(*type)|=CAN_CONFIG_MSG_TYPE_BIT;
    }
}




/*********************************************************************
 * Fonction:        void CANSetMask(enum CAN_BUFFER code,
 *                                  unsigned long val,
 *                                  enum CAN_CONFIG_FLAGS type)
 *
 * PreCondition:    Le module doit �tre en mode de configuration.
 *
 * Entr�e:           code   - Selection du Buffer concern� (CAN_MASK)
 *                  val     - Valeur de masque
 *                  type    - Type de message � filtrer
 *                            CAN_CONFIG_XTD_MSG or CAN_CONFIG_STD_MSG
 *
 * Sortie:          Valeur du masque ajust�e
 *                  
 *
 * Effet de bord:    Aucun
 *
 ********************************************************************/



 void CANSetMask(enum CAN_BUFFER_MASK code,
                 unsigned long val,
                 enum CAN_CONFIG_FLAGS type)
 {
     WORD *ptr;

    // Pointe sur le buffer ad�quat 
    if ( code == CAN_MASK_B1 )
        ptr = (WORD*)&C1RXM0SID;
    else
        ptr = (WORD*)&C1RXM1SID;

    CANIDToRegs(ptr, val,(type&CAN_CONFIG_MSG_TYPE_CARE_BIT)>>12); //CARE OR NOT

}




/*********************************************************************
 * Fonction:        void CANSetFilter(enum CAN_FILTER code,
 *                                   unsigned long val,
 *                                   enum CAN_CONFIG type)
 *
 * PreCondition:    Le module doit �tre en mode de configuration.
 *
 *
 * Entr�e:          code    - Nom du filtre (� choisir parmis ceux d�finis dans CAN_FILTER)
 *                  val     - Valeur � placer dans le filtre.
 *                  type    - Type de message � filtrer
 *                            CAN_CONFIG_XTD_MSG or CAN_CONFIG_STD_MSG
 *
 * Sortie:          Le contenu du filtre est modifi�
 *
 * Effet de bord:   Aucun
 ********************************************************************/
 void CANSetFilter(enum CAN_FILTER code,
                    unsigned long val,
                    enum CAN_CONFIG_FLAGS type)
 {
    WORD *ptr;

    // Select appropriate starting address based on given CAN_FILTER
    // code.
    switch(code)
    {
    case CAN_FILTER_B1_F1:
        ptr = (WORD*)&C1RXF0SID;
        break;

    case CAN_FILTER_B1_F2:
        ptr = (WORD*)&C1RXF1SID;
        break;

    case CAN_FILTER_B2_F1:
        ptr = (WORD*)&C1RXF2SID;
        break;

    case CAN_FILTER_B2_F2:
        ptr = (WORD*)&C1RXF3SID;
        break;

    case CAN_FILTER_B2_F3:
        ptr = (WORD*)&C1RXF4SID;
        break;

    default:
        ptr = (WORD*)&C1RXF5SID;
        break;
    }

    // Convertion mot long vers registres.
    CANIDToRegs(ptr, val, type);

}
 




/*********************************************************************
 * Fonction:        void CANInitialize(BYTE SJW,
 *                                      BYTE BRP,
 *                                      BYTE PHSEG1,
 *                                      BYTE PHSEG2,
 *                                      BYTE PROPSEG,
 *                                      enum CAN_CONFIG_FLAGS flags)
 *
 * PreCondition:    Le module doit �tre en mode de configuration.    
 *
 * Entr�e:          SJW     - SJW : pas de re-synchronisation (entre 1 et 4TQ)                              
 *                  BRP     - BRP : prescaler (1 � 64). TQ=2*BRP*Tcan.
 *                            (Tcan=Tcy/4 si CANCKS=1 dans C1CTRL)
 *                             
 *                  PHSEG1  - PHSEG1 : dur�e de phase 1
 *                              (entre 1 et 8TQ)
 *                  PHSEG2  - PHSEG2 : dur�e de phase 2
 *                               (entre 1 et 8TQ)
 *                  PROPSEG - PROPSEG : temps de propagation
 *                               (entre 1 et 8TQ)
 *                  flags   - Value of type enum CAN_CONFIG_FLAGS
 *
 * Sortie:          Configure le d�bit binaire. Les masques sont plac�s � 0 (tout message accept�).
 *                  Les filtres sont tous configur�s identiquement selon la valeur de  flag.
 *                  Si (config & CAN_CONFIG_VALID_XTD_MSG)
 *                      Tous les filtres sont plac�s � XTD_MSG
 *                  Sinon si (config & CONFIG_VALID_STD_MSG)
 *                      Tous les filtres sont plac�s � STD_MSG
 *                  Si ~(config&CAN_CONFIG_MSG_TYPE_CARE_BIT)
 *					    Les filtres acceptent les 2 types de MSG                     
 *
 * Effets de bord : Annulation des transmissions en cours.
 *
 ********************************************************************/
 void CANInitialize(BYTE SJW,
                    BYTE BRP,
                    BYTE PHSEG1,
                    BYTE PHSEG2,
                    BYTE PROPSEG,
                    enum CAN_CONFIG_FLAGS config)
 {

	// Passage en mode Configuration
    CANSetOperationMode(CAN_OP_MODE_CONFIG);

    // Configuration du d�bit binaire
    CANSetBaudRate(SJW,
                    BRP,
                    PHSEG1,
                    PHSEG2,
                    PROPSEG,
                    config);



//    RXB0CON = config & CAN_CONFIG_MSG_BITS;
// configuration du double buffering
    if ( (config & CAN_CONFIG_DBL_BUFFER_BIT)
                == CAN_CONFIG_DBL_BUFFER_ON )
        C1RX0CONbits.DBEN = 1;


//    RXB1CON = RXB0CON;


    	CANSetMask(CAN_MASK_B1, 0, config);
    	CANSetMask(CAN_MASK_B2, 0, config);
 

	   	CANSetFilter(CAN_FILTER_B1_F1, 0, config);
    	CANSetFilter(CAN_FILTER_B1_F2, 0, config);
    	CANSetFilter(CAN_FILTER_B2_F1, 0, config);
    	CANSetFilter(CAN_FILTER_B2_F2, 0, config);
    	CANSetFilter(CAN_FILTER_B2_F3, 0, config);
    	CANSetFilter(CAN_FILTER_B2_F4, 0, config);

    // Restore to Normal mode.
    CANSetOperationMode(CAN_OP_MODE_NORMAL);
}




/*********************************************************************
 * Fonction:        BOOL CANSendMessage(unsigned long id,
 *                                  BYTE *Data,
 *                                  BYTE DataLen,
 *                                  enum CAN_TX_MSG_FLAGS MsgFlags)
 *
 * PreCondition:    None
 *
 * Entr�e:           id         - Identifiant de message.
 *                                11 ou 29 bits selon que le message est standard ou �tendu.
 *                  Data        - Donn�es (jusque 8 octets)
 *                  DataLen     - Longueur des donn�es (1 � 8).
 *                  MsgFlags    - CAN_TX_MSG_FLAGS
 * 
 * Sortie:          Le message est mis dans la queue lorsqu'un buffer est vide,
 *                  Si aucun buffer n'est disponible, retourne FALSE
 *
 * Effets de bord:  aucun
 *
 ********************************************************************/
BOOL CANSendMessage(unsigned long id,
                     BYTE* Data,
                     BYTE DataLen,
                     enum CAN_TX_MSG_FLAGS MsgFlags)
{
    BYTE i;
    WORD *ptr;
	BYTE *ptr_b;

    // Recherche d'un buffer disponible.
    if ( C1TX0CONbits.TXREQ == 0 )
		ptr=(WORD *)&C1TX0SID;	
    else if ( C1TX1CONbits.TXREQ == 0 )
		ptr=(WORD *)&C1TX1SID;	

    else if ( C1TX2CONbits.TXREQ == 0 )
   		ptr=(WORD *)&C1TX2SID;	
    else
        // Aucun buffer disponible.
        return FALSE;

 	ptr_b=(BYTE *)ptr+6;
    // Application de la priorit� du buffer
    ptr[7]&=~CAN_TX_PRIORITY_BITS|(MsgFlags & CAN_TX_PRIORITY_BITS);

    // Ecriture de l'identifiant �tendu si n�cessaire
    if ( !(MsgFlags & CAN_TX_FRAME_BIT) )
        CANIDToRegs(ptr, id, CAN_CONFIG_XTD_MSG);
    else
        CANIDToRegs(ptr, id, CAN_CONFIG_STD_MSG);

	// Ecriture longueur trame (nb d'octets � transmettre)
	ptr[2]=(ptr[2]&(0b1111110000000111))|(DataLen<<3);
   

    // Ecriture de donn�es.
    for ( i = 0; i < DataLen; i++ )
        ptr_b[i] = Data[i];

    // Indiquer que le buffer est pr�t � �tre �mis 
	ptr[7]|=0b0000000000001000;
	
    return TRUE;
}




/*********************************************************************
 * Fonction:        BOOL CANReceiveMessage(unsigned long *id,
 *                                  BYTE *Data,
 *                                  BYTE DataLen,
 *                                  enum CAN_RX_MSG_FLAGS MsgFlags)
 *
 * PreCondition:    Aucune
 *
 * Input:           Aucune
 *
 * Sorties par ad:  id          - Identifiant message
 *                  Data        - Donn�es lues
 *                  DataLen     - Longueur donn�es (1 � 8).
 *                  MsgFlags    - de tpe CAN_RX_MSG_FLAGS 
 *
 *
 * Sortie:          retourne FALSE si aucun buffer ne contient de donn�es
 *
 * Effets de bord:  Aucun
 *
 ********************************************************************/
BOOL CANReceiveMessage(unsigned long *id,
                        BYTE *Data,
                        BYTE *DataLen,
                        enum CAN_RX_MSG_FLAGS *MsgFlags)
{
    BYTE i;
    BYTE *ptr;
    BOOL Buffer0locked;
	enum CAN_CONFIG_FLAGS *dummy; 
    
	// Start with no error or flags set.
    *MsgFlags = 0x0;

    // Recherche d'un buffer contenant un message re�u
    if ( C1RX0CONbits.RXFUL )
    {

		// d�termine le buffer contenant le message � d�verrouiller en fin de lecture
        Buffer0locked = TRUE;   

        // Effacement du flag message re�u.
        C1INTFbits.RX0IF = 0;

        // Si il y a eu overflow, enregistrer l'�v�nement et l'effacer
        if ( C1INTFbits.RX0OVR )
        {
            *MsgFlags |= CAN_RX_OVERFLOW;
            C1INTFbits.RX0OVR = 0;
        }

		// d�termination du filtre d'acceptance
		*MsgFlags |= (C1RX0CON & 0x01);

		// Taille message
    	*DataLen = (BYTE)(C1RX0DLCbits.DLC);
		//Remote request ?
		*MsgFlags |= C1RX0DLC&CAN_RX_RTR;

		// identifiant �tendu
		*MsgFlags|=(C1RX0SIDbits.RXIDE<<5);

		// R�cup�ration identifiant
        RegsToCANID((WORD *)&C1RX0SID, id,dummy);

		// pointeur vers donn�es
	    ptr = (BYTE*)&C1RX0B1;
 
   }
   else if ( C1RX1CONbits.RXFUL )
   {

        Buffer0locked = FALSE;

        // Effacement du flag message re�u.
        C1INTFbits.RX1IF = 0;

        // Si il y a eu overflow, enregistrer l'�v�nement et l'effacer
        if ( C1INTFbits.RX1OVR )
        {
            *MsgFlags |= CAN_RX_OVERFLOW;
            C1INTFbits.RX1OVR = 0;
        }

        *MsgFlags |= (C1RX1CON & CAN_RX_FILTER_BITS);
        if ( *MsgFlags < 0x02 )
            *MsgFlags |= CAN_RX_DBL_BUFFERED;

		// Taille message
		*DataLen = (BYTE)(C1RX1DLCbits.DLC);
		//Remote request ?
		*MsgFlags |= C1RX1DLC&CAN_RX_RTR;

		// identifiant �tendu
		*MsgFlags|=(C1RX1SIDbits.RXIDE<<5);
		// R�cup�ration identifiant
        RegsToCANID((WORD *)&C1RX0SID, id,dummy);

		// pointeur vers donn�es	    
		ptr = (BYTE*)&C1RX0B1;

    }
    else
        return FALSE;

   // R�cup�ration des donn�es du message
    for ( i = 0; i < *DataLen; i++ )
        Data[i] = ptr[i];

 
    // Enregistrement et effacement d'un flag de message invalide pr�c�dent.
    if ( C1INTFbits.IVRIF )
    {
        *MsgFlags |= CAN_RX_INVALID_MSG;
        C1INTFbits.IVRIF = 0;
    }


	// d�verrouille le buffer
    if ( Buffer0locked )
        C1RX0CONbits.RXFUL = 0;
    else
        C1RX1CONbits.RXFUL = 0;

    return TRUE;
}

