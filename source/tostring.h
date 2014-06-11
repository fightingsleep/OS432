/* 
 * ToString methods used for printing
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew 
*/

#ifndef _TOSTRING_H_
#define _TOSTRING_H_

/*
 * out gets updated. out has to be at least 10 characters long (not counting null termination).
 */
void toHexString(void* a, char* out);

/*
 * out gets updated. out has to be at least 32 characters long (not counting null termination).
 */
void toBinString(void* a, char* out);

/* Out gets updated. out has to be at least 11 characters long (not counting null termination) */
int toDecimalString(int number, char* out);

#endif
