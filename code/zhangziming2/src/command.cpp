#include "command.hpp"
#include "TaskScheduler.hpp"

void command_add_robot(TaskScheduler& obj, std::string robot_name)
{
    obj.add_robot(robot_name);
}

void command_add_task(TaskScheduler& obj, std::string robot_name, int task_ID, std::string task_distription, int priority)
{
    auto temp = obj.interrogate_robot(robot_name);

    if (!obj.is_end(temp))
        (temp->second).add_task(task_ID, task_distription, priority);
}

void command_quash_task(TaskScheduler& obj, std::string robot_name)
{
    auto temp = obj.interrogate_robot(robot_name);

    if (!obj.is_end(temp))
        (temp->second).quash_task();
}

void command_execute_task(TaskScheduler& obj, std::string robot_name)
{
    auto temp = obj.interrogate_robot(robot_name);

    if (!obj.is_end(temp))
        (temp->second).execute_task();
    
}

void command_delete_robot(TaskScheduler& obj, std::string robot_name)
{
    obj.delete_robot(robot_name);
}

void command_interrogate_task(TaskScheduler& obj, std::string robot_name)
{
    (obj.interrogate_robot(robot_name)->second).show_task();

}

void command_get_list(const TaskScheduler& obj)
{
    std::vector<std::string> list = obj.get_list();

    for(std::string it : list)
        std::cout << it << std::endl;
}
