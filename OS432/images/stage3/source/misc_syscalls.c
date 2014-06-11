/**
 * This file contains implementations of miscellanous system calls.
 * 
 * Author: Omar Zarifi
 * Date: March 26, 2014
 */

#include "timer.h"
#include "print.h"
#include "tostring.h"
#include "io_config.h"

int x = 0;
int y = 0;

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
	DrawString(a0, a1, x, y);
	x += 8;
	if(x >= 1024)
	{
		x = 0;
		y += 16;
		if(y >= 768)
		{
			clearScreen();
			x = 0;
			y = 0;
		}
	}
	return 0;
}

