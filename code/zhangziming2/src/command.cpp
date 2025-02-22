#include "command.hpp"
#include "TaskScheduler.hpp"

void command_add_robot(TaskScheduler& obj, std::string robot_name)
{
    obj.add_robot(robot_name);
}

void command_add_task(TaskScheduler& obj, std::string robot_name, int task_ID, std::string task_distription, int priority)
{
    Robot* temp = obj.interrogate_robot(robot_name);

    if (temp)
        temp->add_task(task_ID, task_distription, priority);
}

void command_quash_task(TaskScheduler& obj, std::string robot_name)
{
    Robot* temp = obj.interrogate_robot(robot_name);

    if (temp)
        temp->quash_task();
}

void command_execute_task(TaskScheduler& obj, std::string robot_name)
{
    Robot* temp = obj.interrogate_robot(robot_name);

    if (temp)
        temp->execute_task();
    
}

void command_delete_robot(TaskScheduler& obj, std::string robot_name)
{
    obj.delete_robot(robot_name);
}

void command_interrogate_task(TaskScheduler& obj, std::string robot_name)
{
    obj.interrogate_robot(robot_name)->show_task();

}

void command_get_list(const TaskScheduler& obj)
{
    std::vector<std::string> list = obj.get_list();

    for(std::string name : list)
        std::cout << name << std::endl;
}
