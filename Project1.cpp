// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"


int main(int argc, char* argv[])
{
	
	int n =3;
	Policy p = FCFS;
	MyScheduler test(p, n);
	test.CreateThread(0, 10, 1, 1);//at,rt,pri,tid
	test.CreateThread(1, 10, 1, 2);
	test.CreateThread(3, 3, 1, 3);
	test.CreateThread(4, 4, 1, 4);
	test.CreateThread(5, 5, 1, 5);
	test.Go();	
	return 0;
}

