#include "Task.h"
Task::~Task()
{
    //析构函数
}

Task::Task()
{
    task_ID=0;
    task_priority=0;
    task_statue="待执行";
    task_desc="";
}

Task::Task(int ID,std::string desc,int priority)
{
    task_ID=ID;
    task_desc=desc;
    task_priority=priority;
    task_statue="待执行";
}

void Task::task_done()
{
    task_statue="已执行";
}

std::string Task::get_desc() const
{
    return task_desc;
}

int Task::get_ID() const
{
    return task_ID;
}

int Task::get_priority() const
{
    return task_priority;
}

std::string Task::get_statues() const
{
    return task_statue;
}

bool Task::operator<(const Task &other) const//重载“<”运算符
{
    if(this->task_priority>other.get_priority())//任务优先级的核心
    {
        return true;
    }
    else
        return false;
    
}