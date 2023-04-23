/*
 ============================================================================
 Name        : main.c
 Author      : Louis-Erig HERVE - F4HUZ
 Version     : 1.0
 Date        : 2023 - April - 24
 Copyright   : None
 Description : ARC4_Algorithm main program source
 ============================================================================
 */


/* Include ------------------------------------------------------------------*/
#include "main.h"


/* Define -------------------------------------------------------------------*/


/* Global variables ---------------------------------------------------------*/


/* Functions ----------------------------------------------------------------*/


/*
 * @brief : Main program of "Motorola_EP_KEY_Finder" application
 *
 * @param argc : Number of arguments in the call command line
 *
 * @param argv : Pointer to call command line arguments
 *
 * @return 0 Execution correct
 *         Others = Execution error
 *
 */
int main(int argc, char *argv[])
{
  uint32_t i = 0;
  time_t   rawtime;
  struct tm * timeinfo = NULL;
  uint32_t ErrorFlag = 0;
  size_t   InputKeyLen = 0;
  size_t   NbOfInputASCIIDataToCipher = 0;
  size_t   NbOfOutputDataToCipher = 0;
  size_t   EncryptionKeyLen = 0;
  uint8_t  EncryptionKey[MAX_ARC4_INPUT_KEY_LENGTH] = {0};
  uint8_t  DataToCipher[MAX_OUTPUT_KEY_STREAM_LENGTH] = {0};
  uint8_t  ARC4KeyStreamOutput[MAX_OUTPUT_KEY_STREAM_LENGTH] = {0};
  uint8_t  KSA[256] = {0};
  int32_t  c;

  if(argc == 1)
  {
    usage();
    exit(0);
  }

  while((c = (int32_t)getopt (argc, argv, "hi:k:")) != -1)
  {
    opterr = 0;

    switch(c)
    {
      /* -h : Help */
      case 'h':
      {
        usage();
        exit(0);
      }

      /* -i : Specify the ASCII string (in hex format) to cipher/decipher */
      case 'i':
      {
        /* Get the length of the data to cipher/decipher */
        NbOfInputASCIIDataToCipher = strlen(optarg);

        /* Check the number of ASCII bytes */
        if(NbOfInputASCIIDataToCipher > (MAX_OUTPUT_KEY_STREAM_LENGTH * 2))
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : The input data to cipher/decipher MUST not exceed %u ASCII characters\n", MAX_OUTPUT_KEY_STREAM_LENGTH * 2);
          printf("\n");
          usage();
          exit(0);
        }

        /* Compute the key length (the length will change if it an even or an odd number */
        if((NbOfInputASCIIDataToCipher % 2) == 0) NbOfOutputDataToCipher = NbOfInputASCIIDataToCipher / 2; /* Even number */
        else NbOfOutputDataToCipher = (NbOfInputASCIIDataToCipher / 2) + 1; /* Odd number */

        /* Convert input data to cipher/decipher from an ASCII style to a real hex format */
        ErrorFlag = ConvertAsciiToString((uint8_t *)optarg, NbOfInputASCIIDataToCipher, DataToCipher);

        if(ErrorFlag == 0)
        {
          /* No error */
        }
        else if(ErrorFlag == 1)
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : Please check that your data to cipher/decipher (\"%s\") only contains ACSII characters in the range [0..9] and [a..f] or [A..F]\n", optarg);
          printf("\n");
          usage();
          exit(0);
        }
        else
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : Input data to cipher/decipher : Unknown error\n");
          printf("\n");
          usage();
          exit(0);
        }
        break;
      }

      /* -k : Specify encryption key (in hex format) */
      case 'k':
      {
        /* Get the length of the data to cipher/decipher */
        InputKeyLen = strlen(optarg);

        /* Check the number of ASCII bytes */
        if((InputKeyLen > (MAX_ARC4_INPUT_KEY_LENGTH * 2)) || (InputKeyLen == 0))
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : The key length MUST be in the range [1..%u] byte(s)\n", MAX_ARC4_INPUT_KEY_LENGTH);
          usage();
          exit(0);
        }

        /* Compute the key length (the length will change if it an even or an odd number */
        if((InputKeyLen % 2) == 0) EncryptionKeyLen = InputKeyLen / 2; /* Even number */
        else EncryptionKeyLen = (InputKeyLen / 2) + 1; /* Odd number */

        /* Convert input key from an ASCII style to a real hex format */
        ErrorFlag = ConvertAsciiToString((uint8_t *)optarg, InputKeyLen, EncryptionKey);

        if(ErrorFlag == 0)
        {
          /* No error */

          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("The encryption key used will be (hex format) : ");
          PrintHex(EncryptionKey, EncryptionKeyLen, (uint8_t *)"-", 32);
          printf("\n");
          fflush(stdout);
        }
        else if(ErrorFlag == 1)
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : The encryption key ASCII characters MUST be in the range [0..9] and [a..f] or [A..F], others characters are invalid\n");
          usage();
          exit(0);
        }
        else
        {
          /* Get the current time */
          time(&rawtime);
          timeinfo = localtime(&rawtime);

          /* Print the current time */
          printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
              timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

          printf("ERROR : Input data to cipher/decipher : Unknown error\n");
          usage();
          exit(0);
        }
        break;
      }

      default:
      {
        usage();
        exit(0);
      }
    } /* End switch(c) */
  }

  /* Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  /* Print the current time */
  printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
      timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  printf("Launching the program\r\n");
  fflush(stdout);

  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */

  /* Check if the encryption key is valid */
  if(EncryptionKeyLen == 0)
  {
    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
        timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("The encryption key has not been specified, exiting the program...\r\n");
    fflush(stdout);
    exit(0);
  }

  /* Check the output data length */
  if(NbOfOutputDataToCipher == 0)
  {
    /* By default, produce the max length of key stream at output */
    NbOfOutputDataToCipher = MAX_OUTPUT_KEY_STREAM_LENGTH;

    /* Get the current time */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* Print the current time */
    printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
        timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    printf("The input data has not been specified, so produce %u bytes of key stream at output\r\n", MAX_OUTPUT_KEY_STREAM_LENGTH);
    fflush(stdout);
  }

  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */

  /* Step 1 : Generate the ARC4 KSA */
  ARC4_KSA_Generation(KSA, EncryptionKey, EncryptionKeyLen);

  /* Step 2 : Generate the ARC4 key stream */
  ARC4_Key_Stream_Generation(KSA, ARC4KeyStreamOutput, NbOfOutputDataToCipher);

  /* Step 3 : Encrypt/decrypt (cipher/decipher) input data to produce output data */
  for(i = 0; i < NbOfOutputDataToCipher; i++)
  {
    DataToCipher[i] ^= (ARC4KeyStreamOutput[i] & 0xFF);
  }

  /* Step 4 : Display the content of the data ciphered/deciphered */
  /* Get the current time */
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  /* Print the current time */
  printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
      timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  printf("Output data (hex format) =\n");
  PrintHex(DataToCipher, NbOfOutputDataToCipher, (uint8_t *)"-", 32);
  printf("\n");
  printf("\n");
  fflush(stdout);

  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */
  /* ----------------------------------------------------------------------- */

  /* Print the current time */
  printf("[%04d-%02d-%02d %02d:%02d:%02d] ", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
      timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  printf("Exiting the program\r\n");
  fflush(stdout);

  return EXIT_SUCCESS;
} /* End main() */


