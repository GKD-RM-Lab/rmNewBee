#include <iostream>
#include "task.hpp"

task::task()
:task_ID(0), task_priority(0), task_distription(""), task_status("待执行"){}

task::task(int id, std::string distription, int priority)
:task_ID(id), task_distription(distription), task_priority(priority), task_status("待执行"){}

void task::task_execute()
{
    task_status = "已执行";
    std::cout << "任务：" << task_ID << " 已执行" << std::endl;
}

void task::task_show() const
{
    std::cout << "任务ID：" << task_ID << "，描述：" << 
    task_distription << "，状态：" << task_status << "，优先级：" 
    << task_priority <<std::endl;
}

void task::unexecute_show() const
{
    std::cout << "未执行任务ID：" << task_ID << "，描述：" 
    << task_distription << "，优先级：" << task_priority <<std::endl;
}

bool task::operator<(const task& obj) const
{
    return this->task_priority < obj.task_priority;
}