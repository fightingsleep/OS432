/**
 * The function executed by the console process.
 * The console processes has queues of operations that it needs to perform.
 * Operations are either input (keyboard) or output (monitor).
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#include "console_proc.h"
#include "io_config.h"
#include "leds.h"
#include "memcpy.h"
#include "print.h"
#include "user_syscalls.h"
#include "tostring.h"
#include "keyboard.h"

/* Where to start copying. */
#define START_COPY_ADDRESS (void*) \
	(((unsigned int) framebuffer) \
		+ H_RESOLUTION * (V_SCREEN_CHARS - REFRESH_LINE) * V_CHAR \
		* BITS_PER_PIXEL / 8)
/* Where to start clearing. */
#define START_CLEAR_ADDRESS (void*) \
	(((unsigned int) framebuffer) \
		+ H_RESOLUTION * REFRESH_LINE * V_CHAR * BITS_PER_PIXEL / 8)
/* How much to clear. */
#define CLEAR_AMOUNT H_RESOLUTION * (V_SCREEN_CHARS - REFRESH_LINE) * V_CHAR \
	* BITS_PER_PIXEL / 8 / sizeof(unsigned int)
/* How much to copy. */
#define COPY_AMOUNT H_RESOLUTION * REFRESH_LINE * V_CHAR * BITS_PER_PIXEL / 8

/**
 * Move the contents of the screen up.
 */
void move_screen_up()
{
	unsigned int* temp = (unsigned int*) START_CLEAR_ADDRESS;
	int i;
	
	memcpy(framebuffer, START_COPY_ADDRESS, COPY_AMOUNT);
	for(i = 0; i < CLEAR_AMOUNT; i++)
	{
		temp[i] = 0;
	}
}

void console_proc()
{
	unsigned int cursorX = 0;	/* In cells, not pixels. */
	unsigned int cursorY = 0;	/* In cells, not pixels. */
	unsigned int numCanPrint;
	unsigned int numPrinted;
	unsigned int status;
	unsigned int size;
	char* string;
	char letter;
	int x = 0;
	int y = 0;	

	unsigned int pid;
	struct io_request data;
	
	while(1)
	{
		size = sizeof(struct io_request);
		status = osc_receive(&pid, &data, &size);
		
		if(status == 0)
		{
			switch(data.type)
			{
				case INPUT:
					KeyboardUpdate();
					letter = KeyboardGetChar();
					while(letter != '\n')
					{
						KeyboardUpdate();
						letter = KeyboardGetChar();
						ledon();
						DrawCharacter('X', x, y);
						DrawCharacter(letter, x+16, y);
						x++; y++;
						if(letter != 0 && letter != '\n')
						{
							DrawCharacter(letter, cursorX, cursorY);
							cursorX += 1;
						}
					}
					ledoff();
					break;
				
				case OUTPUT:
				/* Let it fall through to OUTPUT_LN case. */
				
				case OUTPUT_LN:
					string = data.string;
					numPrinted = 0;
					
					while(data.size > 0)
					{
						numCanPrint = H_SCREEN_CHARS - cursorX;
						if(numCanPrint > data.size)
						{
							numPrinted = data.size;
						}
						else
						{
							numPrinted = numCanPrint;
						}
						
						DrawString(string, numPrinted, cursorX * H_CHAR,
							cursorY * V_CHAR);
						
						cursorX = cursorX + numPrinted;
						if(cursorX == H_SCREEN_CHARS)
						{
							cursorX = 0;
							cursorY = cursorY + 1;
							if(cursorY == V_SCREEN_CHARS)
							{
								move_screen_up();
								cursorY = REFRESH_LINE;
							}
						}
						
						data.size = data.size - numPrinted;
						string = string + numPrinted;
					}
					
					if(data.type == OUTPUT_LN)
					{
						cursorX = 0;
						cursorY = cursorY + 1;
						if(cursorY == V_SCREEN_CHARS)
						{
							move_screen_up();
							cursorY = REFRESH_LINE;
						}
					}
					
					break;
			}
		}
	}
}
