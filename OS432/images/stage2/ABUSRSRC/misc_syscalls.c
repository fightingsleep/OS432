/**
 * This file contains implementations of miscellanous system calls.
 * 
 * Author: Omar Zarifi
 * Date: March 26, 2014
 */

#include "timer.h"
#include "print.h"
#include "tostring.h"

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
	DrawString(a0, a1, a2, a3);
	return 0;
}

