# ARC4_Algorithm
A simple command line tool to encrypt / decrypt some data using the well known ARC4 algorithm

## Compiling

### See makefile

Using **GCC on Linux or on Cygwin**

    make all
OR

    make all clean
(to clean .o files after compiling)


Using **MinGW GCC 64 bits on Windows** (compilation made under Cygwin with correct packages installed)

    make SPECIFIC_CC=x86_64-w64-mingw32-gcc specific_gcc clean

Using **MinGW GCC 32 bits on Windows** (compilation made under Cygwin with correct packages installed)

    make SPECIFIC_CC=i686-w64-mingw32-gcc specific_gcc clean

Using any other compiler

    make SPECIFIC_CC=the-name-of-your-compiler specific_gcc clean

## Usage

    ARC4_Algorithm -k [Encryption Key] -i [input data do cipher/decipher]
    
    [Encryption Key]    : An hexadecimal ASCII key (up to 64 bytes [128 ASCII characters or 512 bits key])
                          Example : "12"                 = 1 byte  ( 8 bits key)
                          Example : "ABCD"               = 2 bytes (16 bits key)
                          Example : "AABBCCDDEE"         = 5 bytes (40 bits key)
                          Example : "AABBCCDDEEFF112233" = 9 bytes (72 bits key)
                          Example : "000000000000000001" = 9 bytes (72 bits key)
                          Example : "A"                  = Will be considered as 1 byte [0xA0] (8 bits key)
                          Note    : For good decoding a key length with a multiple of 8 bits should be preferred [8, 16, 24, 32, 40, 44, 48... bits]
    
    [input data do encrypt/decrypt] : An hexadecimal ASCII string to cipher or decipher (up to 4096 bytes [8192 ASCII characters])
                          Example : "DEADBEEF"           = 4 bytes (32 bits) of data to cipher/decipher
                          Example : "CAFEDECADEADBEEF"   = 8 bytes (64 bits) of data to cipher/decipher
                          Example : "ABC"                = will be considered as 2 bytes (16 bits : [0xAB-0xC0]) of data to cipher/decipher

## Examples

Encrypt the following HEX string  : `"00112233445566778899AABBCCDDEEFF"` (total 16 bytes)
With the following encryption key : `"DEADBEEF"` (total 4 bytes)

Call the program with the following syntax :

    ARC4_Algorithm -k "DEADBEEF" -i "00112233445566778899AABBCCDDEEFF"

The argument `-k [Encryption Key]` is mandatory, launching the software without this argument will causes an error

The argument `-i [input data do cipher/decipher]` is optional, if no argument is passed, then the tool will display at output the key stream produced by the ARC4 algorithm (4096 bytes will be diplayed as defined by the constant `MAX_OUTPUT_KEY_STREAM_LENGTH`).

**Note :**
To ensure a good working of this software it is preferable to pass a key and data with a multiple of 8 bits (8, 16, 24, 32, 40... bits).

## Limitations

The encryption key length (parameter `-k [Encryption Key]`) is limited by the constant `MAX_ARC4_INPUT_KEY_LENGTH` to **64 bytes**

The input data to cipher/decipher length (parameter `-i [input data do cipher/decipher]`) is limited by the constant `MAX_OUTPUT_KEY_STREAM_LENGTH` to **4096 bytes**

Modify these two constant if you want to increase the capability of this software

