#include <iostream>
#include <string>
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
            obj.add_robot(robot_name);
        }
        else if (command == "添加任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            Robot* robot_ptr = obj.interrogate_robot(robot_name);
            if (robot_ptr)
            {
                std::string task_distription;
                int task_ID;
                std::cin >> task_ID >> task_distription;
                robot_ptr->add_task(task_ID, task_distription);
            }
        }
        else if (command == "撤销任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            Robot* robot_ptr = obj.interrogate_robot(robot_name);
            if (robot_ptr)
                robot_ptr->quash_task();
        }
        else if (command == "执行任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            Robot* robot_ptr = obj.interrogate_robot(robot_name);
            if (robot_ptr)
                robot_ptr->execute_task();
        }
        else if (command == "删除机器人")
        {
            std::string robot_name;
            std::cin >> robot_name;
            obj.delete_robot(robot_name);
        }
        else if (command == "查询任务")
        {
            std::string robot_name;
            std::cin >> robot_name;
            Robot* robot_ptr = obj.interrogate_robot(robot_name);
            if (robot_ptr)
                robot_ptr->show_task();
        }
        else if (command == "获取机器人名称列表")
        {
            auto name_list = obj.get_list();
            for (const auto& name : name_list)
                std::cout << name << std::endl;
        }
        else if (command == "退出")
            break;
        else
            std::cout << "输入错误" << std::endl;
    }
    
    return 0;
}