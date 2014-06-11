/* ToString methods used for printing */

#include "tostring.h"
#include "memcpy.h"

char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

/**
 * out gets updated. out has to be at least 10 characters long (not counting null termination).
 */
void toHexString(void* a, char* out)
{
        int i = 0;
        out[0] = '0';
        out[1] = 'x';
        unsigned int b = (unsigned int) a;

        for(i = 1; i < 9; i++)
        {
                out[10 - i] = hex[b % 16];
                b = b / 16;
        }
}

/**
 * out gets updated. out has to be at least 32 characters long (not counting null termination).
 */
void toBinString(void* a, char* out)
{
        int i = 0;
        unsigned int b = (unsigned int) a;

        for(i = 31; i >= 0; i--)
        {
                out[i] = '0' + (b % 2);
                b = b / 2;
        }
}


int toDecimalString(int number, char* out)
{
        int i = 0;
        int b;
	if(number >= 0)
	{
		b = number;
	}
	else
	{
		b = -number;
	}

        do
        {
                out[10 - i] = '0' + (b % 10);
                b = b / 10;
		i++;
        } while(b > 0);

	if(number < 0)
	{
		out[10-i] = '-';
		i++;
	}

	if(i < 11)
	{
		memcpy((void *)out,(void *)(out+11-i),i);
	}

	return i;	
}
