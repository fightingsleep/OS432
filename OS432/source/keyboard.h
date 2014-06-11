/* 
 * Keyboard/USB related functions
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
 *
*/

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

unsigned int UsbInitialise();

void UsbCheckForChange();

void KeyboardUpdate();

char KeyboardGetChar();

#endif
