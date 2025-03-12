#pragma once

#include"task.h"
#include<vector>
#include<thread>
#include<map>
#include<atomic>
using namespace std;

class taskman
{
public:
	taskman() {};
	~taskman() {};
	void monitor();
	void run();
	void addTask(int key ,int kind);
	void popTask();
	void callback(int key, int msg);
private:
	atomic<int> Out;
	map<int,taskBase*>TaskMap;
	vector<taskBase*>TaskList;
	vector<atomic<int>*>a;
	vector<taskBase*>task;
	thread handler;



};