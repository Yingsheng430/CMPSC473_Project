//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
#include<queue>
#include<algorithm>
#include <iterator>
#include<vector>
vector<ThreadDescriptorBlock*> q;
vector<ThreadDescriptorBlock*>temp;
int z = 0;

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	
	ThreadDescriptorBlock *newthread = new ThreadDescriptorBlock;
	newthread->arriving_time = arriving_time;
	newthread->remaining_time = remaining_time;
	newthread->priority = priority;
	newthread->tid = tid;
	q.push_back(newthread);
	

}
bool compare(ThreadDescriptorBlock* a, ThreadDescriptorBlock* b)
{
	
	return a->arriving_time < b->arriving_time;
}

bool compareRT(ThreadDescriptorBlock* a, ThreadDescriptorBlock* b)
{

	return a->remaining_time < b->remaining_time;
}

void MyScheduler::firstcome(vector<ThreadDescriptorBlock*> &que, int &timer, int& i, int& z)
{
	
	if (z == 0)
	{
		sort(que.begin(), que.end(), compare);
	}
	if (que[z]->arriving_time <= timer)
	{
		CPUs[i] = que[z];
		z++;
		//que.erase(que.begin());
	}
}
void MyScheduler::shortest_wo(vector<ThreadDescriptorBlock*> &que, int &timer, int& i, int&z, vector<ThreadDescriptorBlock*>&temp)
{

	if (z == 0)
	{
		sort(que.begin(), que.end(), compare);
	}
	while (que[z]->arriving_time <= timer)
	{
		temp.push_back(que[z]);
		sort(temp.begin(), temp.end(), compareRT);
		z++;
	}
}


bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	//cout << "Disoatch running" << endl;
	switch (policy)
	{
	case FCFS://First Come First Serve
		//sortAT(q);
		while (z < q.size())
		{
			for (int j = 0; j < num_cpu; j++)
			{
				if (CPUs[j] == NULL)
				{
					firstcome(q, timer, j, z);
				}
			}
			return true;
		}
		for (int i = 0; i < num_cpu; i++)
		{
			while (CPUs[i] != NULL)
			{
				return true;
			}

			if (i == num_cpu - 1)
			{
				z = 0;
				/*for (vector<ThreadDescriptorBlock*>::iterator it = q.begin(); it != q.end(); it++)
				{
				delete(*it);
				}*/
				//where to free? execut
				return false;
			}
		}
		break;
	case STRFwoP://Shortest Time Remaining First, without preemption
		while (z < q.size())
		{
			for (int j = 0; j < num_cpu; j++)
			{
				if (CPUs[j] == NULL)
				{
					shortest_wo(q, timer, j, z, temp);
					while (!temp.empty())
					{
						CPUs[j] = temp[0];
						cout << temp[0]->tid << endl;
						if (temp.empty())
							break;
						temp.erase(temp.begin()+0);
					}
				}
			}
			return true;
		}
		for (int i = 0; i < num_cpu; i++)
		{
			while (CPUs[i] != NULL)
			{
				return true;
			}

			if (i == num_cpu - 1)
			{
				z = 0;
				/*for (vector<ThreadDescriptorBlock*>::iterator it = q.begin(); it != q.end(); it++)
				{
				delete(*it);
				}*/
				//where to free? execut
				return false;
			}
		}
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
