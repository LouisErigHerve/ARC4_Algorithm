# sudo apt-get update
# sudo apt-get install make gcc
#
# Call this script with the following syntax:
# Standard GCC
# make all clean
#
# Compiling with MinGW32 GCC (by using Cygwin on Windows)
# make SPECIFIC_CC=i686-w64-mingw32-gcc specific_gcc clean
#
# Compiling with MinGW64 GCC (by using Cygwin on Windows)
# make SPECIFIC_CC=x86_64-w64-mingw32-gcc specific_gcc clean
#

CC = gcc
#CC = x86_64-w64-mingw32-gcc
#CC = x86_64-w64-mingw32-gcc-11
#CC = i686-w64-mingw32-gcc
#CC = i686-w64-mingw32-gcc-11

CFLAGS = -O3 -Wall -c -fmessage-length=0 -std=c99 -o

all:
	$(CC) $(CFLAGS) main.o main.c
	$(CC) $(CFLAGS) ARC4_algorithm.c ARC4_algorithm.c
	$(CC) -o ARC4_algorithm ARC4_algorithm.o main.o

specific_gcc:
	$(SPECIFIC_CC) $(CFLAGS) main.o main.c
	$(SPECIFIC_CC) $(CFLAGS) ARC4_algorithm.o ARC4_algorithm.c
	$(SPECIFIC_CC) -o ARC4_algorithm ARC4_algorithm.o main.o

clean:
	rm -rf *.o
