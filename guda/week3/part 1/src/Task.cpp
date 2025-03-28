#include "Task.h"
#include <iostream>

Task::Task()
{
    task_ID=0;
    task_desc="";
    task_statue="待执行";
}

Task::Task(int ID,std::string desc)
{
    task_ID=ID;
    task_desc=desc;
    task_statue="待执行";
}

Task::~Task()
{
    //析构函数
}

void Task::do_task()
{
    task_statue="已执行";
}

int Task::get_ID() const
{
    return task_ID;
}

std::string Task::get_desc() const
{
    return task_desc;
}

std::string Task::get_statue() const
{
    return task_statue;
}