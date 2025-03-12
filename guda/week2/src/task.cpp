//task.cpp
#include "task.h"


task::task(int id,std::string desc){
    taskID=id;
    task_description=desc;
    task_status="待执行";
}

task::~task() {
    // 析构函数
}

void task::task_done(){
    task_status="已执行";
}

int task::getID() const
{
    return taskID;
}

std::string task::get_description() const
{
    return task_description;
}

std::string task::get_status() const
{
    return task_status;
}