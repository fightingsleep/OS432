/**
 * Input/output initialization routines.
 * 
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
 */

#include "io_config.h"
#include "keyboard.h"

void input_init()
{
	while(UsbInitialise() != 0);
	UsbCheckForChange();
}

void output_init()
{
	struct FrameBuferDescription* bufDesc = (struct FrameBuferDescription*) 
		InitialiseFrameBuffer(H_RESOLUTION, V_RESOLUTION, BITS_PER_PIXEL);
	framebuffer = bufDesc;
	SetGraphicsAddress(bufDesc);
}
