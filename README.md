rpi-lcdlink
===========

Mathlink code to interact with the Adafruit RGB LCD plate on a RPi.  Uses WiringPi 

Installation
============
Make sure that you have WiringPi installed.  See www.wiringpi.com/download-and-install/

the gpio i2c module needs to be loaded with:

gpio load i2c

Compile with:

mcc -o lcdlink lcdlink.c lcdlink.tm -I/usr/local/include -lwiringPi -lwiringPiDev -lpthread -lm


or with:

make lcdlink

Version
=======

No versioning tags yet.  Latest version includes Makefile to simplify
compiling, usage descriptions for all public functions and a modification
to lcdPuts that allows position assignment as does lcdPutc.

