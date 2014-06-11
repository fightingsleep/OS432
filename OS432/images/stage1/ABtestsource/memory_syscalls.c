/**
 * Implementation of user memory management calls.
 * 
 * Author: Omar Zarifi
 * Date: March 25, 2014
 */

#include "memory.h"
#include "process.h"

/**
 * a0 is the size. Remaining arguments are unused.
 */
unsigned long long internal_malloc(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	return (unsigned long long)
		((unsigned int) memory_allocator(&current->process_heap, a0));
}

/**
 * a0 is the pointer to the chunk that needs freeing. Remaining arguments are
 * unused.
 */
unsigned long long internal_free(unsigned int a0, unsigned int a1,
	unsigned int a2, unsigned int a3, unsigned int a4)
{
	memory_deallocator(&current->process_heap, (void*) a0);
	return 0;
}
