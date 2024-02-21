/***********************************************************
************************************************************
*
* Fichier de déclarations générales
*
*           D. CARTON, M. COLAS - Mars 2008
*                        V 1.2
************************************************************
***********************************************************/


#ifndef GEN_H
#define GEN_H


#define Fcy 29488000  // Fréquence de cycle

typedef unsigned char BYTE;
typedef unsigned int WORD;


union _BITFIELD{
 unsigned int WORD;
 struct 
 {
  unsigned char BYTEH;
  unsigned char BYTEL;
 }BYTE;
 
 struct  
 {
  unsigned int B15:1;
  unsigned int B14:1;
  unsigned int B13:1;
  unsigned int B12:1;
  unsigned int B11:1;
  unsigned int B10:1;
  unsigned int B9:1;
  unsigned int B8:1;
  unsigned int B7:1;
  unsigned int B6:1;
  unsigned int B5:1;
  unsigned int B4:1;
  unsigned int B3:1;
  unsigned int B2:1;
  unsigned int B1:1;
  unsigned int B0:1;
 }BITS;
};




typedef union _BITFIELD BITFIELD;


typedef enum _BOOL
{
FALSE=0,
TRUE,
} BOOL;



#endif
