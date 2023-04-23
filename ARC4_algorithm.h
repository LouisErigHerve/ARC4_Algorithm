/*
 ============================================================================
 Name        : ARC4_algorithm.h
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2023 - April - 23
 Copyright   : None
 Description : ARC4 encryption / decryption library header
 ============================================================================
 */

#ifndef ARC4_ALGORITHM_H_
#define ARC4_ALGORITHM_H_


/* Include ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


/* Define -------------------------------------------------------------------*/


/* External variables -------------------------------------------------------*/


/* Typedef ------------------------------------------------------------------*/


/* Function prototypes -----------------------------------------------------*/
void ARC4_KSA_Generation(uint8_t * KSAOutput, uint8_t * Key, uint32_t KeyLength);
void ARC4_Key_Stream_Generation(uint8_t * KSAInput, uint8_t * KeyStreamOutput, uint32_t KeyStreamOutputLen);
void ARC4_swap_bytes(uint8_t * p1, uint8_t * p2);


#endif /* ARC4_ALGORITHM_H_ */

/* End of file */
