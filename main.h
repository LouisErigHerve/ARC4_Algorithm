/*
 ============================================================================
 Name        : main.h
 Author      : Louis-Erig HERVE - F4HUZ
 Version     : 1.0
 Date        : 2023 - April - 24
 Copyright   : None
 Description : ARC4_Algorithm main program header
 ============================================================================
 */

#ifndef MAIN_H_
#define MAIN_H_


#ifdef __cplusplus
extern "C" {
#endif


/* Include ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include "ARC4_Algorithm.h"


/* Define -------------------------------------------------------------------*/
#define MAX_ARC4_INPUT_KEY_LENGTH       64  /* Input key length = 64 bytes maximum */
#define MAX_OUTPUT_KEY_STREAM_LENGTH  4096  /* Max 4096 byte of key stream produced a output */


/* External variables -------------------------------------------------------*/


/* Typedef ------------------------------------------------------------------*/


/* Function prototypes -----------------------------------------------------*/
uint32_t ConvertAsciiToString(uint8_t * Input, size_t InputLength, uint8_t * Output);
uint32_t ConvertAsciiToByte(uint8_t AsciiMsbByte, uint8_t AsciiLsbByte, uint8_t * OutputByte);
void PrintHex(uint8_t * ByteArray, uint32_t Length, uint8_t * Delimiter, uint32_t MaxValuesPerLine);
void usage(void);


#ifdef __cplusplus
}
#endif


#endif /* MAIN_H_ */

/* End of file */
