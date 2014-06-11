/*
 * This file contains basic user programs used for testing the OS
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew 
 *
*/


#include "user_programs.h"
#include "tostring.h"

unsigned int printA()
{
	char a[] = "A";
	while(1)
	{
		osc_drawstring(a, 1);
		osc_sleep(100);
	}
	return 0;
}


unsigned int printB()
{
	char b[] = "B";
        while(1)
        {       
                osc_drawstring(b, 1);
		osc_sleep(100);
        }
        return 0;
}

unsigned int printC()
{
        char c[] = "C";
        while(1)
        {
                osc_drawstring(c, 1);
                osc_sleep(100);
        }
        return 0;
}

unsigned int pidTalk()
{
	unsigned int childPid;
	char msg[] = "Hello my child";
	char msg2[] = "Parent is sending the message: ";
	char msg3[] = "Parent has received the message: ";
	unsigned int *pidfrom;
	void *msgreceived;
	unsigned int *size;
	char success[] = "Success!";

	*size = 100;
	childPid = osc_create_process(pidTalkChild);

	osc_drawstring(msg2, 31);
	osc_drawstring(msg, 14);
	osc_drawstringln(" ", 1);
	osc_async_send(childPid, (void *) msg, 14);

	osc_sleep(1000);
	osc_receive(pidfrom, msgreceived, size);
	osc_drawstringln(" ", 1);
	osc_drawstring(msg3, 33);
	osc_drawstring(msgreceived, *size);

	osc_drawstringln(" ", 1);
	osc_drawstringln(success, 8);

	while(1);

	return 0;
}

unsigned int pidTalkChild()
{
	unsigned int *pidfrom;
	void *msg;
	unsigned int *size;
	char msg2[] = "Child has received the message: ";
	char msg3[] = "Child is sending the message: ~ Hello parent ~ back to its parent";
	char msg4[] = "Hello parent";

	*size = 100;
	osc_receive(pidfrom, msg, size);
	osc_drawstring(msg2, 32);
	osc_drawstring(msg, *size);
	osc_drawstringln(" ", 1);

	osc_drawstringln(msg3, 65);

	osc_async_send(2, (void *) msg4, 12);

	while(1);
	
	return 0;
}

unsigned int lineDraw()
{
	int p1x = 0;
	int p1y = 0;
	int p2x = 0;
	int p2y = 0;
	int counter = 0;

	while(1)
	{
		p1x = counter % 1023;
		p2x = counter % 1019;
		p1y = counter % 767;
		p2y = counter % 763;
		counter = counter + osc_gettime() % 19374;
		if(counter >= 1046578321)
		{
			counter = osc_gettime() % 17339;
		}
		if(counter % 5)
		{
			osc_changeTextColor(counter % 65535);
		}
		osc_drawline(p1x, p1y, p2x, p2y);
		osc_sleep(10);
	}
}
