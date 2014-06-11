#include "print.h"

void newRowOnScreen(struct FrameBuferDescription *bufDesc)
{
        int i;
        int row = 16*2048;

        for(i = 0; i < bufDesc->size-row; i++)
        {
                *((char*)(bufDesc->pointer + i)) = 0;
                *((char*)(bufDesc->pointer + i)) = *((char*)(bufDesc->pointer + i + row));
        }
        for(i = bufDesc->size-row; i<bufDesc->size; i++){
                *((char*)(bufDesc->pointer + i)) = 0;
        }
}

void clearScreen(struct FrameBuferDescription *bufDesc)
{
        int i;

        for(i = 0; i < bufDesc->size; i++)
        {
                *((char*)(bufDesc->pointer + i)) = 0;
	}
}

