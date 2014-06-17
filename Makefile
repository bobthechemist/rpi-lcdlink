# This makefile can be used to build the lcdlink
# program.  Presently, there is only one program
# to make, so typing 'make' or 'make lcdlink' will
# generate the same result.  'make clean' will remove
# object files but will NOT remove the binary file created.
# File adopted from examples located under MLINKDIR

# While this is working, it can be cleaned up.

# Portions of this makefile require the use of GNU make.
# see http://www.gnu.org/software/make for more information.

VERSION=10.0
MLINKDIR = /opt/Wolfram/WolframEngine/10.0/SystemFiles/Links/MathLink/DeveloperKit/Linux-ARM
SYS = Linux-ARM
CADDSDIR = ${MLINKDIR}/CompilerAdditions
EXTRA_CFLAGS=

INCDIR = ${CADDSDIR}
LIBDIR = ${CADDSDIR}

MPREP = ${CADDSDIR}/mprep
RM = rm

CC = gcc
CXX = /usr/bin/g++

BINARIES = lcdlink

all : $(BINARIES)

lcdlink : lcdlinktm.o lcdlink.o
	${CXX} ${EXTRA_CFLAGS} -I${INCDIR} lcdlinktm.o lcdlink.o -L${LIBDIR} -lML32i4 -lm -lpthread -lrt -lstdc++ -ldl -l wiringPi -lwiringPiDev -o $@



.c.o :
	${CC} -c ${EXTRA_CFLAGS} -I${INCDIR} $<


lcdlinktm.c : lcdlink.tm
	${MPREP} $? -o $@



clean :
	@ ${RM} -rf *.o *tm.c 
