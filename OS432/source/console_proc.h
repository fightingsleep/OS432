/**
 * The function executed by the console process.
 * The console processes has queues of operations that it needs to perform.
 * Operations are either input (keyboard) or output (monitor).
 * 
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
 */

/*
 * WARNING: THIS PROCESSES IS NOT CURRENTLY BEING RUN OR USED FOR INPUT OR
 * OUTPUT. THE FUNCTIONS CURRENTLY BEING USED ARE IN misc_syscalls.c. IDEALLY
 * THIS PROCESS WOULD BE A BETTER WAY OF DOING IO.   
*/


#ifndef _CONSOLE_PROC_H_
#define _CONSOLE_PROC_H_

#include "io_config.h"

#define CONSOLE_PID 2

/* Request type; either input or output. */
enum io_request_type
{
	INPUT,
	OUTPUT,
	OUTPUT_LN
};

/* A structure to encode a request for service from the console. */
struct io_request
{
	enum io_request_type type;
	char string[MAX_IO_STRING_SIZE];
	unsigned int size;
};

void console_proc();

#endif
