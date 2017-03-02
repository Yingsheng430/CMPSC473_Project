// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{
	

	cout << "\tOutput for 2 CPU FCFS\n";
	MyScheduler myScheduler2(STRFwoP, 2);
	myScheduler2.CreateThread(0, 5, 1, 0);
	myScheduler2.CreateThread(5, 13, 2, 1);
	myScheduler2.CreateThread(6, 32, 2, 2);
	myScheduler2.CreateThread(2, 10, 2, 3);
	myScheduler2.Go();

	/*Our output
	Thread ID : 0 Finishing Time : 5 CPU No. : 0
	Thread ID : 3 Finishing Time : 12 CPU No. : 1
	Thread ID : 1 Finishing Time : 18 CPU No. : 0
	Thread ID : 2 Finishing Time : 44 CPU No. : 1
	*/


	
	////how to continue with another set of input?
	return 0;
}