/*
 * @brief : This function convert the the input command line from an ASCII-hex style
 *          to a real hexadecimal string format
 *
 * @param Input : The ASCII string (in hexadecimal format)
 *   @arg Example : "ABCDEF0123456789" contains 16 ASCII bytes
 *                  and will be converted into a 8 bytes string
 *                  like Output = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89}
 *
 *   @arg Example : "ABC" contains 3 ASCII bytes
 *                  and will be converted into a 2 bytes string
 *                  like Output = {0xAB, 0xC0}
 *
 * @param Length : The number of ASCII bytes to convert
 *
 * @param Output : The output string containing assembled data
 *
 * @return 0 = Conversion OK
 *         1 = Error => The input numbers are not in the correct range (not ASCII style)
 */
uint32_t ConvertAsciiToString(uint8_t * Input, size_t InputLength, uint8_t * Output)
{
  uint32_t ErrorFlag = 0;
  uint32_t i = 0;
  uint32_t j = 0;
  uint32_t MSBByte = '0';
  uint32_t LSBByte = '0';

  for(i = 0, j = 0; i < InputLength; i += 2, j++)
  {
    /* When InputLength is not a multiple of 2, replace the invalid
     * byte by a '0' ASCII character */
    if((i + 0) < InputLength) MSBByte = Input[i + 0];
    else MSBByte = '0';

    /* When InputLength is not a multiple of 2, replace the invalid
     * byte by a '0' ASCII character */
    if((i + 1) < InputLength) LSBByte = Input[i + 1];
    else LSBByte = '0';

    /* Convert 2 ASCII hex character into 1 byte */
    ErrorFlag = ConvertAsciiToByte(MSBByte, LSBByte, &Output[j]);

    /* Check if an error has been detected */
    if(ErrorFlag) break;
  }

  return ErrorFlag;
} /* End ConvertAsciiToString() */


