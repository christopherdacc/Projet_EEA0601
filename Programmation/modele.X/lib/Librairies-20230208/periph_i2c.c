#include "p30f4012.h"
#include "dsp.h"
#include "periph_i2c.h"

/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion I2C 
*             (Mode Mono Master)
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/


// initialisation du bus I2C
void I2Cinit(void)
{
/* I2CCON: I2C™ Control Register

bit 15 I2CEN: I2C Enable bit
	1 = Enables the I2C module and configures the SDA and SCL pins as serial port pins
	0 = Disables I2C module. All I2C pins are controlled by port functions.

bit 14 Unimplemented: Read as ‘0’

bit 13 I2CSIDL: Stop in Idle Mode bit
	1 = Discontinue module operation when device enters an Idle mode
	0 = Continue module operation in Idle mode

bit 12 SCLREL: SCL Release Control bit (when operating as I2C Slave)
	1 = Release SCL clock
	0 = Hold SCL clock low (clock stretch)
	If STREN = 1:
	Bit is R/W (i.e., software may write ‘0’ to initiate stretch and write ‘1’ to release clock)
	Hardware clear at beginning of slave transmission.
	Hardware clear at end of slave reception.
	If STREN = 0:
	Bit is R/S (i.e., software may only write ‘1’ to release clock)
	Hardware clear at beginning of slave transmission.

bit 11 IPMIEN: Intelligent Peripheral Management Interface (IPMI) Enable bit
	1 = Enable IPMI Support mode. All addresses Acknowledged.
	0 = IPMI mode not enabled

bit 10 A10M: 10-bit Slave Address bit
	1 = I2CADD is a 10-bit slave address
	0 = I2CADD is a 7-bit slave address

bit 9 DISSLW: Disable Slew Rate Control bit
	1 = Slew rate control disabled
	0 = Slew rate control enabled

bit 8 SMEN: SMBus Input Levels bit
	1 = Enable I/O pin thresholds compliant with SMBus specification
	0 = Disable SMBus input thresholds

bit 7 GCEN: General Call Enable bit (when operating as I2C slave)
	1 = Enable interrupt when a general call address is received in the I2CRSR
	(module is enabled for reception)
	0 = General call address disabled

bit 6 STREN: SCL Clock Stretch Enable bit (when operating as I2C slave)
	Used in conjunction with SCLREL bit.
	1 = Enable software or receive clock stretching
	0 = Disable software or receive clock stretching

bit 5 ACKDT: Acknowledge Data bit (When operating as I2C Master. Applicable during master receive.)
	Value that will be transmitted when the software initiates an Acknowledge sequence.
	1 = Send NACK during acknowledge
	0 = Send ACK during acknowledge
	
bit 4 ACKEN: Acknowledge Sequence Enable bit
(When operating as I2C master. Applicable during master receive.)
	1 = Initiate Acknowledge sequence on SDA and SCL pins, and transmit ACKDT data bit
	Hardware clear at end of master Acknowledge sequence.
	0 = Acknowledge sequence not in progress

bit 3 RCEN: Receive Enable bit (when operating as I2C master)
	1 = Enables Receive mode for I2C
	Hardware clear at end eighth bit of master receive data byte.
	0 = Receive sequence not in progress

bit 2 PEN: Stop Condition Enable bit (when operating as I2C master)
	1 = Initiate Stop condition on SDA and SCL pins
	Hardware clear at end of master Stop sequence.
	0 = Stop condition not in progress

bit 1 RSEN: Repeated Start Condition Enabled bit (when operating as I2C master)
	1 = Initiate Repeated Start condition on SDA and SCL pins
	Hardware clear at end of master Repeated Start sequence.
	0 = Repeated Start condition not in progress

bit 0 SEN: Start Condition Enabled bit (when operating as I2C master)
	1 = Initiate Start condition on SDA and SCL pins
	Hardware clear at end of master Start sequence.
	0 = Start condition not in progress
*/

I2CCON=0;
/* I2C baud rate generator */
I2CBRG=268;   // 47 : 400kHz  (268 : 100kHz)


/* Paramétrage interruption */
IPC3bits.MI2CIP=1;   // priorité interruption =1
IFS0bits.MI2CIF=0;   // RAZ flag interruption
IEC0bits.MI2CIE=1;   // autorisation interruption 

I2CCONbits.I2CEN=1; // module I2C on


}



