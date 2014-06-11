/**
 * Function executed by the first process.
 */

#include "tostring.h"
#include "user_syscalls.h"
#include "user_programs.h"
#include "string.h"
#include "leds.h"
#include "print.h"

#define NULL ((void*) 0)

void master_process()
{
	char welcomemsg[] = "Welcome to OS432: Launching Process Test";
	DrawString(welcomemsg, 40, 0, 0);
	internal_create_process(printA, 0, 0, 0, 0);
        internal_create_process(printB, 0, 0, 0, 0);
	while(1)
	{
	}
}
