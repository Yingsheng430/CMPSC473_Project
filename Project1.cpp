// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{
	

	cout << "\tOutput for 3 CPU FCFS\n";
	MyScheduler ms3 = MyScheduler(Policy::STRFwoP, 2);
	
	ms3.CreateThread(2, 4, 0, 9002);
	ms3.CreateThread(2, 3, 0, 9001);
	ms3.CreateThread(2, 5, 0, 9000);
	ms3.Go();
	/* Results should be:
	Thread ID : 9001 Finishing Time :  5 CPU No. : 1
	Thread ID : 9002 Finishing Time :  7 CPU No. : 2
	Thread ID : 9000 Finishing Time : 25 CPU No. : 0  */

	/*MyScheduler ms2 = MyScheduler(Policy::FCFS, 4);
	ms2.CreateThread(3, 1, 0, 9002);
	ms2.CreateThread(2, 1, 0, 9001);
	ms2.CreateThread(1, 1, 0, 9000);
	ms2.CreateThread(5, 1, 0, 9002);
	ms2.CreateThread(6, 1, 0, 9001);
	ms2.CreateThread(7, 1, 0, 9000);
	ms2.Go();*/



	return 0;
}

