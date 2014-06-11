#include "print.h"

int xcoord = 0;
int ycoord = 16;

unsigned int printA()
{
	char a[] = "A";
	while(1)
	{
		osc_drawstring(a, 1, xcoord, ycoord);
		xcoord+=8;
		if(xcoord >= 1024)
		{
			xcoord = 0;
			ycoord += 16;
			if(ycoord >= 768)
			{
				break;
			}
		}
	}
	while(1);
	return 0;
}


unsigned int printB()
{
	char b[] = "B";
        while(1)
        {       
                osc_drawstring(b, 1, xcoord, ycoord);
                xcoord+=8;
                if(xcoord >= 1024)
                {
                        xcoord = 0;
                        ycoord += 16;
			if(ycoord >= 768)
			{
				break;
			}
                }
        }
	while(1);
        return 0;
}

/*
unsigned int pidTalk(){
	unsigned int childPid;
	char sending[] = "Sending Message";
	char recieved[] = "Recieved Message";
	char message[] = "Parent Message";
	char *recievedMessage;
	int *recievedSize;
	
	childPid = osc_create_process(pidTalkChild);
	osc_print_string(sending, 16);
	osc_send(childPid, (void*)message, 15, recievedMessage, recievedSize);
	osc_print_string(recieved, 17);
	osc_print_string(recievedMessage, recievedSize);

	return 0;
}

unsigned int pidTalkChild(){
	unsigned int parentPid;
	char sending[] = "Sending Message";
	char recieved[] = "Recieved Message";
	char message[] = "Child Message";
	char *recievedMessage;
	int *recievedSize;
	
	parentPid = osc_getppid();
	osc_print_string(sending, 16);
	osc_recieve(parentPid, recievedMessage, recievedSize);
	osc_print_string(recieved, 17);
	osc_print_string(recievedMessage, recievedSize);
	osc_reply(parentPid, message, 14);
	
	return 0;

}
*/
