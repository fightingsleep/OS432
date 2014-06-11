/**
 * This file contains the process-related routines.
 * 
 * Author: Omar Zarifi
 * Date: March 11, 2014
 */

#include "memory.h"
#include "process.h"
#include "scheduler.h"
#include "tostring.h"
#include "print.h"

#define NULL ((void*) 0)

/* Note: memory must be initialized before processes.
 * Processes must be initialized last. This function does not return. */
void processes_init()
{
	struct process_node* node;
	
	/* Create the master process. */
	struct process* master = (struct process*) kmalloc(sizeof(struct process));
	master->pid = 1;
	master->ppid = 0;
	master->program_counter = (void*) (KERNEL_STACK_START + 0x8);
	master->process_heap.address = kmalloc(USER_HEAP_SIZE + USER_STACK_SIZE);
	master->process_space_base = master->process_heap.address;
	master->process_heap.size = USER_HEAP_SIZE;
	master->stack_pointer = (void*) (((char*) master->process_heap.address)
		+ USER_HEAP_SIZE + USER_STACK_SIZE - 15 * 4);
	*((unsigned int*) master->stack_pointer) = USER_CPSR;
	master->process_heap.next = NULL;
	master->state = ACTIVE;
	master->children.head = NULL;
	master->children.tail = NULL;
	master->message_queue.head = NULL;
	master->message_queue.tail = NULL;
	/* Note that the reply field does not need initialization. */

/*	
	 Create the console process. 
	struct process* console = (struct process*) kmalloc(sizeof(struct process));
	console->pid = 2;
	console->ppid = 0;
	console->program_counter = (void*) (KERNEL_STACK_START + 0x64);
	console->process_heap.address = kmalloc(USER_HEAP_SIZE + USER_STACK_SIZE);
	console->process_space_base = console->process_heap.address;
	console->process_heap.size = USER_HEAP_SIZE;
	console->stack_pointer = (void*) (((char*) console->process_heap.address)
		+ USER_HEAP_SIZE + USER_STACK_SIZE - 15 * 4);
	*((unsigned int*) console->stack_pointer) = USER_CPSR | 0xF;
	console->process_heap.next = NULL;
	console->state = ACTIVE;
	console->children.head = NULL;
	console->children.tail = NULL;
	console->message_queue.head = NULL;
	console->message_queue.tail = NULL;
	 Note that the reply field does not need initialization. 
*/

	/* Initialize the system structures that keep track of processes. */
	node = (struct process_node*) kmalloc(sizeof(struct process_node));
	node->proc = master;
	processes.head = node;
	processes.tail = node;
	node->next = NULL;
	
	/*
	node = (struct process_node*) kmalloc(sizeof(struct process_node));
	node->proc = console;
	node->next = NULL;
	processes.head->next = node;
	processes.tail = node;
	sleeping.head = NULL;
	sleeping.tail = NULL;
	*/

	/* The master process will now take control. */
	schedule();
}

struct process* get_by_pid(unsigned int pid)
{
	struct process_node* node = processes.head;
	while(node != NULL && node->proc->pid != pid)
	{
		node = node->next;
	}
	if(node == NULL)
	{
		return NULL;
	}
	else
	{
		return node->proc;
	}
}
