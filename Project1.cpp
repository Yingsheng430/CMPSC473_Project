// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{
	

	cout << "\tOutput for 3 CPU FCFS\n";
	MyScheduler ms3 = MyScheduler(Policy::FCFS, 3);
	ms3.CreateThread(1, 24, 0, 9000);
	ms3.CreateThread(2, 3, 0, 9001);
	ms3.CreateThread(3, 4, 0, 9002);
	ms3.Go();
	/* Results should be:
	Thread ID : 9001 Finishing Time :  5 CPU No. : 1
	Thread ID : 9002 Finishing Time :  7 CPU No. : 2
	Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

	return 0;
}

