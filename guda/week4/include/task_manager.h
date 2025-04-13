#pragma once

#include "task.h"
#include <map>

using namespace std;

class TaskManager{
private:
  thread out_thread;
  atomic<int> out;
  vector<atomic<int> *> a;
  vector<TaskBase *> task_list;
  map<int,TaskBase *> task_map;

public:
    TaskManager()=default;

    void add_task(int key,int kind);
    void pop_task();
    void run();
    void out_check();


};