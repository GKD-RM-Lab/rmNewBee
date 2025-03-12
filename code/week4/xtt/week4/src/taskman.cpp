#include"taskman.h"
#include<string>
#include<iostream>

using namespace std;
void taskman::monitor()
{
	while(true)
	{
		int val = Out.exchange(0);
		if (val != 0)
		{
			printf("out:%d\n", val);
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}



void taskman::run()
{
	handler = thread(&taskman::monitor, this);
	while (true)
	{
		string command;
		cin >> command;
		if (command == "add") {
			int key;
			int kind;
			cin >> key >> kind;
			addTask(key, kind);
			cout << "successfully add " << endl;
		}
		else if (command == "callback")
		{
			int key;
			int msg;
			cin >> key >> msg;
			callback(key, msg);
		}
		else if (command == "pop")
		{
			popTask();
			cout << "successfully delete" << endl;
		}
		else {
			cout << "error command please input again" << endl;
		}


	}
}

void taskman:: addTask(int key,int kind)
{
	auto p2 = a.empty() ? &Out : a.back();
	a.push_back(new atomic<int>(0));
	auto p1 = a.back();

	taskBase* p=nullptr;
	if (kind == 1)
	{
		p = new task1(key, p1, p2);
	}
	else if (kind == 2)
	{
		p = new task2(key, p1, p2);
	}
	else if (kind == 3)
	{
		p = new task3(key, p1, p2);
	}
	
	TaskMap[key] = p;
	TaskList.push_back(p);
	p->start();

}

void taskman::popTask()
{
	auto p = TaskList.back();
	TaskList.pop_back();
	TaskMap.erase(p->key);
	p->stop();
	delete p;
	delete a.back();
	a.pop_back();
	
}

void taskman::callback(int key,int msg)
{
	if (TaskMap.count(key))
	{
		TaskMap[key]->callback(msg);
	}
	else
	{
		printf("Invalid key : %d", key);
	}


}