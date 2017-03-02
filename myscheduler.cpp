//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
#include<queue>
#include<algorithm>
#include <iterator>
#include<vector>
vector<ThreadDescriptorBlock*> q;
int z = 0;
bool first = true;
bool setbegin =false;
int beginat = 0;
int endat = 0;
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
			
	}
}
void MyScheduler::shortest_wo(vector<ThreadDescriptorBlock*> &que, int &timer, int& i, int&z,int&begin, int&end, bool& setbegin)
{
	if (z == 0)
	{
		sort(que.begin(), que.end(), compare);
	}

	if (z <= endat)//multiple
	{
		
		
		if (first)
		{
			z = beginat;
			CPUs[i] = que[z];
			z++;
			first = false;
		}
		else
		{
			CPUs[i] = que[z];
			if (z == endat)
			{
				z = endat + 1;
				setbegin = false;
			}
			else
			z++;//reset so that does not exit the while 
		}

	}

}
void MyScheduler::find_range(vector<ThreadDescriptorBlock*> &que, int &timer, int z, int&begin, int&end, bool&setbegin)
{
	if (z == 0)
	{
		sort(que.begin(), que.end(), compare);
	}
	while (z < que.size() && que[z]->arriving_time <= timer)
	{
		if (z == que.size() - 1)
		{
			end = z;
		}
		else if (z != que.size() - 1 && que[z + 1]->arriving_time > timer)
		{
			end = z;
			//cout << "end at " << end << endl;
		}
		if (z == 0)
		{
			begin = z;

		}
		else if (z != 0 && que[z - 1]->arriving_time < timer&& !setbegin)
		{
			begin = z;
			setbegin = true;
			//cout << "begin at " << begin << endl;
		}

		z++;
	}
	for (int p = begin; p <end; p++)//sort accroding to remaining time
	{
		for (int q = p + 1; q <= end; q++)
		{
			if (que[p]->remaining_time > que[q]->remaining_time)
			{
				ThreadDescriptorBlock* temp;
				temp = que[p];
				que[p] = que[q];
				que[q] = temp;
			}
		}
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
		//cout << "dispatching";
		while (z < q.size())
		{
			for (int j = 0; j < num_cpu; j++)
			{
				if (CPUs[j] == NULL&& z <q.size())
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
				/*for (int j = 0; j < q.size(); j++)
				{
					free(q[j]);
				}*/
				return false;
				break;
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
					find_range(q, timer, z, beginat, endat,setbegin);
					shortest_wo(q, timer, j, z,beginat, endat,setbegin);
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
			if (i == num_cpu - 1)//reset and return false
			{
				z = 0;//reset z
				first = true;
				setbegin = false;
				beginat = 0;
				endat = 0;
				for (int j = 0; j < q.size(); j++)
				{
					free(q[j]);
				}
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
	
}