// routine d'interruption traitement des évènements I2C
void __attribute__((__interrupt__,no_auto_psv)) _MI2CInterrupt( void )
{
IFS0bits.MI2CIF=0;   // RAZ flag interruption
isr_I2C();

}

// génération des commandes de controle des échanges sur le bus
void I2C_Cmd(unsigned char commande)
{
I2CCON=(I2CCON&0xFFC0)+commande;
}


// routine de traitement des évènements I2C
// cette routine est appelée par la fonction d'interruption
unsigned char I2Cstate = 0;  		// état du bus
unsigned char I2Cerror = 0;  		// indicateur d'erreur
unsigned char I2Ccycleinprogress=0;
unsigned char *I2C_Pstring_send;	// Pointeur chaîne à émettre
unsigned int I2CCount_send;			// taille chaîne à émettre
unsigned char *I2C_Pstring_rec;     // Pointeur chaîne à recevoir
unsigned int I2CCount_rec;          // taille chaîne à recevoir
unsigned char I2C_read_AD;          // adresse lecture
unsigned char I2CSubAD;             // adresse registre esclave pour
									// lecture ou écriture

/***********************************************/
/*            Routine bas niveau               */
/*      de traitement d'un cycle de lecture    */
/*      ou d'écriture                          */
/***********************************************/

