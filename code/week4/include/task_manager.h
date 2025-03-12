#pragma once

#include "task.h"
#include <map>

class TaskManager {
    std::thread out_thread;
    std::atomic<int> out;
    std::vector<std::atomic<int> *> a;
    std::vector<TaskBase *> task_list;
    std::map<int, TaskBase *> task_map;

public:
    TaskManager() = default;

    void add_task(int key, int kind);
    void pop_task();
    void run();
    void out_check();
};