#include <iostream>
#include <string>
#include <vector>
#include "task.hpp"
#include "Robot.hpp"

Robot::Robot(std::string name)
    :robot_name(name), task_count(0), execute_count(0) {}

Robot::~Robot()
{
    for(int count = execute_count; count < task_count; count++)
        manager[count].unexecute_show();
}

void Robot::add_task(int id, std::string distription)
{
    manager.push_back(task());
    manager[task_count].task_set(id, distription);
    task_count++;
}

void Robot::execute_task()
{
    for(; execute_count < task_count; execute_count++)
        manager[execute_count].task_execute();
}

void Robot::show_task()
{
    for(int count = 0; count < task_count; count++)
        manager[count].execute_show();
        
}