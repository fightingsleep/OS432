/* Keyboard/USB related functions */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

unsigned int UsbInitialise();

void UsbCheckForChange();

void KeyboardUpdate();

char KeyboardGetChar();

#endif
