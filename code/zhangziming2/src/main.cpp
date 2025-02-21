#include <iostream>
#include <string>
#include "Robot.hpp"
#include "task.hpp"
#include "command.hpp"
#include "TaskScheduler.hpp"

int main()
{
    TaskScheduler obj;
    while(true)
    {
        std::cout << "输入命令：";
        std::string command;
        std::cin >> command;

        if (command == "添加机器人")
        {
            std::string robot_name;
            std::cin >> robot_name;
            command_add_robot(obj, robot_name);
        }
        else if (command == "添加任务")
        {
            std::string task_distription, robot_name;
            int task_ID, task_priority;
            std::cin >> robot_name >> task_ID >> task_distription >> task_priority;
            command_add_task(obj, robot_name, task_ID, task_distription, task_priority);
        }
        else if (command == "撤销任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            command_quash_task(obj, robot_name);
        }
        else if (command == "执行任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            command_execute_task(obj, robot_name);
        }
        else if (command == "删除机器人")
        {
            std::string robot_name;
            std::cin >> robot_name;
            command_delete_robot(obj, robot_name);
        }
        else if (command == "查询任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            command_interrogate_task(obj, robot_name);
        }
        else if (command == "获取机器人名称列表")
            command_get_list(obj);
        else if (command == "退出")
            break;
        else
            std::cout << "输入错误" << std::endl;
    }
    
    return 0;
}