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
bool compare(ThreadDescriptorBlock* a, ThreadDescriptorBlock* b)
{
	return(a->arriving_time < b->arriving_time);
}

void MyScheduler::firstcome(queue<ThreadDescriptorBlock*> &que, int &timer, int& i, bool& empty)
{
	
	//sort(que.begin(), que.end(), compare);
	if (que.empty())
	{
		empty = true;
	}
	else
	{
		if (que.front()->arriving_time <= timer)
		{
			CPUs[i] = que.front();
			que.pop();
		}
		/*if (!que.empty())
		cout << "Time: " << timer << " CPU: " << i << " Thread: " << que.front()->tid << endl;*/
	}

}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
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
			}
			return true;
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
