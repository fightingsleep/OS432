/* Main C method, jumped to from init.s */

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
