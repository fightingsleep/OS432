/**
 * This file contains internal syscall definitions.
 * 
 * Author: Omar Zarifi
 * Date: March 25, 2014
 */

#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#define NUM_SYSCALLS 16

#define SYSCALL_DUMMY 0
#define SYSCALL_MALLOC 1
#define SYSCALL_FREE 2
#define SYSCALL_SEND 3
#define SYSCALL_GET_REPLY 4
#define SYSCALL_WAIT_FOR_SEND 5
#define SYSCALL_RECEIVE 6
#define SYSCALL_REPLY 7
#define SYSCALL_GETPID 8
#define SYSCALL_GETPPID 9
#define SYSCALL_CREATE_PROCESS 10
#define SYSCALL_WAITPID 11
#define SYSCALL_EXIT 12
#define SYSCALL_SLEEP 13
#define SYSCALL_YIELD 14
#define SYSCALL_GETTIME 15

unsigned long long internal_dummy_syscall(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_malloc(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_free(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_send(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_get_reply(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_wait_for_send(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_receive(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_reply(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_getpid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_getppid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_create_process(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_waitpid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_exit(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_sleep(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_yield(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);
unsigned long long internal_gettime(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4);

unsigned long long (*syscall_functions[NUM_SYSCALLS])(unsigned int,
	unsigned int, unsigned int, unsigned int, unsigned int);

/**
 * Initialize the array of internal system call functions.
 */
void syscalls_init();

#endif
