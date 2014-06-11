/* 
 * Memory (kmalloc & malloc) testing function
 *
 * CMPT 432: Operating Systems
 * Group: Omar, Chris, Chad, Joseph, Matthew 
*/

int memtest(void){
	char* outMessage = "Memory Test Running";
	int i,j;
	void* points[10];
		DrawString(outMessage, 20, 0, 48);
	for(j = 0; j < 2000; j+=100);
		for(i = 0; i < 10; i++){
			points[i] = (void*)kmalloc(j);
		}
		for(i = 0; i < 10; i++){
			kfree(points[i]);
		}
	}
	/* TODO: Put in output for the required memory stats */
	return 1;

}

