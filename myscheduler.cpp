//myschedule.cpp
/*
Name: JIaxin Liang
Name: Xuejian Zhou

*/


/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"
#include<algorithm>
#include <iterator>
vector<ThreadDescriptorBlock*> q;
vector<ThreadDescriptorBlock*>newq;

int z = 0;
bool first = true;
bool setbegin =false;
int beginat = 0;
int endat = 0;
vector<int>invalid_tid;
void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	
	ThreadDescriptorBlock *newthread = new ThreadDescriptorBlock;
	newthread->arriving_time = arriving_time;
	newthread->remaining_time = remaining_time;
	newthread->priority = priority;
	newthread->tid = tid;
	q.push_back(newthread);

	/*for (int i = 0; i < q.size(); i++)
	{
		cout << "que number " << q[i]->tid << "is created" << endl;
	}
	cout << "\n";*/
	
}
void MyScheduler::freeque(vector<ThreadDescriptorBlock*> &que)
{
	while (!que.empty())
	{
		que.pop_back();
	}
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
void MyScheduler::shortest_wo(vector<ThreadDescriptorBlock*> &que, int &timer, int& i, int&z,int&begin, int&end)
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
		if (z == que.size() - 1)
		{
			end = z;
			setbegin = false;
		}
		else if (z != que.size() - 1 && que[z + 1]->arriving_time > timer)
		{
			end = z;
			setbegin = false;
			//cout << "end at " << end << endl;
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
void MyScheduler::sort_SRTwP(vector<ThreadDescriptorBlock*> &que, int &timer, vector<ThreadDescriptorBlock*>&newque,int&beginat)	//push the ones that are ready to new que, sort it according to rt
{

	
	while (beginat < que.size() &&timer == que[beginat]->arriving_time)
	{
		newque.push_back(que[beginat]);
		beginat++;
	}
	if (!newque.empty())
	{
		for (int p = 0; p< newque.size()-1; p++)//sort accroding to remaining time
		{
			for (int q = p + 1; q < newque.size(); q++)
			{
				if (newque[p]->remaining_time > newque[q]->remaining_time)
				{
					ThreadDescriptorBlock* temp;
					temp = newque[p];
					newque[p] = newque[q];
					newque[q] = temp;
				}
			}
		}
		
	}

}
void MyScheduler::sort_PBS(vector<ThreadDescriptorBlock*> &que, int &timer, vector<ThreadDescriptorBlock*>&newque, int&beginat)	//push the ones that are ready to new que, sort it according to rt
{


	while (beginat < que.size() && timer == que[beginat]->arriving_time)
	{
		newque.push_back(que[beginat]);
		beginat++;
	}
	if (!newque.empty())
	{
		for (int p = 0; p< newque.size() - 1; p++)//sort accroding to remaining time
		{
			for (int q = p + 1; q < newque.size(); q++)
			{
				if (newque[p]->priority < newque[q]->priority)
				{
					ThreadDescriptorBlock* temp;
					temp = newque[p];
					newque[p] = newque[q];
					newque[q] = temp;
				}
			}
		}

	}

}

bool MyScheduler::Dispatch()
{
	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	//cout << "Dispatch running" << endl;
	switch (policy)
	{
	case FCFS://First Come First Serve
		while (z < q.size())
		{
			for (int j = 0; j < num_cpu; j++)
			{
				if (CPUs[j] == NULL&& z < q.size())
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
				//timer = 0;
				freeque(q);
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
				if (CPUs[j] == NULL&& z < q.size())
				{
					find_range(q, timer, z, beginat, endat, setbegin);
					shortest_wo(q, timer, j, z, beginat, endat);
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
				//reset
				z = 0;
				first = true;
				setbegin = false;
				beginat = 0;
				endat = 0;
				timer = 0;
				freeque(q);
				return false;
			}
		}
		break;
	case STRFwP:	//Shortest Time Remaining First, with preemption
		
		{
			sort(q.begin(), q.end(), compare);// ort according to AT
			sort_SRTwP(q, timer, newq, beginat); //add in new thread to newque at new timer sort them 
			z = 0;//new queue iterator
			endat = 0;
			while (newq[z]->remaining_time == 0)
			{
				z++;
				endat++;
				if (endat == q.size())
				{
					freeque(q);
					freeque(newq);
					beginat = 0; 
					endat = 0;
					z = 0;
					return false;
				}
			}
			
			for (int i = 0; i < num_cpu; i++)
			{
				//in_or_out(z, CPUs, num_cpu,in);
			
				if (z < newq.size())//not in 
				{

					for (int j = i+1; j < num_cpu; j++)
					{
						CPUs[j] = NULL;
					}
					CPUs[i] = newq[z];
					z++;
					//}
				}

			}
			
			return true;
		}
		
		return false;

		break;
	case PBS:		//Priority Based Scheduling, with preemption
	{
						sort(q.begin(), q.end(), compare);// ort according to AT
						sort_PBS(q, timer, newq, beginat); //add in new thread to newque at new timer sort them 
						z = 0;//new queue iterator
						endat = 0;
						for (int i = 0; i < newq.size(); i++)
						{
							if (newq[i]->remaining_time == 0)
							{
								endat++;
							}
							if (endat == q.size())
							{
								freeque(q);
								freeque(newq);
								beginat = 0;
								endat = 0;
								z = 0;
								return false;
							}
						}

						for (int i = 0; i < num_cpu; i++)
						{
							//in_or_out(z, CPUs, num_cpu,in);

							if (z < newq.size())//not in 
							{
								for (int j = i + 1; j < num_cpu; j++)
								{
									CPUs[j] = NULL;
								}

								if (z < newq.size())
								{
									while (newq[z]->remaining_time == 0)
									{
										z++;
									}
									if (z < newq.size())
									{
										CPUs[i] = newq[z];
									}
									z++;
								}
								//}
							}

						}
						return true;
	}
		return false;
		break;
	default:
		cout << "Invalid policy!";
		throw 0;
	}


}