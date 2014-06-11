/**
 * This file contains the context saving and restoring functionality.
 * 
 * Author: Omar Zarifi
 * Date: March 17, 2014
 */

#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include "memory.h"
#include "process.h"

/**
 * Routine to save the context to the process structure of the current process.
 * The routine is defined as a macro because we don't want to modify stacks
 * with function calls.
 * At the end of this call, the top of the stack of the current process will
 * contain lr, r0-r12, SPSR (in reverse order). Moreover, its updated stack
 * pointer and return address will be saved on the process structure.
 * Note: IRQ/FIQ handler must substract 4 from the saved program counter after
 * calling this routine.
 */
#define save_context() \
	asm volatile \
	( \
		"mov sp, %[c] \n\t" \
		"push {r12} \n\t" \
		"push {r11} \n\t" \
		"push {r10} \n\t" \
		"mov r10, #0x1F \n\t" \
		"mrs r11, cpsr \n\t" \
		"mov r12, r11 \n\t" \
		"orr r11, r11, r10 \n\t" \
		"msr cpsr, r11 \n\t" \
		"push {lr} \n\t" \
		"push {r0} \n\t" \
		"push {r1} \n\t" \
		"push {r2} \n\t" \
		"push {r3} \n\t" \
		"push {r4} \n\t" \
		"push {r5} \n\t" \
		"push {r6} \n\t" \
		"push {r7} \n\t" \
		"push {r8} \n\t" \
		"push {r9} \n\t" \
		"mov r0, sp \n\t" \
		"msr cpsr, r12 \n\t" \
		"pop {r1} \n\t" \
		"pop {r2} \n\t" \
		"pop {r3} \n\t" \
		"mrs r4, spsr \n\t" \
		"mov r5, sp \n\t" \
		"mov sp, r0 \n\t" \
		"push {r1} \n\t" \
		"push {r2} \n\t" \
		"push {r3} \n\t" \
		"push {r4} \n\t" \
		"mov r0, sp \n\t" \
		"mov r1, lr \n\t" \
		"mov sp, r5 \n\t" \
		"mov %[a], r0 \n\t" \
		"mov %[b], r1 \n\t" \
		: [a] "=r" (current->stack_pointer), \
			[b] "=r" (current->program_counter) \
		: [c] "I" (KERNEL_STACK_START) \
	);

/**
 * Routine to restore the context of the current process.
 * The routine is defined as a macro because we don't want to modify stacks
 * with function calls.
 */
#define restore_context() \
	asm volatile \
	( \
		"mov lr, %0 \n\t" \
		"mov r0, sp \n\t" \
		"mov r10, #0x1F \n\t" \
		"mrs r11, cpsr \n\t" \
		"mov r12, r11 \n\t" \
		"orr r11, r11, r10 \n\t" \
		"msr cpsr, r11 \n\t" \
		"mov sp, %1 \n\t" \
		"pop {r5} \n\t" \
		"pop {r6} \n\t" \
		"pop {r7} \n\t" \
		"pop {r8} \n\t" \
		"pop {r9} \n\t" \
		"mov r1, sp \n\t" \
		"mov sp, r0 \n\t" \
		"push {r9} \n\t" \
		"push {r8} \n\t" \
		"push {r7} \n\t" \
		"push {r6} \n\t" \
		"push {r5} \n\t" \
		"mov r9, sp \n\t" \
		"mov sp, r1 \n\t" \
		"pop {r8} \n\t" \
		"pop {r7} \n\t" \
		"pop {r6} \n\t" \
		"pop {r5} \n\t" \
		"pop {r4} \n\t" \
		"pop {r3} \n\t" \
		"pop {r2} \n\t" \
		"pop {r1} \n\t" \
		"pop {r0} \n\t" \
		"pop {lr} \n\t" \
		"msr cpsr, r12 \n\t" \
		"mov sp, r9 \n\t" \
		"pop {r9} \n\t" \
		"msr spsr, r9 \n\t" \
		"pop {r12} \n\t" \
		"pop {r11} \n\t" \
		"pop {r10} \n\t" \
		"pop {r9} \n\t" \
		"movs pc, lr \n\t" \
		: \
		: "r" (current->program_counter), "r" (current->stack_pointer) \
	);

#endif
