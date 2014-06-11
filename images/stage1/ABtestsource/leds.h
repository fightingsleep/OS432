/* Method to manipulate the pi's LED's */

#ifndef _LEDS_H_
#define _LEDS_H_

/* Sets the function of a pin */
void SetGpioFunction(unsigned int gpioRegister, unsigned int function);

/* Sets the pin high or low */
void SetGpio(unsigned int gpioRegister, unsigned int value);

/* Turns the ACT LED on */
void ledon();

/* Turns the ACT LED off */
void ledoff();

/* Blinks the ACT LED. WARNING: WILL NOT RETURN (INFINITE LOOP) */
void ledblink();

#endif
