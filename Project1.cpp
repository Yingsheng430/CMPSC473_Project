// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{
	

	
	MyScheduler myScheduler(FCFS, 2);

	myScheduler.CreateThread(1, 5, 1, 0);
	myScheduler.CreateThread(3, 13, 2, 1);
	myScheduler.CreateThread(0, 32, 2, 2);
	myScheduler.CreateThread(2, 10, 2, 3);
	myScheduler.Go();
	/*Our output
	Thread ID : 0 Finishing Time : 6 CPU No. : 1
	Thread ID : 3 Finishing Time : 16 CPU No. : 1
	Thread ID : 1 Finishing Time : 29 CPU No. : 1
	Thread ID : 2 Finishing Time : 32 CPU No. : 0
	*/


	/* My results, assuming my project works...
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 6 Finishing Time : 9 CPU No. : 1
	Thread ID : 0 Finishing Time : 12 CPU No. : 0
	Thread ID : 1 Finishing Time : 14 CPU No. : 0
	Thread ID : 5 Finishing Time : 16 CPU No. : 0
	Thread ID : 2 Finishing Time : 16 CPU No. : 1
	Thread ID : 3 Finishing Time : 17 CPU No. : 0
	*/


	////how to continue with another set of input?
	return 0;
}

