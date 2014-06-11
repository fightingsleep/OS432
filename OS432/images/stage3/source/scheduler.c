/**
 * This file contains the scheduling and context switching facility.
 * 
 * Author: Omar Zarifi
 * Date: March 14, 2014
 */

#include "cpu_context.h"
#include "interrupts.h"
#include "process.h"
#include "scheduler.h"
#include "timer.h"

#define NULL ((void*) 0)

void schedule()
{
	disableTimer();

	/*	
	 Wake up any sleeping processes that should be done sleeping. 
	unsigned long long current_time = GetTimeStamp();
	struct process_node* prev = NULL;
	struct process_node* node = sleeping.head;
	while(node != NULL)
	{
		if(node->proc->wakeup_time <= current_time)
		{
			struct process_node* temp;
			node->proc->state = ACTIVE;
			
			 Remove the node from the sleeping list. 
			if(prev == NULL)
			{
				sleeping.head = node->next;
			}
			else
			{
				prev->next = node->next;
			}
			if(node->next == NULL)
			{
				sleeping.tail = prev;
			}
			
			temp = node;
			node = node->next;
			kfree(temp);
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
	*/
	
	/* Choose the next process. */
	struct process_node* node = processes.head;
	while(node != NULL)
	{
		if(node->next != NULL)
		{
			processes.head = node->next;
			processes.tail->next = node;
			processes.tail = node;
			node->next = NULL;
		}
		
		if(node->proc->state == ACTIVE)
		{
			current = node->proc;
			node = NULL;
		}
	}
	
	/* Set up the timer once again. */
	ackTimerInterrupt();
	loadTimerValue(TIMER_VALUE);
	enableTimer();
	
	restore_context();
}
