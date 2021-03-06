/**
 * This file contains initialization for the array of syscall functions.
 * 
 * Author: Omar Zarifi
 * Date: March 28, 2014
 */

#include "syscalls.h"

/**
 * Initialize the array of internal system call functions.
 */
void syscalls_init()
{
	syscall_functions[0] = internal_dummy_syscall;
	syscall_functions[1] = internal_malloc;
	syscall_functions[2] = internal_free;
	syscall_functions[3] = internal_send;
	syscall_functions[4] = internal_get_reply;
	syscall_functions[5] = internal_wait_for_send;
	syscall_functions[6] = internal_receive;
	syscall_functions[7] = internal_reply;
	syscall_functions[8] = internal_getpid;
	syscall_functions[9] = internal_getppid;
	syscall_functions[10] = internal_create_process;
	syscall_functions[11] = internal_waitpid;
	syscall_functions[12] = internal_exit;
	syscall_functions[13] = internal_sleep;
	syscall_functions[14] = internal_yield;
	syscall_functions[15] = internal_gettime;
}
