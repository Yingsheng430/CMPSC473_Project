//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
#include<queue>
#include<algorithm>
queue<ThreadDescriptorBlock*> q;
bool empty = false;
void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	
	ThreadDescriptorBlock *newthread = new ThreadDescriptorBlock;
	newthread->arriving_time = arriving_time;
	newthread->remaining_time = remaining_time;
	newthread->priority = priority;
	newthread->tid = tid;
	q.push(newthread);
	//free(newthread);

}

void MyScheduler::firstcome(queue<ThreadDescriptorBlock*> &que, int &num, int& i, bool& empty)
{
		if (que.empty())
		{
			empty = true;
		}
		else
		{
			CPUs[i] = que.front();
			que.pop();
			/*if (!que.empty())
			cout << "Time: " << timer << " CPU: " << i << " Thread: " << que.front()->tid << endl;*/
		}
		


}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	/*
	for (int i = 1; i <=num_cpu; i++)
	{
	if (CPUs[i] != NULL)
	{
	continue;
	return true;
	}
	if (!empty)//null and empty
	{
	firstcome(q, timer, i, empty);
	return true;
	}
	else//empty
	{
	for (int j = 1; j <= num_cpu; j++)
	{
	if (CPUs[j] != NULL)
	{
	return true;
	}
	if (j == num_cpu)
	{
	return false;
	break;
	}
	}
	}
	return false;
	}
	*/
	switch(policy)
	{

	case FCFS://First Come First Serve
		while (!empty)
		{
			for (int j = 0; j < num_cpu; j++)
			{
				if (CPUs[j] == NULL)
				{
					firstcome(q, timer, j, empty);
				}
				return  true;
			}
		}
		for (int i = 0; i < num_cpu; i++)
		{
			if (CPUs[i] != NULL)
				return true;
			if (i == num_cpu - 1)
				return false;
		}
		break;
			
		case STRFwoP:	//Shortest Time Remaining First, without preemption

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption

			break;
		case PBS:		//Priority Based Scheduling, with preemption
			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	return true;
}
