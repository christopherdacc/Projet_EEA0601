/***********************************************************
************************************************************
*
* Fichier de configuration et de gestion de la liaison RS232
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/

#include "p30f4012.h"
#include "dsp.h"
#include "periph_gen.h"
#include "periph_uart.h"

// -------------------------------
// U1MOD: UART1 Mode Register
// -------------------------------

/*

bit 15 UARTEN: UART Enable bit
	1 = UART is enabled. UART pins are controlled by UART as defined by UEN<1:0> and UTXEN control bits.
	0 = UART is disabled. UART pins are controlled by corresponding PORT, LAT, and TRIS bits.

bit 14 Unimplemented: Read as ‘0’

bit 13 USIDL: Stop in Idle Mode bit
	1 = Discontinue operation when device enters Idle mode
	0 = Continue operation in Idle mode

bit 12 Unimplemented: Read as ‘0’

bit 11 Reserved: Write ‘0’ to this location

bit 10 ALTIO: UART Alternate I/O Selection bit
	1 = UART communicates using UxATX and UxARX I/O pins
	0 = UART communicates using UxTX and UxRX I/O pins
	Note: The alternate UART I/O pins are not available on all devices. See device data sheet for details.

bit 9-8 Reserved: Write ‘0’ to these locations

bit 7 WAKE: Enable Wake-up on Start bit Detect During Sleep Mode bit
	1 = Wake-up enabled
	0 = Wake-up disabled

bit 6 LPBACK: UART Loopback Mode Select bit
	1 = Enable Loopback mode
	0 = Loopback mode is disabled

bit 5 ABAUD: Auto Baud Enable bit
	1 = Input to Capture module from UxRX pin
	0 = Input to Capture module from ICx pin

bit 4-3 Unimplemented: Read as ‘0’

bit 2-1 PDSEL<1:0>: Parity and Data Selection bits
	11 = 9-bit data, no parity
	10 = 8-bit data, odd parity
	01 = 8-bit data, even parity
	00 = 8-bit data, no parity

bit 0 STSEL: Stop Selection bit
	1 = 2 Stop bits
	0 = 1 Stop bit
*/

// -------------------------------
// U1STA: UART1 Status and Control Register
// -------------------------------


/*

bit 15 UTXISEL: Transmission Interrupt Mode Selection bit
	1 = Interrupt when a character is transferred to the Transmit Shift register and as result, the transmit buffer
	becomes empty
	0 = Interrupt when a character is transferred to the Transmit Shift register (this implies that there is at least
	one character open in the transmit buffer)

bit 14-12 Unimplemented: Read as ‘0’

bit 11 UTXBRK: Transmit Break bit
	1 = UxTX pin is driven low, regardless of transmitter state
	0 = UxTX pin operates normally

bit 10 UTXEN: Transmit Enable bit
	1 = UART transmitter enabled, UxTX pin controlled by UART (if UARTEN = 1)
	0 = UART transmitter disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled
	by PORT.

bit 9 UTXBF: Transmit Buffer Full Status bit (Read Only)
	1 = Transmit buffer is full
	0 = Transmit buffer is not full, at least one more data word can be written

bit 8 TRMT: Transmit Shift Register is Empty bit (Read Only)
	1 = Transmit shift register is empty and transmit buffer is empty (the last transmission has completed)
	0 = Transmit shift register is not empty, a transmission is in progress or queued in the transmit buffer

bit 7-6 URXISEL<1:0>: Receive Interrupt Mode Selection bit
	11 =Interrupt flag bit is set when Receive Buffer is full (i.e., has 4 data characters)
	10 =Interrupt flag bit is set when Receive Buffer is 3/4 full (i.e., has 3 data characters)
	0x =Interrupt flag bit is set when a character is received

bit 5 ADDEN: Address Character Detect (bit 8 of received data = 1)
	1 = Address Detect mode enabled. If 9-bit mode is not selected, this control bit has no effect.
	0 = Address Detect mode disabled

bit 4 RIDLE: Receiver Idle bit (Read Only)
	1 = Receiver is Idle
	0 = Data is being received

bit 3 PERR: Parity Error Status bit (Read Only)
	1 = Parity error has been detected for the current character
	0 = Parity error has not been detected

bit 2 FERR: Framing Error Status bit (Read Only)
	1 = Framing Error has been detected for the current character
	0 = Framing Error has not been detected

bit 1 OERR: Receive Buffer Overrun Error Status bit (Read/Clear Only)
	1 = Receive buffer has overflowed
	0 = Receive buffer has not overflowed
bit 0 URXDA: Receive Buffer Data Available bit (Read Only)
	1 = Receive buffer has data, at least one more character can be read
	0 = Receive buffer is empty
*/



// -------------------------------
// U1RXREG: UART1 Receive Register
// -------------------------------

/*
bit 15-9 Unimplemented: Read as ‘0’
bit 8 URX8: Data bit 8 of the Received Character (in 9-bit mode)
bit 7-0 URX<7:0>: Data bits 7-0 of the Received Character
*/



// -------------------------------
// U1TXREG: UARTX Transmit Register (Write Only)
// -------------------------------

/*
bit 15-9 Unimplemented: Read as ‘0’
bit 8 UTX8: Data bit 8 of the Character to be Transmitted (in 9-bit mode)
bit 7-0 UTX<7:0>: Data bits 7-0 of the Character to be Transmitted
*/


// -------------------------------
// U1BRG: UART1 Baud Rate Register
// -------------------------------
/*
bit 15-0 BRG<15:0>: Baud Rate Divisor bits
U1BRG=Fcy/(16*baudrate)-1

*/

// initialisation de la liaison série 
void SERIALinit(unsigned int baudrate)
{

U1MODE= 0b0000010000000000;			// module off sur alt, 8 bits , no parity, 1 stop
U1STA=  0b0000000000000000; 	    // transmission inactive, 
									// interruption pour 1 carac RX
									// pas de gestion d'erreurs
U1BRG=Fcy/16/baudrate-1;	   	    // 
U1MODEbits.UARTEN=1;				// mise en route module
U1STAbits.UTXEN=1;					// autoriser la transmission

}


// test caractère présent dans buffer 
unsigned int SERIALReadCharReceived()
{
 return U1STAbits.URXDA;
}



// routine d'écriture d'un caractère sur liaison série 
void SERIALWrite(char c)
{
while(!U1STAbits.TRMT);  // attente émission prête
	U1TXREG=c;
}

// routine de lecture d'un caractère sur liaison série 
char SERIALRead()
{
return U1RXREG;
}
