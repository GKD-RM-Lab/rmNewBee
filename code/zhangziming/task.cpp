#include <iostream>
#include "task.hpp"

task::task()
    :task_ID(0), task_distription("静止"), task_status("待执行"){}

void task::task_set(int id, std::string distription)
{
    task_ID = id;
    task_distription = distription;
}

void task::task_execute()
{
    task_status = "已执行";
}

void task::execute_show()
{
    std::cout << "任务ID：" << task_ID << "，描述：" << 
    task_distription << "，状态：" << task_status << std::endl;
}

void task::unexecute_show()
{
    std::cout << "未执行任务ID：" << task_ID << "，描述：" 
    << task_distription << std::endl;
}