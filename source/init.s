.section .init
.globl _start
_start:

/* 
 * This code jumps to initalize() in main.c
 * It also contains the instructions that are used in the interrupt description
 * table that is placed at the beginning of memory. Along with other
 * instructions needed for process creation and general initalization
 * 
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
*/

mov sp, #0x8000			/* 0x8000 */
b initialize			/* 0x8004 */
b master_process		/* 0x8008 */
ldr pc, _dummy_reset_handler_address			/* 0x800C */
ldr pc, _dummy_undefined_handler_address		/* 0x8010 */
ldr pc, _dummy_svc_handler_address				/* 0x8014 */
ldr pc, _dummy_prefetch_abort_handler_address	/* 0x8018 */
ldr pc, _dummy_data_abort_handler_address		/* 0x801C */
mov r0, r0						/* 0x8020 */
ldr pc, _dummy_irq_handler_address				/* 0x8024 */
ldr pc, _dummy_fiq_handler_address				/* 0x8028 */
_dummy_reset_handler_address:
mov r0, r0				/* 0x802C */
_dummy_undefined_handler_address:
mov r0, r0				/* 0x8030 */
_dummy_svc_handler_address:
mov r0, r0				/* 0x8034 */
_dummy_prefetch_abort_handler_address:
mov r0, r0				/* 0x8038 */
_dummy_data_abort_handler_address:
mov r0, r0				/* 0x803C */
_dummy_irq_handler_address:
mov r0, r0				/* 0x8040 */
_dummy_fiq_handler_address:
mov r0, r0				/* 0x8044 */
mov r0, r0				/* 0x8048 */
mov r0, r0				/* 0x804C */
b svc_handler			/* 0x8050 */
mov r0, r0				/* 0x8054 */
mov r0, r0				/* 0x8058 */
b irq_handler			/* 0x805C */
mov r0, r0				/* 0x8060 */
b console_proc			/* 0x8064 */
b new_process			/* 0x8068 */
