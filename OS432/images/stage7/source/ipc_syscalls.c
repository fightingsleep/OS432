/**
 * This file contains implementations of system calls related to inter-process
 * communication.
 * 
 * Author: Omar Zarifi
 * Date: March 26, 2014
 */

#include "ipc_facility.h"
#include "memcpy.h"
#include "process.h"

#define NULL ((void*) 0)

/**
 * a0 is the pid of the process to send to. a1 is the pointer to the data to
 * send. a2 is the size of the message. a3 is the synchronous flag (if a3 is 1,
 * then the sender blocks until a reply is received; otherwise, sender does not
 * block). Remaining arguments are unused.
 */
unsigned long long internal_send(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process* partner = get_by_pid(a0);
	struct ipc_node* new_node =
		(struct ipc_node*) kmalloc(sizeof(struct ipc_node));
	
	if(new_node == NULL)
	{
		return IPC_MEMORY_ERROR;
	}
	if(a0 == 1 || partner == NULL)
	{
		kfree(new_node);
		return IPC_INVALID_PID;
	}
	
	new_node->data = NULL;
	if(a2 > 0)
	{
		new_node->data = kmalloc(a2);
		if(new_node->data == NULL)
		{
			kfree(new_node);
			return IPC_MEMORY_ERROR;
		}
		memcpy(new_node->data, (void*) a1, a2);
	}
	new_node->size = a2;
	new_node->sender = current->pid;
	new_node->next = NULL;
	
	if(partner->message_queue.tail == NULL)
	{
		partner->message_queue.head = new_node;
	}
	else
	{
		partner->message_queue.tail->next = new_node;
	}
	partner->message_queue.tail = new_node;
	
	if(partner->state == BLOCKED_RECEIVE)
	{
		partner->state = ACTIVE;
	}
	
	if(a3 == 1)
	{
		current->reply.sender = a0;
		current->state = BLOCKED_REPLY;
		/* Put 0 into r0. */
		*((unsigned int*) (((unsigned int) current->stack_pointer) + 52))
			= 0;
		schedule();
	}
	
	return 0;
}

/**
 * a0 is the pointer to memory allocated for the reply. a1 is a pointer to an
 * integer that holds the maximum size of the reply. Remaining arguments are
 * unused.
 */
unsigned long long internal_get_reply(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	unsigned int* size = (unsigned int*) a1;
	
	if(current->reply.size < *size)
	{
		*size = current->reply.size;
	}
	
	memcpy((void*) a0, current->reply.data, *size);
	kfree(current->reply.data);
	return 0;
}

/**
 * All arguments are unused.
 */
unsigned long long internal_wait_for_send(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	if(current->message_queue.head == NULL)
	{
		current->state = BLOCKED_RECEIVE;
		schedule();
	}
	
	return 0;
}

/**
 * a0 is a pointer to an unsigned integer that is to hold the pid of the
 * sender. a1 is a pointer to memory allocated for the message. a2 is a pointer
 * to an integer that holds the maximum size of the reply. Remaining arguments
 * are unused.
 */
unsigned long long internal_receive(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	unsigned int* pid = (unsigned int*) a0;
	unsigned int* size = (unsigned int*) a2;
	struct ipc_node* node = current->message_queue.head;
	current->message_queue.head = node->next;
	if(current->message_queue.tail == node)
	{
		current->message_queue.tail = node->next;
	}
	
	*pid = node->sender;
	if(node->size < *size)
	{
		*size = node->size;
	}
	
	memcpy((void*) a1, node->data, *size);
	kfree(node->data);
	kfree(node);
	return 0;
}

/**
 * a0 is the pid of the process to reply to. a1 is a pointer to the reply. a2
 * is the size of the reply.
 */
unsigned long long internal_reply(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	struct process* partner = get_by_pid(a0);
	
	if(partner == NULL)
	{
		return IPC_INVALID_PID;
	}
	if(partner->state != BLOCKED_REPLY
		|| partner->reply.sender != current->pid)
	{
		return IPC_INVALID_REPLY;
	}
	
	partner->reply.data = kmalloc(a2);
	if(partner->reply.data == NULL)
	{
		return IPC_MEMORY_ERROR;
	}
	memcpy(partner->reply.data, (void*) a1, a2);
	partner->reply.size = a2;
	
	return 0;
}