/*
 * @brief : This function convert two ASCII bytes into one byte
 *          Example : 'A' (0x41) and '9' (0x39) will give an
 *                    output byte value of 0xA9
 *
 * @param AsciiMsbByte : The ASCII byte of the MSByte
 *   @arg Range ['0'..'9'] or ['a'..'f'] or ['A'..'F']
 *
 * @param AsciiLsbByte : The ASCII byte of the LSByte
 *   @arg Range ['0'..'9'] or ['a'..'f'] or ['A'..'F']
 *
 * @param OutputByte : The output pointer of the generated byte
 *
 * @return 0 = Conversion OK
 *         1 = Error => The input numbers are not in the correct range
 */
uint32_t ConvertAsciiToByte(uint8_t AsciiMsbByte, uint8_t AsciiLsbByte, uint8_t * OutputByte)
{
  uint32_t ErrorFlag = 0;
  uint8_t  Temp = 0;

  *OutputByte = 0;

  /* Check if the MSB byte is in the range ['0'..'9'] */
  if((AsciiMsbByte >= '0') && (AsciiMsbByte <= '9'))
  {
    Temp = ((AsciiMsbByte - '0') << 4) & 0xF0;
  }
  /* Check if the MSB byte is in the range ['A'..'F'] */
  else if((AsciiMsbByte >= 'A') && (AsciiMsbByte <= 'F'))
  {
    Temp = ((AsciiMsbByte - 'A' + 0x0A) << 4) & 0xF0;
  }
  /* Check if the MSB byte is in the range ['a'..'f'] */
  else if((AsciiMsbByte >= 'a') && (AsciiMsbByte <= 'f'))
  {
    Temp = ((AsciiMsbByte - 'a'  + 0x0A) << 4) & 0xF0;
  }
  else
  {
    /* Not an ASCII byte in the range ['0'..'9']['a'..'f']['A'..'F'],
     * set the error flag */
    ErrorFlag = 1;
  }

  /* Check if the MSB byte is in the range ['0'..'9'] */
  if((AsciiLsbByte >= '0') && (AsciiLsbByte <= '9'))
  {
    Temp |= ((AsciiLsbByte - '0') & 0x0F);
  }
  /* Check if the MSB byte is in the range ['A'..'F'] */
  else if((AsciiLsbByte >= 'A') && (AsciiLsbByte <= 'F'))
  {
    Temp |= ((AsciiLsbByte - 'A' + 0x0A) & 0x0F);
  }
  /* Check if the MSB byte is in the range ['a'..'f'] */
  else if((AsciiLsbByte >= 'a') && (AsciiLsbByte <= 'f'))
  {
    Temp |= ((AsciiLsbByte - 'a' + 0x0A) & 0x0F);
  }
  else
  {
    /* Not an ASCII byte in the range ['0'..'9']['a'..'f']['A'..'F'],
     * set the error flag */
    ErrorFlag = 1;
  }

  /* Fill the output byte */
  *OutputByte = Temp;

  return ErrorFlag;
} /* End ConvertAsciiToByte() */


