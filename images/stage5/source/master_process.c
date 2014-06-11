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
	char command[26];
	unsigned int *lengthread;
	char welcomemsg[] = "Welcome to OS432! The commands are listed below:";
	char option1[] = "1) Process test";
	char option2[] = "2) IPC test";
	char promptmsg[] = "Please enter a command: ";
	osc_drawstringln(welcomemsg, 48);
	osc_drawstringln(option1, 15);
	osc_drawstringln(option2, 11);
	osc_drawstringln(promptmsg, 24);
	osc_getstring(command, 25, lengthread);
	osc_drawstringln(" ", 1);

	if(strcmp(command, "1") == 0)
	{
		osc_create_process(printA);
        	osc_create_process(printB);
	}
	if(strcmp(command, "2") == 0)
	{
		osc_create_process(pidTalk);
	}
	while(1)
	{
	}
}
