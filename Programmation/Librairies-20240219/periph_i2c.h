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

#ifndef I2C_H
#define I2C_H

//Adresse esclave (acc�lerom�tre : 0011101)
#define SLAVE_AD					0x1D

// d�finition de l'�tat de l'automate de trame pour la routine d'interruption
#define  W_INIT							0
#define  W_STARTING 					1 
#define  W_AD_WRITING 					2
#define  W_SUB_AD_WRITING 				3
#define  W_TESTING_ACK_AFTER_TRANSMIT 	4
#define  W_STOPING						5


#define  R_INIT 					    6
#define  R_STARTING 					7
#define  R_AD_WRITING				 	8
#define  R_SUB_AD_WRITING				9
#define  R_RESTARTING					10
#define  R_READ_STARTING 				11
#define  R_RECEIVING                    12
#define  R_STOPING	 					13


// d�finition des actions �mises par le maitre
#define START 	1
#define RSTART 	2
#define STOP 	4
#define RCEN	8
#define ACK 	16
#define NACK 	48


// initialisation AD SLAVE sur 7bits, 100kHz
void I2Cinit(void);

// routine d'interruption
void __attribute__((__interrupt__)) _MI2CInterrupt( void );

// Emission des signaux de commande (uniquement pour la gestion bas niveau)
void I2C_Cmd(unsigned char commande);

// gestionnaire d'�v�nements I2C
void isr_I2C(void);

// �criture de donn�es vers l'esclave
void I2C_Write_Data(unsigned char subad,unsigned char * data,unsigned int length);

// lecture de donn�es depuis l'esclave
void I2C_Read_Data(unsigned char subad,unsigned char * data,unsigned int length);

#endif
