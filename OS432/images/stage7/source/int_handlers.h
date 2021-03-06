/**
 * This file contains interrupt handler function declarations.
 * Note that this file isn't used directly. The compiler-generated assembly is
 * manually modified and used. This is due to generated function prologues
 * modifying registers.
 * 
 * Author: Omar Zarifi
 * Date: March 19, 2014
 */

#ifndef _INT_HANDLERS_H_
#define _INT_HANDLERS_H_

/**
 * Initialize the interrupt descriptor table.
 */
void idt_init();

/**
 * Routine to handle a supervisor call.
 */
void svc_handler();

/**
 * Routine to handle an interrupt request.
 */
void irq_handler();

#endif
