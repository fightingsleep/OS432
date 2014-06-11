	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"int_handlers.c"
	.text
	.align	2
	.global	idt_init
	.type	idt_init, %function
idt_init:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #32768
	add	r3, r3, #44
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L3:
	ldr	r3, [fp, #-8]
	mov	r2, r3, asl #2
	ldr	r3, [fp, #-12]
	add	r2, r3, r2
	ldr	r3, [fp, #-8]
	add	r3, r3, #8192
	add	r3, r3, #18
	mov	r3, r3, asl #2
	str	r3, [r2, #0]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #6
	ble	.L3
	mov	r0, #0
	mov	r1, #32768
	add	r1, r1, #12
	mov	r2, #60
	bl	memcpy
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
	.size	idt_init, .-idt_init
	.align	2
	.global	svc_handler
	.type	svc_handler, %function
svc_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
@ 33 "int_handlers.c" 1
	mov sp, #32768 
	push {r12} 
	push {r11} 
	push {r10} 
	mov r10, #0x1F 
	mrs r11, cpsr 
	mov r12, r11 
	orr r11, r11, r10 
	msr cpsr, r11 
	push {lr} 
	push {r0} 
	push {r1} 
	push {r2} 
	push {r3} 
	push {r4} 
	push {r5} 
	push {r6} 
	push {r7} 
	push {r8} 
	push {r9} 
	mov r0, sp 
	msr cpsr, r12 
	pop {r1} 
	pop {r2} 
	pop {r3} 
	mrs r4, spsr 
	mov r5, sp 
	mov sp, r0 
	push {r1} 
	push {r2} 
	push {r3} 
	push {r4} 
	mov r0, sp 
	mov r1, lr 
	mov sp, r5 
	mov r4, r0 
	mov r5, r1 
	
	stmfd	sp!, {r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #36
	ldr	r3, .L7
	ldr	r0, [r3, #0]
	ldr	r3, .L7
	ldr	r1, [r3, #0]
@ 0 "" 2
	str	r4, [r0, #8]
	str	r5, [r1, #12]
	ldr	r3, .L7
	ldr	r3, [r3, #0]
	ldr	r3, [r3, #8]
	add	r3, r3, #32
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-32]
	add	r3, r3, #20
	ldr	r2, [r3, #0]
	ldr	r3, .L7+4
	ldr	r4, [r3, r2, asl #2]
	ldr	r3, [fp, #-32]
	add	r3, r3, #16
	ldr	r1, [r3, #0]
	ldr	r3, [fp, #-32]
	add	r3, r3, #12
	ldr	lr, [r3, #0]
	ldr	r3, [fp, #-32]
	add	r3, r3, #8
	ldr	r2, [r3, #0]
	ldr	r3, [fp, #-32]
	add	r3, r3, #4
	ldr	ip, [r3, #0]
	ldr	r3, [fp, #-32]
	ldr	r3, [r3, #0]
	str	r3, [sp, #0]
	mov	r0, r1
	mov	r1, lr
	mov	r3, ip
	mov	lr, pc
	bx	r4
	mov	r3, r0
	mov	r4, r1
	str	r3, [fp, #-28]
	str	r4, [fp, #-24]
	sub	r2, fp, #28
	ldmia	r2, {r1-r2}
	mov	r3, r2
	mov	r4, #0
	str	r3, [fp, #-20]
	ldr	r3, [fp, #-28]
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-32]
	add	r2, r3, #16
	ldr	r3, [fp, #-20]
	str	r3, [r2, #0]
	ldr	r3, [fp, #-32]
	add	r2, r3, #20
	ldr	r3, [fp, #-16]
	str	r3, [r2, #0]
	ldr	r3, .L7
	ldr	r3, [r3, #0]
	ldr	r2, [r3, #12]
	ldr	r3, .L7
	ldr	r3, [r3, #0]
	ldr	r3, [r3, #8]
@ 46 "int_handlers.c" 1
	mov lr, r2 
	mov r0, sp 
	mov r10, #0x1F 
	mrs r11, cpsr 
	mov r12, r11 
	orr r11, r11, r10 
	msr cpsr, r11 
	mov sp, r3 
	pop {r5} 
	pop {r6} 
	pop {r7} 
	pop {r8} 
	pop {r9} 
	mov r1, sp 
	mov sp, r0 
	push {r9} 
	push {r8} 
	push {r7} 
	push {r6} 
	push {r5} 
	mov r9, sp 
	mov sp, r1 
	pop {r8} 
	pop {r7} 
	pop {r6} 
	pop {r5} 
	pop {r4} 
	pop {r3} 
	pop {r2} 
	pop {r1} 
	pop {r0} 
	pop {lr} 
	msr cpsr, r12 
	mov sp, r9 
	pop {r9} 
	msr spsr, r9 
	pop {r12} 
	pop {r11} 
	pop {r10} 
	pop {r9} 
	movs pc, lr 
	
@ 0 "" 2
	sub	sp, fp, #8
	ldmfd	sp!, {r4, fp, lr}
	bx	lr
.L8:
	.align	2
.L7:
	.word	current
	.word	syscall_functions
	.size	svc_handler, .-svc_handler
	.align	2
	.global	irq_handler
	.type	irq_handler, %function
irq_handler:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
@ 51 "int_handlers.c" 1
	mov sp, #32768 
	push {r12} 
	push {r11} 
	push {r10} 
	mov r10, #0x1F 
	mrs r11, cpsr 
	mov r12, r11 
	orr r11, r11, r10 
	msr cpsr, r11 
	push {lr} 
	push {r0} 
	push {r1} 
	push {r2} 
	push {r3} 
	push {r4} 
	push {r5} 
	push {r6} 
	push {r7} 
	push {r8} 
	push {r9} 
	mov r0, sp 
	msr cpsr, r12 
	pop {r1} 
	pop {r2} 
	pop {r3} 
	mrs r4, spsr 
	mov r5, sp 
	mov sp, r0 
	push {r1} 
	push {r2} 
	push {r3} 
	push {r4} 
	mov r0, sp 
	mov r1, lr 
	mov sp, r5 
	mov r4, r0 
	mov r5, r1 
	
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r3, .L11
	ldr	r0, [r3, #0]
	ldr	r3, .L11
	ldr	r1, [r3, #0]
@ 0 "" 2
	str	r4, [r0, #8]
	str	r5, [r1, #12]
	ldr	r3, .L11
	ldr	r2, [r3, #0]
	ldr	r3, .L11
	ldr	r3, [r3, #0]
	ldr	r3, [r3, #12]
	sub	r3, r3, #4
	str	r3, [r2, #12]
	bl	schedule
	sub	sp, fp, #4
	ldmfd	sp!, {fp, lr}
	bx	lr
.L12:
	.align	2
.L11:
	.word	current
	.size	irq_handler, .-irq_handler
	.comm	kernel_heap,12,4
	.comm	kernel_stack,4,4
	.comm	current,4,4
	.comm	processes,8,4
	.comm	sleeping,8,4
	.comm	syscall_functions,64,4
	.ident	"GCC: (Sourcery G++ Lite 2008q3-66) 4.3.2"
