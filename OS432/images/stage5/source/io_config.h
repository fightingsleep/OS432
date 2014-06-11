/**
 * Input/output configuration.
 * Note: H - horizontal, V - vertical.
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#ifndef _IO_CONFIG_H_
#define _IO_CONFIG_H_

#include "print.h"

/* Output resolution. */
#define H_RESOLUTION 1024
#define V_RESOLUTION 768

/* Output bits per pixel. */
#define BITS_PER_PIXEL 16

/* Character size. */
#define H_CHAR 8
#define V_CHAR 16

/* Number of characters that can be printed on screen. */
#define H_SCREEN_CHARS (H_RESOLUTION / H_CHAR)
#define V_SCREEN_CHARS (V_RESOLUTION / V_CHAR)

/* Maximum size of an input/output string. */
#define MAX_IO_STRING_SIZE 256

/* Number of lines to leave when contents of the screen must be moved up. */
#define REFRESH_LINE 10

/**
 * Initialize the input device (keyboard).
 */
void input_init();

/**
 * Initialize the output device (monitor).
 */
void output_init();

/**
 * Framebuffer description structure
 */
struct FrameBuferDescription* framebuffer;

#endif
