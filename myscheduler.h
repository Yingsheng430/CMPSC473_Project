#pragma once
//myschedule.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()' 
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only 
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

#include "scheduler.h"
#include<queue>
#include<vector>
//Define your data structure here.
	/*
	*
	*
	*
	*
	*/

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure
	void freeque(vector<ThreadDescriptorBlock*> &que);
	void firstcome(vector<ThreadDescriptorBlock*>&, int &, int&, int&);
	void find_range(vector<ThreadDescriptorBlock*> &que, int& timer, int z, int&begin, int&end, bool &setb);
	void shortest_wo(vector<ThreadDescriptorBlock*>&, int &, int&, int&, int&, int&);
	void MyScheduler::sort_SRTwP(vector<ThreadDescriptorBlock*> &que, int &timer, vector<ThreadDescriptorBlock*>&newque, int&);
	void MyScheduler::sort_PBS(vector<ThreadDescriptorBlock*> &que, int &timer, vector<ThreadDescriptorBlock*>&newque, int&beginat);
	
};
