/* Code to set up clock interrupts */

#include "interrupts.h"

/* Set the predivider register */
void loadPreDivValue(unsigned int value)
{
	unsigned int *tmp = (unsigned int *)TIMERPREDIV;
	*tmp = value;
}

/* Acknowledge timer interrupt */
void ackTimerInterrupt()
{
	unsigned int *x = (unsigned int *)TIMERACKREG;
	*x = 0;
}

/* Turn the timer off */
void disableTimer()
{
        unsigned int *x = (unsigned int *)TIMERCONTROL;
        unsigned int y = *(x);
        *x = (y & ~(1 << 7));
}


/* Turn the timer on */
void enableTimer()
{
	unsigned int *x = (unsigned int *)TIMERCONTROL;
	unsigned int y = *(x);
	*x = (y | 1 << 7);
}

/* Tell timer to fire interrupts */
void enableTimerInterrupts()
{
        unsigned int *a = (unsigned int *)IRQENABLEREG;
        unsigned int b = *(a);
        unsigned int *x = (unsigned int *)TIMERCONTROL;
        unsigned int y = *(x);
	ackTimerInterrupt();
	*a = (b | 1);
        *x = (y | 1 << 5);
}

/* Get timer value */
unsigned int getTimerValue()
{
	unsigned int *tmp = (unsigned int *)ARMTIMERVAL;
	unsigned int time = *(tmp);
	return time;
}

/* Load value into timer */
void loadTimerValue(unsigned int time)
{
	unsigned int *tmp = (unsigned int *)TIMERLDADDR;
	*tmp = time;
}

/**
 * Initialize timer interrupts.
 */
void timer_interrupt_init()
{
	loadPreDivValue(PREDIVISOR);
	enableTimerInterrupts();
	loadTimerValue(TIMER_VALUE);
	enableTimer();
}
