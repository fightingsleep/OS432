/**
 * This file contains implementations of miscellanous system calls.
 * 
 * Author: Omar Zarifi
 * Date: March 26, 2014
 */

#include "timer.h"
#include "print.h"

int xScreenCoord = 0;
int yScreenCoord = 0;

/**
 * Not actually used.
 */
unsigned long long internal_dummy_syscall(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	
}

/**
 * All arguments are unused.
 */
unsigned long long internal_gettime(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	return GetTimeStamp();
}

unsigned long long internal_drawstring(unsigned int a0, unsigned int a1,
        unsigned int a2, unsigned int a3, unsigned int a4)
{
	DrawString((char *)a0, a1, xScreenCoord, yScreenCoord);
	xScreenCoord += a1 * 8;
	if(xScreenCoord >= 1024)
	{
		xScreenCoord = 0;
		yScreenCoord += 16;
		if(yScreenCoord >= 768)
		{
			clearScreen();
			xScreenCoord = 0;
			yScreenCoord = 0;
		}
	}
	return 0;
}

unsigned long long internal_drawstringln(unsigned int a0, unsigned int a1,
        unsigned int a2, unsigned int a3, unsigned int a4)
{
	if(xScreenCoord > 0)
	{
		xScreenCoord = 0;
		yScreenCoord += 16;
		if(yScreenCoord >= 768)
		{
			clearScreen();
			yScreenCoord = 0;
		}
	}
	DrawString((char *)a0, a1, xScreenCoord, yScreenCoord);
	xScreenCoord = 0;
	yScreenCoord += 16;
	if(yScreenCoord >= 768)
	{
		clearScreen();
		yScreenCoord = 0;
	}
        return 0;
}

