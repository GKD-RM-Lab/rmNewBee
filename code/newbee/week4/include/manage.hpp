#pragma once
#include"task.hpp"
#include<iostream>
#include<map>
#include<thread>
#include<atomic>
#include<vector>
class manage{
public:
    std::thread out_thread;
    std::atomic<int> out=0;
    std::map<int,task*> tasks;
    std::vector<std::atomic<int>*> a;
    std::vector<task* > task_list;
    void checkout();
    void run();
    manage(){}
};
