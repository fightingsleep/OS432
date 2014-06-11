/*
 * This file contains the scheduling and context switching facility.
 * 
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew 
 */

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

/**
 * Schedule and switch to an active process.
 * Note: this routine does not return. If a process blocks itself, then calls
 * schedule(), execution may at a later point resume after the schedule() call.
 * However, this is a result of another process unblocking the blocked process,
 * and the scheduler scheduling it.
 */
void schedule();

#endif
