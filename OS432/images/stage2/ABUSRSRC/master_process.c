/**
 * Function executed by the first process.
 */

#include "tostring.h"
#include "user_syscalls.h"
#include "user_programs.h"
#include "string.h"

#define NULL ((void*) 0)

void master_process()
{
	char welcomemsg[] = "Welcome to OS432: Launching Process Test";
	osc_drawstring((void *)welcomemsg, 40, 0, 0);
	osc_create_process(printA);
        osc_create_process(printB);
	while(1)
	{
	}
}
