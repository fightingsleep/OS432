/* Methods to manipulate the pi's LED's */

#include "timer.h"
#include "leds.h"

/* Turns the ACT LED on */
void ledon()
{
	SetGpioFunction(16, 1);
	SetGpio(16, 0);
}

/* Turns the ACT LED off */
void ledoff()
{
	SetGpioFunction(16, 1);
	SetGpio(16, 1);
}

/* Blinks the ACT LED. WARNING: NEVER RETURNS (INFINITE LOOP)*/
void ledblink()
{
	while(1)
	{
		ledon();
		Wait(500000);
		ledoff();
		Wait(500000);
	}
}
