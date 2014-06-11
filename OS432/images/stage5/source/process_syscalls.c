/**
 * This file contains implementations of system calls related to processes.
 * 
 * Author: Omar Zarifi
 * Date: March 25, 2014
 */

#include "process.h"
#include "timer.h"
#include "user_syscalls.h"

#define NULL ((void*) 0)

unsigned int next_free = 2;

/**
 * All arguments are unused.
 */
unsigned long long internal_getpid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	return (unsigned long long) current->pid;
}

/**
 * All arguments are unused.
 */
unsigned long long internal_getppid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	return (unsigned long long) current->ppid;
}

/**
 * Return a new usable pid.
 */
unsigned int get_free_pid()
{
	next_free = next_free + 1;
	return next_free - 1;
}

/**
 * a0 is a function pointer (of the form unsigned int func(void)). Remaining
 * arguments are unused.
 */
unsigned long long internal_create_process(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process_node* nodeC;
	struct process_node* nodeS;
	struct process* n = (struct process*) kmalloc(sizeof(struct process));
	if(n == NULL)
	{
		return 0;
	}
	
	n->pid = get_free_pid();
	n->ppid = current->pid;
	/* This forces the new process to jump to new_process(). */
	n->program_counter = (void*) (KERNEL_STACK_START + 0x68);
	n->process_heap.address = kmalloc(USER_HEAP_SIZE + USER_STACK_SIZE);
	if(n->process_heap.address == NULL)
	{
		kfree(n);
		return 0;
	}
	n->process_space_base = n->process_heap.address;
	n->process_heap.size = USER_HEAP_SIZE;
	n->stack_pointer = (void*) (((char*) n->process_heap.address)
		+ USER_HEAP_SIZE + USER_STACK_SIZE - 15 * 4);
	*((unsigned int*) n->stack_pointer) = USER_CPSR;
	/* This puts the function pointer into saved r6. */
	*((unsigned int*)(((unsigned int) n->stack_pointer) + 28)) = a0;
	n->process_heap.next = NULL;
	n->state = ACTIVE;
	n->children.head = NULL;
	n->children.tail = NULL;
	n->message_queue.head = NULL;
	n->message_queue.tail = NULL;
	/* Note that the reply field does not need initialization. */
	
	/* Add the new process to the list of children of the caller and to the
	 * system list of processes. */
	nodeC = (struct process_node*) kmalloc(sizeof(struct process_node));
	if(nodeC == NULL)
	{
		kfree(n->process_heap.address);
		kfree(n);
		return 0;
	}
	nodeC->proc = n;
	nodeC->next = NULL;
	if(current->children.tail == NULL)
	{
		current->children.head = nodeC;
		current->children.tail = nodeC;
	}
	else
	{
		current->children.tail->next = nodeC;
		current->children.tail = nodeC;
	}
	
	/* Add the new process to the system list of processes. */
	nodeS = (struct process_node*) kmalloc(sizeof(struct process_node));
	if(nodeS == NULL)
	{
		kfree(n->process_heap.address);
		kfree(n);
		kfree(nodeC);
		return 0;
	}
	nodeS->proc = n;
	nodeS->next = NULL;
	processes.tail->next = nodeS;
	processes.tail = nodeS;
	
	return (unsigned long long) n->pid;
}

/**
 * A new process created through create_process() enters this function.
 * Note that the function pointer to the desired routine must be saved in r6.
 */
void new_process()
{
	unsigned int f_pointer;
	unsigned int (*function)(void);
	unsigned int ret;
	
	asm volatile
	(
		"mov %0, r6 \n\t"
		: "=r" (f_pointer)
	);
	
	function = (int (*)(void)) f_pointer;
	ret = function();
	osc_exit(ret);
}

/**
 * a0 is the pid of the child. Remaining arguments are unused.
 */
unsigned long long internal_waitpid(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process_node* prev = NULL;
	struct process_node* node = current->children.head;
	
	while(node != NULL && node->proc->pid != a0)
	{
		prev = node;
		node = node->next;
	}
	
	if(node == NULL)
	{
		return 0x0BADCA11;
	}
	
	if(node->proc->state != DEAD)
	{
		current->state = BLOCKED_WAITPID;
		/* Put 1 into r1. */
		*((unsigned int*) (((unsigned int) current->stack_pointer) + 48))
			= 1;
		schedule();
		
		return 0;
	}
	else
	{
		int ret = node->proc->return_value;
		kfree(node->proc);
		if(prev == NULL)
		{
			current->children.head = node->next;
		}
		else
		{
			prev->next = node->next;
		}
		if(node->next == NULL)
		{
			current->children.tail = prev;
		}
		kfree(node);
		
		return (unsigned long long) ret;
	}
}

/**
 * a0 is the exit code. Remaining arguments are unused.
 */
unsigned long long internal_exit(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process_node* prev = NULL;
	struct process_node* mine = processes.head;
	struct process* parent = get_by_pid(current->ppid);
	
	/* Clean up memory used by the process. */
	struct heap_node* heap_node = current->process_heap.next;
	while(heap_node != NULL)
	{
		struct heap_node* temp = heap_node;
		heap_node = heap_node->next;
		kfree(temp);
	}
	kfree(current->process_space_base);
	
	/* Find and remove the process node from the system list. */
	while(mine->proc != current)
	{
		prev = mine;
		mine = mine->next;
	}
	prev->next = mine->next;
	processes.tail = prev;
	kfree(mine);
	
	/* Get the parent to adopt your children. */
	prev = current->children.head;
	while(prev != NULL)
	{
		parent->children.tail->next = prev;
		parent->children.tail = prev;
		prev = prev->next;
	}
	
	current->state = DEAD;
	current->return_value = a0;
	
	/* If the parent is waiting for some child to finish, wake it up. */
	if(parent->state == BLOCKED_WAITPID)
	{
		parent->state = ACTIVE;
	}
	
	schedule();
	
	return 0;
}

/**
 * a0 is the amount of time to sleep (in milliseconds). Remaining arguments are
 * unused.
 */
unsigned long long internal_sleep(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process_node* node = (struct process_node*)
		kmalloc(sizeof(struct process_node));
	unsigned long long time = GetTimeStamp();
	
	if(node == NULL)
	{
		schedule();
	}
	node->proc = current;
	node->next = NULL;
	
	current->wakeup_time = time + a0;
	current->state = BLOCKED;
	
	if(sleeping.tail == NULL)
	{
		sleeping.head = node;
	}
	else
	{
		sleeping.tail->next = node;
	}
	sleeping.tail = node;
	
	schedule();
	
	return 0;
}

/**
 * All arguments are unused.
 */
unsigned long long internal_yield(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	schedule();
	
	return 0;
}
