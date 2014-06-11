/* 
 * A simple memory copy routine
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew
*/

void* memcpy(void* dest, const void* source, unsigned int size)
{
	unsigned int i;
	
	if(dest < source)
	{
		for(i = 0; i < size; i++)
		{
			((char*) dest)[i] = ((char*) source)[i];
		}
	}
	else
	{
		for(i = size - 1; i > 0; i--)
		{
			((char*) dest)[i] = ((char*) source)[i];
		}
		((char*) dest)[0] = ((char*) source)[0];
	}
	
	return dest;
}
