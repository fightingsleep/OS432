/*
 * This file contains basic user programs used for testing the OS
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew   
 *
*/

#ifndef USER_PROGRAMS_H
#define USER_PROGRAMS_H

/* Print the letter A forever */
unsigned int printA();

/* Print the letter B forever */
unsigned int printB();

/* Print the letter C forever */
unsigned int printC();

/* Parent IPC test process */
unsigned int pidTalk();

/* Child IPC test program */
unsigned int pidTalkChild();

/* Draws lines infinitely */
unsigned int lineDraw();


#endif
