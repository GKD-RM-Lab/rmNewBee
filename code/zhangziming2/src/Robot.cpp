#include <iostream>
#include <string>
#include <vector>
#include "task.hpp"
#include "Robot.hpp"

Robot::Robot(std::string name)
:robot_name(name) {}

Robot::~Robot()
{
    std::cout << "机器人" << robot_name << "：" << std::endl;
    if (unexecute_list.empty())
        std::cout << "无未执行任务" << std::endl;
    else
        for(auto it = unexecute_list.rbegin(); it != unexecute_list.rend(); ++it)
            (*it).task_show();
}

void Robot::add_task(int id, std::string distription, int priority)
{
    manager.emplace(id, distription, priority);
    unexecute_list.emplace(id, distription, priority);
}

void Robot::execute_task()
{
    if (unexecute_list.empty())
        std::cout << "无可执行内容" << std::endl;
    else
    {
        task temp = *unexecute_list.rbegin();
        unexecute_list.erase(temp);
        manager.erase(temp);
        temp.task_execute();
        manager.emplace(temp);
    }
}

void Robot::show_task() const
{
    if (manager.empty())
        std::cout << "无任务" << std::endl;
    else
        for(auto it = manager.rbegin(); it != manager.rend(); ++it)
            (*it).task_show();
}

void Robot::quash_task()
{
    if (unexecute_list.empty())
        std::cout << "无可撤销任务" << std::endl;
    else
    {
        manager.erase(*(unexecute_list.begin()));
        unexecute_list.erase(unexecute_list.begin());
        std::cout << "任务撤销" << std::endl;
    } 
}