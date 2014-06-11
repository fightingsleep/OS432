#include "io_config.h"

void clearScreen()
{
        int i;
        for(i = 0; i < framebuffer->size; i++)
        {
                *((char*)(framebuffer->pointer + i)) = 0;
        }
}
