#include "user_programs.h"
#include "tostring.h"

unsigned int printA()
{
	char a[] = "A";
	while(1)
	{
		osc_drawstring(a, 1);
		osc_sleep(1000);
	}
	return 0;
}


unsigned int printB()
{
	char b[] = "B";
        while(1)
        {       
                osc_drawstring(b, 1);
		osc_sleep(1000);
        }
        return 0;
}


unsigned int pidTalk()
{
	unsigned int childPid;
	char msg[] = "Hello my child";
	char msg2[] = "Parent is sending the message: ";

	childPid = osc_create_process(pidTalkChild);

	osc_drawstring(msg2, 31);
	osc_drawstring(msg, 14);
	osc_drawstringln(" ", 1);
	osc_async_send(childPid, (void *) msg, 14);

	while(1);

	return 0;
}

unsigned int pidTalkChild()
{
	unsigned int *pidfrom;
	void *msg;
	unsigned int *size;
	char msg2[] = "Child has received the message: ";
	char msg3[] = "Success!";

	
	osc_receive(pidfrom, msg, size);

	osc_drawstring(msg2, 32);
	osc_drawstring(msg, *size);
	osc_drawstringln(msg3, 8);

	while(1);
	
	return 0;
}
