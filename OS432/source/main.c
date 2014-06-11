/* 
 * Main C method, jumped to from init.s
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
*/

#include "int_handlers.h"
#include "io_config.h"
#include "memory.h"
#include "process.h"
#include "syscalls.h"

void initialize()
{
	input_init();
	output_init();
	memory_init();
	idt_init();
	syscalls_init();
	timer_interrupt_init();
	processes_init();
}
