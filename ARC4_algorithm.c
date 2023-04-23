/*
 ============================================================================
 Name        : ARC4_algorithm.c
 Author      : Louis-Erig HERVE
 Version     : 1.0
 Date        : 2023 - April - 23
 Copyright   : None
 Description : ARC4 encryption / decryption library source
 ============================================================================
 */


/* Include ------------------------------------------------------------------*/
#include "ARC4_algorithm.h"


/* Global variables ---------------------------------------------------------*/


/* Functions ----------------------------------------------------------------*/

/*
 * @brief : This function generates the Key-scheduling algorithm (KSA)
 *          This algorithm is not exactly the same as the original ARC4
 *          encryption, it is a modified version to match with the
 *          Motorola MotoTRBO encryption algorithm.
 *
 * @param KSAOutput : Byte array of 256 bytes
 *
 * @param Key : Byte array witch contains the key
 *
 * @param KeyLen : The length of the key in byte
 *   @note : If the key is 40 bit, it length is 5 bytes (40 / 8), so
 *           the argument "5" must be passed to the function
 *   @note : If the key is 72 bit, it length is 9 bytes (72 / 8), so
 *           the argument "9" must be passed to the function
 *
 * @return None
 */
void ARC4_KSA_Generation(uint8_t * KSAOutput, uint8_t * Key, uint32_t KeyLength)
{
  uint32_t i, j;

  /* 1st Step : KSA array initialization */
  for(i = 0; i < 256; i++)
  {
    KSAOutput[i] = i;
  }

  /* Re-init indexes */
  i = 0;
  j = 0;

  /* 2nd Step : KSA array computing and filling */
  for(i = 0; i < 256; i++)
  {
    /* The "% 256" can be replaced by "& 0xFF" */
    /* j = (j + KSAOutput[i] + Key[i % KeyLength]) % 256; */
    j = (j + KSAOutput[i] + Key[i % KeyLength]) & 0xFF;

    /* Swap bytes of the KSA array */
    ARC4_swap_bytes(&KSAOutput[i], &KSAOutput[j]);
  }
} /* End ARC4_KSA_Generation() */


/*
 * @brief : This function execute the pseudo-random generation algorithm (PRGA)
 *          to generate the KeyStreamOutput.
 *
 * @param KSAInput : Pointer of the Key-scheduling algorithm (KSA) array (previously
 *                   computed by the "ARC4_KSA_Generation()" function)
 *
 * @param KeyStreamOutput : Array pointer of the key stream
 *
 * @param KeyStreamOutputLen : Number of byte of the key stream array
 *
 * @return None
 */
void ARC4_Key_Stream_Generation(uint8_t * KSAInput, uint8_t * KeyStreamOutput, uint32_t KeyStreamOutputLen)
{
  uint32_t i, j, Id, Len;
  uint8_t EncryptingByte;

  Len = KeyStreamOutputLen;
  i = 0;
  j = 0;
  Id = 0;

  /* Loop until all byte have not been encrypted */
  while(Len)
  {
    Len--;
    i = (i + 1) & 0xFF;
    j = (j + KSAInput[i]) & 0xFF;
    ARC4_swap_bytes(&KSAInput[i], &KSAInput[j]);
    EncryptingByte = KSAInput[(KSAInput[i] + KSAInput[j]) & 0xFF];
    KeyStreamOutput[Id++] = EncryptingByte;
  }
} /* End ARC4_Key_Stream_Generation() */


/*
 * @brief : This function swap two byte in a tab
 *
 * @param p1 : Pointer of the first byte to swap
 *
 * @param p2 : Pointer of the second byte to swap
 *
 * @return None
 */
void ARC4_swap_bytes(uint8_t * p1, uint8_t * p2)
{
  uint8_t Temp = *p1;
  *p1 = *p2;
  *p2 = Temp;
} /* End ARC4_swap_bytes() */


/* End of file */
