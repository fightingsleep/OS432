/* Code to enable clock interrupts */

#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#define ARMTIMERBASE (void *)0x2000B000;
#define TIMERCONTROL (void *)0x2000B408;
#define IRQENABLEREG (void *)0x2000B218;
#define ARMTIMERVAL  (void *)0x2000B404;
#define TIMERLDADDR  (void *)0x2000B400;
#define TIMERACKREG  (void *)0x2000B40C;
#define TIMERPREDIV  (void *)0x2000B41C;

/* Constants that determine frequency of clock interrupts. */
#define PREDIVISOR 100
#define TIMER_VALUE 0xFFFFFFFF

/* Set the predivider register */
void loadPreDivValue(unsigned int value);

/* Acknowledge timer interrupt */
void ackTimerInterrupt();

/* Turn the timer off */
void disableTimer();

/* Turn the timer on */
void enableTimer();

/* Tell timer to fire interrupts */
void enableTimerInterrupts();

/* Get timer value */
unsigned int getTimerValue();

/* Load value into timer */
void loadTimerValue(unsigned int time);

/**
 * Initialize timer interrupts.
 */
void timer_interrupt_init();

#endif
