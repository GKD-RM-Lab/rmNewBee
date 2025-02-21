#include <iostream>
#include <string>
#include <vector>
#include "task.hpp"
#include "Robot.hpp"

Robot::Robot(std::string name)
:robot_name(name), task_count(0), execute_count(0)
{
    manager.reserve(100);
}

Robot::Robot() {}

Robot::~Robot()
{
    std::cout << "机器人：" << robot_name << std::endl; 
    if (execute_count < task_count)
        for(int count = execute_count; count < task_count; count++)
            manager[count].unexecute_show();
    else
        std::cout << "无未执行任务" << std::endl;
}

void Robot::add_task(int id, std::string distription)
{
    manager.emplace_back(id, distription);
    task_count++;
}

void Robot::execute_task()
{
    for(; execute_count < task_count; execute_count++)
        manager[execute_count].task_execute();
}

void Robot::show_task() const
{
    if (task_count)
        for(int count = 0; count < task_count; count++)
            manager[count].task_show();
    else
        std::cout << "无任务" << std::endl;
}

void Robot::quash_task()
{
    if (execute_count < task_count)
    {
        manager.pop_back();
        std::cout << "已撤销" << std::endl;
        task_count--;
    }
    else
        std::cout << "无可撤销任务" << std::endl;
}