void isr_I2C(void)
{
static int I2Cindx=0;


switch(I2Cstate)
{

    /******** Cycles d'une procédure d'écriture sur l'esclave ************/


    // 
    // lancement procédure écriture (par appel classique)
    //
	case W_INIT :							
    I2C_Cmd(START);
	I2Ccycleinprogress=1;
    I2Cstate++;          						// passage W_STARTING
	I2Cindx=0;
	break;


    // 
    // Start terminé, on envoie l'adresse esclave
    //
	case W_STARTING :    						
	I2CTRN=SLAVE_AD*2;   						// cycle d'écriture : W=0
    I2Cstate++;          						// passage W_AD_WRITING 		
	break;


	case W_AD_WRITING :
	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	 {
     I2Cstate=0;                      			// si erreur retour à l'état 0 et STOP
	 I2Cerror=1;
     I2Cindx=0;
     I2C_Cmd(STOP);
	 }
    else
	{
	I2CTRN=I2CSubAD|0x80;
	I2Cstate++;
	}

	break;



    // 
    // Adresse lue, on écrit les données et on lance STOP si fini
    //
	case W_SUB_AD_WRITING :  			 	
	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	 {
     I2Cstate=0;                      			// si erreur retour à l'état 0 et STOP
	 I2Cerror=1;
     I2Cindx=0;
     I2C_Cmd(STOP);
	 }
    else
     {   
     if(I2Cindx<I2CCount_send)						// sinon tant qu'il y a	des octets on émet
	  I2CTRN=*(I2C_Pstring_send+(I2Cindx++));     
	 else
      {
      I2Cstate++;								// plus d'octets, on envoie le stop
	  I2Cindx=0;
      I2C_Cmd(STOP);	
	  }
     }
	break;


    // 
    // STOP terminé
    //
	case W_STOPING :
    I2Cindx=0;
 	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	{
     I2Cstate=0;                      			// si erreur retour à l'état 0 et STOP
	 I2Cerror=1;
     I2C_Cmd(STOP);								// pour nouvelle tentative	
    }
	else	
	{
	I2Ccycleinprogress=0;
	}
    break;


    /******** Cycles d'une procédure de lecture sur l'esclave ************/



    // 
    // lancement procédure de lecture (par appel classique)
    //
	case R_INIT :			
	I2C_Cmd(START);
	I2Ccycleinprogress=1;
    I2Cindx=0;
	I2Cstate++;
	break;



    // 
    // START terminé, envoie de l'adresse de l'esclave
    //
	case R_STARTING :
	I2CTRN=SLAVE_AD*2+0;   						// cycle de lecture : W=1
	I2Cstate++;
	break;



    // 
    // Adresse reçue  
    // on envoie l'adresse du registre de l'esclave
    //
    case R_AD_WRITING :
	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	 {
     I2Cstate=R_INIT;                 			// si erreur retour à l'état R_INIT et STOP
	 I2Cerror=1;							    // ce qui relance la séquence
     I2Cindx=0;
     I2C_Cmd(STOP);
	 }
    else  
	 {
     I2Cstate++;
	 I2CTRN=I2CSubAD|0x80;							// transmission sub-adresse + incrément auto
     }
	break;

	//
	//  Adresse registre reçue, lancement de la commande RESTART pour changement sens bus 
	//
	case R_SUB_AD_WRITING :
	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	 {
     I2Cstate=R_INIT;                 			// si erreur retour à l'état R_INIT et STOP
	 I2Cerror=1;							    // ce qui relance la séquence
     I2Cindx=0;
     I2C_Cmd(STOP);
	 }
    else  
	 {
     I2C_Cmd(RSTART);
     I2Cstate++;
     }
	break;
    

	// 
    // RSTART terminé, envoie commande mode read 
    //
	case R_RESTARTING :
     I2CTRN=SLAVE_AD*2+1;						// adresse esclave pour lecture	 
     I2Cstate++;
    break;

	// 
    // Adresse reçue ou données envoyée 
    // on repasse en mode réception pour la donnée suivante
    //
	case R_READ_STARTING :  			 			
	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	 {
     I2Cstate=R_INIT;                 			// si erreur retour à l'état R_INIT et STOP
	 I2Cerror=1;								    // ce qui relance la séquence
     I2Cindx=0;
     I2C_Cmd(STOP);
	 }
    else  
     {
     I2C_Cmd(RCEN);								// receive mode	
     I2Cstate++;
     }
    break;
    

    case R_RECEIVING :

 *(I2C_Pstring_rec+(I2Cindx++))=I2CRCV;
	if(I2Cindx<I2CCount_rec)						// sinon tant qu'il y a	des octets on reçoit
      {
	  I2C_Cmd(ACK);
      }
	else
	  {
      I2C_Cmd(NACK);
	  I2Cstate++;
      }
	break;


	case R_STOPING :      			 			// stop terminé
    I2Cindx=0;
 	if(I2CSTATbits.ACKSTAT==1)		 			// on teste l'ACK de l'esclave
	{
     I2Cstate=R_INIT;                 			// si erreur retour à l'état 0 et STOP
	 I2Cerror=1;
     I2C_Cmd(STOP);								// pour nouvelle tentative	
    }
	else	
	{
	I2Ccycleinprogress=0;
	}
    break;

}

}



/***********************************************/
/*        Routines I2C haut niveau             */
/***********************************************/

// Ecriture d'une chaine sur le bus (le premier octet peut être l'adresse d'écriture sur l'escave)
void I2C_Write_Data(unsigned char subad,unsigned char * data,unsigned int length)
{
 while(I2Ccycleinprogress);	// attente cycle précédent terminé
 I2C_Pstring_send=data;
 I2CCount_send=length;
 I2CSubAD=subad;
 I2Cstate=W_INIT;
 isr_I2C();
}

// Lecture de données sur l'esclave à partir de l'adresse ad
void I2C_Read_Data(unsigned char subad,unsigned char * data,unsigned int length)
{
 while(I2Ccycleinprogress);	// attente cycle précédent terminé
 I2C_Pstring_rec=data;
 I2CCount_rec=length;
 I2CSubAD=subad;
 I2Cstate=R_INIT;
 isr_I2C();
}
