/**
 * Prototypes for system calls available to be called by a user program.
 * 
 * Author: Omar Zarifi
 * Date: March 4, 2014
 */

#ifndef _USER_SYSCALLS_H_
#define _USER_SYSCALLS_H_

/******************************************************************************
 * Memory management.					[2]
 *****************************************************************************/

/* Allocate a chunk of memory of the desired size (in bytes) and return a
 * pointer to the chunk. */
void* osc_malloc(unsigned int size);
/* Free a previously allocated chunk of memory. */
void osc_free(void* address);

/******************************************************************************
 * Inter-process communication.			[4]
 *****************************************************************************/

/* Send a message of (at most) the given size to the given process. Returns 0
 * on success, non-zero on failure.
 * This blocks until the receiver replies. */
unsigned int osc_send(unsigned int pid, void* msg, unsigned int size,
	void* reply, unsigned int* r_size);
/* Similar to osc_send() described above; however, this call is asynchronous.
 * That is, the sender is not blocked, but there is no guarantee that the
 * receiver ever gets the message. */
unsigned int osc_async_send(unsigned int pid, void* msg, unsigned int size);
/* Receive a message of (at most) the given size. When the call returns, pid
 * holds the sender PID, and size holds the actual message size. Returns 0 on
 * success, non-zero on failure.
 * Note that this call blocks until a message is sent by another process. */
unsigned int osc_receive(unsigned int* pid, void* msg, unsigned int* size);
/* Reply to a process that is waiting for a reply from this process. Returns 0
 * on success, non-zero on failure. */
unsigned int osc_reply(unsigned int pid, void* msg, unsigned int size);

/******************************************************************************
 * Process-related.						[7]
 *****************************************************************************/

/* Return the PID of the calling process. */
unsigned int osc_getpid();
/* Return the PID of the parent of the calling process. */
unsigned int osc_getppid();
/* Create a new process. The new process starts executing the given function.
 * On failure returns 0. Otherwise, returns the PID of the new child. */
unsigned int osc_create_process(unsigned int (*function)(void));
/* Wait for the child with the given PID to exit. Returns the exit code of the
 * child. */
unsigned int osc_waitpid(unsigned int pid);
/* Terminate the calling process with the given exit code. */
void osc_exit(unsigned int ret);
/* Sleep for (at least) the given duration (in milliseconds). */
void osc_sleep(unsigned int duration);
/* Voluntarily give up the processor. */
void osc_yield();

/******************************************************************************
 * Input/output.						[3]
 *****************************************************************************/

/* Print the given string at the cursor position. Size of the string must also
 * be provided. */
void osc_print_string(char* string, unsigned int size);
/* Print the given string at the cursor position, followed by a new line. Size
 * of the string (without the new line) must also be provided. */
void osc_print_line(char* string, unsigned int size);
/* Get a string from the keyboard. Maximum size of the string must also be
 * provided. Size will contain the actual number of characters read. */
void osc_get_string(char* string, unsigned int* size);

/* Prints a string to the screen on the current line */
void osc_drawstring(void *string, unsigned int length);

/* Prints a string to the screen on its own line */
void osc_drawstringln(void *string, unsigned int length);

/* Gets a string from the keyboard */
void osc_getstring(char *string, unsigned int maxlength, unsigned int *lengthread);

/* Draws a line on the screen */
void osc_drawline(unsigned int p1x, unsigned int p1y, unsigned int p2x, unsigned int p2y);

/* 
 * Changes the text color on the screen
 * Do not give this function a number greater than 65635
*/
void osc_changeTextColor(unsigned int color);

/******************************************************************************
 * Miscellaneous.						[1]
 *****************************************************************************/

/* Return the system time (milliseconds). */
unsigned long long osc_gettime();

#endif
