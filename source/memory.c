/*
 * This file contains the kernel memory management facility.
 *  
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew    
 *
 */

#include "memory.h"
#include "process.h"

#define NULL ((void*) 0)

void* kmalloc(unsigned int size)
{
	return memory_allocator(&kernel_heap, size);
}

/* Uses the first fit algorithm. */
void* memory_allocator(heap* h, unsigned int size)
{
	unsigned int padding = 4 - (size % 4);
	unsigned int size2 = size + sizeof(unsigned int) + padding;
	struct heap_node* prev = NULL;
	struct heap_node* node = h;
	void* address = NULL;
	
	if(padding == 4)
	{
		size2 = size2 - 4;
	}
	
	while(address == NULL && node != NULL)
	{
		if(node->size >= size2)
		{
			address = node->address;
			*((unsigned int*) address) = size2;
			node->address = (void*) (((char*) node->address) + size2);
			node->size = node->size - size2;
			
			if(node->size == 0)
			{
				if(prev == NULL)
				{
					if(node->next != NULL)
					{
						struct heap_node* temp = node->next;
						
						h->address = temp->address;
						h->size = temp->size;
						h->next = temp->next;
						
						kfree(temp);
					}
				}
				else
				{
					prev->next = node->next;
					kfree(node);
				}
			}
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
	
	if(address != NULL)
	{
		address = (void*) (((char*) address) + sizeof(unsigned int));
	}
	return address;
}

void kfree(void* address)
{
	memory_deallocator(&kernel_heap, address);
}

void memory_deallocator(heap* h, void* address)
{
	unsigned int size = *((unsigned int*) address);
	struct heap_node* prev = NULL;
	struct heap_node* node = h;
	
	if(h->size == 0)
	{
		h->address = address;
		h->size = size;
		return;
	}
	
	while(node != NULL && node->address < address)
	{
		prev = node;
		node = node->next;
	}
	
	if(prev != NULL)
	{
		if(((char*) prev->address) + prev->size == address)
		{
			prev->size = prev->size + size;
			
			if(node != NULL
				&& ((char*) prev->address) + prev->size == node->address)
			{
				prev->size = prev->size + node->size;
				prev->next = node->next;
				
				kfree(node);
			}
		}
		else
		{
			if(node != NULL && ((char*) address) + size == node->address)
			{
				node->address = ((char*) node->address) - size;
				node->size = node->size + size;
			}
			else
			{
				struct heap_node* new = (struct heap_node*)
					kmalloc(sizeof(struct heap_node));
				if(new != NULL)
				{
					new->address = address;
					new->size = size;
					new->next = node;
					prev->next = new;
				}
			}
		}
	}
	else
	{
		if(((char*) address) + size == node->address)
		{
			node->address = ((char*) node->address) - size;
			node->size = node->size + size;
		}
		else
		{
			struct heap_node* new = (struct heap_node*)
				kmalloc(sizeof(struct heap_node));
			if(new != NULL)
			{
				new->address = node->address;
				new->size = node->size;
				new->next = node->next;
				node->address = address;
				node->size = size;
				node->next = new;
			}
		}
	}
}

void memory_init()
{
	kernel_heap.address = (void*) KERNEL_HEAP_START;
	kernel_heap.size = KERNEL_HEAP_SIZE;
	kernel_heap.next = NULL;
}
