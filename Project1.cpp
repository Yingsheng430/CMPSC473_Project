// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{

	

	cout << "STRFwP Policy, 3 CPUs\n";
	MyScheduler ms3 = MyScheduler(Policy::STRFwP, 3);
	ms3.CreateThread(0, 12, 0, 0);
	ms3.CreateThread(5, 2, 2, 1);
	ms3.CreateThread(3, 7, 1, 2);
	ms3.CreateThread(9, 1, 10, 3);
	ms3.CreateThread(1, 4, 3, 4);
	ms3.CreateThread(5, 2, 3, 5);
	ms3.CreateThread(1, 4, 3, 6);

	ms3.Go();

	/*
	Thread ID : 6 Finishing Time : 5 CPU No. : 0
	Thread ID : 4 Finishing Time : 5 CPU No. : 1
	Thread ID : 5 Finishing Time : 7 CPU No. : 0
	Thread ID : 1 Finishing Time : 7 CPU No. : 1
	Thread ID : 2 Finishing Time : 10 CPU No. : 0
	Thread ID : 3 Finishing Time : 10 CPU No. : 1
	Thread ID : 0 Finishing Time : 16 CPU No. : 0
	All the Threads have been executed !! .. Exiting Scheduler ..
	*/
	////how to continue with another set of input?
	//when do you need to use new? 
	//Th
	return 0;
}

