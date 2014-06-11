/* Methods related to printing to the screen */

#ifndef _PRINT_H_
#define _PRINT_H_

struct FrameBuferDescription* bufDesc;

/* This structure is filled out by GPU */
struct FrameBuferDescription 
{
	unsigned int width;
	unsigned int height;
	unsigned int vWidth;
	unsigned int vHeight;
	unsigned int pitch;
	unsigned int bitDepth;
	unsigned int x;
	unsigned int y;
	void* pointer;
	unsigned int size;
};

/* Use this to ask for a frame buffer. (Typically use width = 1024, height = 768, bitDepth = 16) */
struct FrameBuferDescription* InitialiseFrameBuffer(unsigned int width, unsigned int height, unsigned int bitDepth);

/* Set the graphics address for the printing methods in print.h */
void SetGraphicsAddress(struct FrameBuferDescription* value);

/* Draws a character at a given x and y coordinate */
unsigned int DrawCharacter(char character, unsigned int x, unsigned int y);

/* Draws a string at a given x and y coordinate */
void DrawString(char* string, unsigned int length, unsigned int x, unsigned int y);

/* Moves the frame buffer up one row */
void newRowOnScreen(struct FrameBuferDescription *bufDesc);

/* Clears the screen */
void clearScreen();

#endif
