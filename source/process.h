/*
 * This file contains the description of a process, as well as the system
 * process management routines and structures.
 * 
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew 
 */

#ifndef _PROCESS_H_
#define _PROCESS_H_

/* Default heap and stack sizes for a user process. */
#define USER_HEAP_SIZE 65536
#define USER_STACK_SIZE 65536

/* Processor operation mode bits for user processes. */
#define USER_CPSR 0x00000150

#include "ipc_facility.h"
#include "memory.h"

/* Process state. */
enum process_state
{
	ACTIVE,
	BLOCKED,
	BLOCKED_RECEIVE,
	BLOCKED_REPLY,
	BLOCKED_WAITPID,
	DEAD
};

struct process;

/* A node for a list of processes. */
struct process_node
{
	struct process* proc;
	struct process_node* next;
};

/* A list of processes. */
struct process_list
{
	struct process_node* head;
	struct process_node* tail;
};

/* A process descriptor. */
struct process
{
	/* PID. */
	unsigned int pid;
	/* PID of the parent. */
	unsigned int ppid;
	/* Pointer to the top of the process stack. */
	void* stack_pointer;
	/* Pointer to the next instruction to execute. */
	void* program_counter;
	/* Process heap. */
	heap process_heap;
	/* Base address of the memory set aside for the process. */
	void* process_space_base;
	/* State of the process. */
	enum process_state state;
	/* List of children of this process. */
	struct process_list children;
	/* Queue of sent messages. */
	struct ipc_msg_list message_queue;
	/* Structure for the reply. */
	struct ipc_node reply;
	/* When to awake this process (is applicable when the process sleeps). */
	unsigned long long wakeup_time;
	/* Return value of the process. */
	unsigned int return_value;
};

/* The active process. */
struct process* current;

/* List of processes in the system. */
struct process_list processes;

/* List of processes that requested to sleep for a specified amount of time. */
struct process_list sleeping;

/**
 * Initialize the process sytem.
 */
void processes_init();

/**
 * Return a pointer to a process structure given its pid.
 */
struct process* get_by_pid(unsigned int pid);

#endif