/*
 * @brief : This function displays a byte array in hexadecimal
 *
 * @param ByteArray : The byte array table
 *
 * @param Length : The number of byte inside the array table
 *
 * @param Delimiter : A string containing a delimiter to insert
 *                    between two displayed byte
 *   @arg NULL : No delimiter between each data
 *
 * @param MaxValuesPerLine : The number maximum of value to display in
 *                           the same line, once reached a "\n" is automatically
 *                           inserted to go to the next line.
 *   @arg  0 : Unused
 *   @arg -1 : Unused
 *
 * @return None
 */
void PrintHex(uint8_t * ByteArray, uint32_t Length, uint8_t * Delimiter, uint32_t MaxValuesPerLine)
{
  uint32_t i;

  /* Parse all bytes in the tab */
  for(i = 0; i < Length; i++)
  {
    /* Print the byte value in hexadecimal format */
    printf("%02X", ByteArray[i]);

    /* Check if we need to jump to the next line (add an '\n') */
    if((MaxValuesPerLine != 0) && (MaxValuesPerLine != -1) && (((i + 1) % MaxValuesPerLine) == 0))
    {
      printf("\n");
    }
    /* Print the delimiter (if needed) */
    else if((Delimiter != NULL) && (i != (Length -1)))
    {
      printf("%s", Delimiter);
    }
    else
    {
      /* Nothing to do */
    }
  }

  /* Flush the output buffer */
  fflush(stdout);

} /* End PrintHex() */


/*
 * @brief : This function print the command line explanations
 *          for the current software
 *
 * @param  None
 *
 * @return None
 */
void usage(void)
{
  printf("\n");
  printf("This program decode some data by using the ARC4 algorithm\n");
  printf("\n");
  printf("Usage :\n");
  printf("\n");
  printf("ARC4_Algorithm -k [Encryption Key] -i [input data do cipher/decipher]\n");
  printf("\n");
  printf("[Encryption Key]    : An hexadecimal ASCII key (up to %u bytes [%u ASCII characters or %u bits key])\n", MAX_ARC4_INPUT_KEY_LENGTH, MAX_ARC4_INPUT_KEY_LENGTH * 2, MAX_ARC4_INPUT_KEY_LENGTH * 8);
  printf("                      Example : \"12\"                 = 1 byte  ( 8 bits key)\n");
  printf("                      Example : \"ABCD\"               = 2 bytes (16 bits key)\n");
  printf("                      Example : \"AABBCCDDEE\"         = 5 bytes (40 bits key)\n");
  printf("                      Example : \"AABBCCDDEEFF112233\" = 9 bytes (72 bits key)\n");
  printf("                      Example : \"000000000000000001\" = 9 bytes (72 bits key)\n");
  printf("                      Example : \"A\"                  = Will be considered as 1 byte [0xA0] (8 bits key)\n");
  printf("                      Note    : For good decoding a key length with a multiple of 8 bits should be preferred [8, 16, 24, 32, 40, 44, 48... bits]\n");
  printf("\n");
  printf("[input data do encrypt/decrypt] : An hexadecimal ASCII string to cipher or decipher (up to %u bytes [%u ASCII characters])\n", MAX_OUTPUT_KEY_STREAM_LENGTH, MAX_OUTPUT_KEY_STREAM_LENGTH * 2);
  printf("                      Example : \"DEADBEEF\"           = 4 bytes (32 bits) of data to cipher/decipher\n");
  printf("                      Example : \"CAFEDECADEADBEEF\"   = 8 bytes (64 bits) of data to cipher/decipher\n");
  printf("                      Example : \"ABC\"                = will be considered as 2 bytes (16 bits : [0xAB-0xC0]) of data to cipher/decipher\n");
  printf("\n");
  printf("\n");
  fflush(stdout);
} /* End usage() */


/* End of file */

