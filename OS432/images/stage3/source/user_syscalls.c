/**
 * This file contains system calls.
 * 
 * Author: Omar Zarifi
 * Date: March 26, 2014
 */

#include "console_proc.h"
#include "memcpy.h"
#include "syscalls.h"
#include "user_syscalls.h"

void* osc_malloc(unsigned int size)
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_MALLOC), "r" (size)
	);
	
	return (void*) ret;
}

void osc_free(void* address)
{
	asm volatile
	(
		"mov r0, %0 \n\t"
		"mov r1, %1 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_FREE), "r" (address)
	);
}

unsigned int osc_send(unsigned int pid, void* msg, unsigned int size,
	void* reply, unsigned int* r_size)
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"mov r2, %3 \n\t"
		"mov r3, %4 \n\t"
		"mov r4, %5 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_SEND), "r" (pid), "r" (msg), "r" (size), "I" (1)
	);
	
	if(ret != 0)
	{
		return ret;
	}
	
	asm volatile
	(
		"mov r0, %0 \n\t"
		"mov r1, %1 \n\t"
		"mov r2, %2 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_GET_REPLY), "r" (reply), "r" (r_size)
	);
	
	return 0;
}

unsigned int osc_async_send(unsigned int pid, void* msg, unsigned int size)
{
	unsigned int ret;

	asm volatile
	(
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"mov r2, %3 \n\t"
		"mov r3, %4 \n\t"
		"mov r4, %5 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_SEND), "r" (pid), "r" (msg), "r" (size), "I" (0)
	);
	
	return ret;
}

unsigned int osc_receive(unsigned int* pid, void* msg, unsigned int* size)
{
	asm volatile
	(
		"mov r0, %0 \n\t"
		"svc #0 \n\t"
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"mov r2, %3 \n\t"
		"mov r3, %4 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_WAIT_FOR_SEND), "I" (SYSCALL_RECEIVE), "r" (pid),
			"r" (msg), "r" (size)
	);
	
	return 0;
}

unsigned int osc_reply(unsigned int pid, void* msg, unsigned int size)
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"mov r2, %3 \n\t"
		"mov r3, %4 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_REPLY), "r" (pid), "r" (msg), "r" (size)
	);
	
	return ret;
}

unsigned int osc_getpid()
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_GETPID)
	);
	
	return ret;
}

unsigned int osc_getppid()
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_GETPPID)
	);
	
	return ret;
}

unsigned int osc_create_process(unsigned int (*function)(void))
{
	unsigned int ret;
	
	asm volatile
	(
		"mov r0, %1 \n\t"
		"mov r1, %2 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		: "=r" (ret)
		: "I" (SYSCALL_CREATE_PROCESS), "r" (function)
	);
	
	return ret;
}

unsigned int osc_waitpid(unsigned int pid)
{
	unsigned int ret;
	unsigned int looping = 1;
	
	while(looping == 1)
	{
		asm volatile
		(
			"mov r0, %2 \n\t"
			"mov r1, %3 \n\t"
			"svc #0 \n\t"
			"mov %0, r0 \n\t"
			"mov %1, r1 \n\t"
			: "=r" (ret), "=r" (looping)
			: "I" (SYSCALL_WAITPID), "r" (pid)
		);
	}
	
	return ret;
}

void osc_exit(unsigned int ret)
{
	asm volatile
	(
		"mov r0, %0 \n\t"
		"mov r1, %1 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_EXIT), "r" (ret)
	);
}

void osc_sleep(unsigned int duration)
{
	asm volatile
	(
		"mov r0, %0 \n\t"
		"mov r1, %1 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_SLEEP), "r" (duration)
	);
}

void osc_yield()
{
	asm volatile
	(
		"mov r0, %0 \n\t"
		"svc #0 \n\t"
		:
		: "I" (SYSCALL_YIELD)
	);
}

void osc_print_string(char* string, unsigned int size)
{
	struct io_request request;
	
	request.type = OUTPUT;
	memcpy(request.string, string, size);
	request.size = size;
	
	osc_async_send(CONSOLE_PID, &request, sizeof(struct io_request));
}

void osc_print_line(char* string, unsigned int size)
{
	struct io_request request;
	
	request.type = OUTPUT_LN;
	memcpy(request.string, string, size);
	request.size = size;
	
	osc_async_send(CONSOLE_PID, &request, sizeof(struct io_request));
}

void osc_get_string(char* string, unsigned int* size)
{
	struct io_request request;

	request.type = INPUT;
	request.size = *size;
	
	osc_send(CONSOLE_PID, &request, sizeof(struct io_request), &request,
		size);
	memcpy(string, request.string, request.size);
	*size = request.size;
}

void osc_drawstring(void *string, unsigned int length)
{
	asm volatile
	(
		"mov r0, %0\n\t"
		"mov r1, %1\n\t"
		"mov r2, %2\n\t"
		"svc #0\n\t"
	 :
	 : "I" (SYSCALL_DRAWSTRING), "r" (string), "r" (length)
	 : "r0", "r1", "r2"
	);
}

unsigned long long osc_gettime()
{
	unsigned int top;
	unsigned int bottom;
	unsigned long long time;
	
	asm volatile
	(
		"mov r0, %2 \n\t"
		"svc #0 \n\t"
		"mov %0, r0 \n\t"
		"mov %1, r1 \n\t"
		: "=r" (bottom), "=r" (top)
		: "I" (SYSCALL_GETTIME)
	);
	
	time = top * 0x100000000ull + bottom;
	return time;
}
