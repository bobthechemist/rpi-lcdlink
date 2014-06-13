/*
 * lcdlink.c:
 *	WolframLink code for outputting to the Adafruit RGB
 *      LCD plate on a RPi from Mathematica.  This version 
 *      does not attempt to read the state of the 5 buttons.
 *      
 *	Code adapted from WiringPi by Gorden Henderson
 *      https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 * Copyright (c) 2014 BoB LeSuer except for wiringPi components which
 * are Copyright (c) 2012-2013 Gorden Henderson (license below)
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <mcp23017.h>
#include <lcd.h>

#include "mathlink.h"


#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif


// Defines for the Adafruit Pi LCD interface board

#define	AF_BASE		100
#define	AF_RED		(AF_BASE + 6)
#define	AF_GREEN	(AF_BASE + 7)
#define	AF_BLUE		(AF_BASE + 8)

#define	AF_E		(AF_BASE + 13)
#define	AF_RW		(AF_BASE + 14)
#define	AF_RS		(AF_BASE + 15)

#define	AF_DB4		(AF_BASE + 12)
#define	AF_DB5		(AF_BASE + 11)
#define	AF_DB6		(AF_BASE + 10)
#define	AF_DB7		(AF_BASE +  9)

#define	AF_SELECT	(AF_BASE +  0)
#define	AF_RIGHT	(AF_BASE +  1)
#define	AF_DOWN		(AF_BASE +  2)
#define	AF_UP		(AF_BASE +  3)
#define	AF_LEFT		(AF_BASE +  4)

// Global lcd handle:

static int lcdHandle ;

// Example of how a user-defined character is defined.

static unsigned char newChar [8] = 
{
  0b00100,
  0b00100,
  0b00000,
  0b00100,
  0b01110,
  0b11011,
  0b11011,
  0b10001,
} ;










/*
Modified from the WiringPi function, scrollMessage, in lcd.c and accepts
as an argument the text of the message.  No memory allocation checks are
made at this time.  Spaces are pre/appended to the message to improve 
display. 
*/
void scrollMessage (int line, int width, char * msg)
{
  char buf [32] ;
  char *spaces = "                ";
  char *output = malloc(2*strlen(spaces)+strlen(msg)+1);
  static int position = 0 ;
  static int timer = 0 ;

  strcpy(output,spaces);
  strcat(output,msg);
  strcat(output,spaces);

  if (millis () < timer)
    return ;

  timer = millis () + 200 ;

  strncpy (buf, &output [position], width) ;
  buf [width] = 0 ;
  lcdPosition (lcdHandle, 0, line) ;
  lcdPuts (lcdHandle, buf) ;

  if (++position == (strlen (output) - width))
    position = 0 ;
  free(output);
}

/*
 * setBacklightColor:
 *	The colour outputs are inverted.
 *      function named changed from wiringPi version
 *        since I'm afraid of u's :-)
 */

static void setBacklightColor (int color)
{
  color &= 7 ;

  digitalWrite (AF_RED,   !(color & 1)) ;
  digitalWrite (AF_GREEN, !(color & 2)) ;
  digitalWrite (AF_BLUE,  !(color & 4)) ;
}


/*
 * adafruitLCDSetup:
 *	Setup the Adafruit board by making sure the additional pins are
 *	set to the correct modes, etc.
 *
 * Very limited error checking - commands that send error information to stdout
 *   have been commented out for reference.  Other commands sending information
 *   to stdout have been removed.
 */

static void adafruitLCDSetup (int color)
{
  int i ;

//	Backlight LEDs

  pinMode (AF_RED,   OUTPUT) ;
  pinMode (AF_GREEN, OUTPUT) ;
  pinMode (AF_BLUE,  OUTPUT) ;
  setBacklightColor (color) ;

//	Input buttons
//      (Will be set up but not used)

  for (i = 0 ; i <= 4 ; ++i)
  {
    pinMode (AF_BASE + i, INPUT) ;
    pullUpDnControl (AF_BASE + i, PUD_UP) ;	// Enable pull-ups, switches close to 0v
  }

// Control signals

  pinMode (AF_RW, OUTPUT) ; digitalWrite (AF_RW, LOW) ;	// Not used with wiringPi - always in write mode

// The other control pins are initialised with lcdInit ()

  lcdHandle = lcdInit (2, 16, 4, AF_RS, AF_E, AF_DB4,AF_DB5,AF_DB6,AF_DB7, 0,0,0,0) ;

/* Should redirect error handling to some type of Mathlink communication tool

  if (lcdHandle < 0)
  {
    fprintf (stderr, "lcdInit failed\n") ;
    exit (EXIT_FAILURE) ;
  }
*/

}









/* mathlink function calls */

int mllcdputs(char *buf);
int mllcdclear();
int mllcdcolor(int color);
int mllcdposition(int col, int row);
int mllcdscroll(int row, char *buf);

/* mathlink main routine */
int main(int argc, char *argv[])
{



    wiringPiSetupSys () ;
    mcp23017Setup (AF_BASE, 0x20) ;
    adafruitLCDSetup (1) ;

    return MLMain(argc, argv);
}

/* mathlink function definitions */
int mllcdputs(char *buf)
{
    lcdPuts(lcdHandle, buf);
    return 0;
}

int mllcdclear()
{
    lcdClear(lcdHandle);
    return 0;
}
int mllcdcolor(int color)
{
    setBacklightColor(color);
    return 0;
}
int mllcdposition(int col, int row)
{
    lcdPosition (lcdHandle, col, row);
}
int mllcdscroll(int row, char *buf)
{
    lcdClear(lcdHandle);
    for (;;)
    {
        scrollMessage(row,16, buf);
	if (digitalRead (AF_SELECT) == LOW)
        {
            lcdClear(lcdHandle);
            return 0;
        }

    }
}

