#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <map>
#include "TaskScheduler.hpp"

void TaskScheduler::add_robot(std::string robot_name)
{
    robot_list.emplace(robot_name, robot_name); 
}

void TaskScheduler::delete_robot(std::string robot_name)
{
    if (robot_list.find(robot_name) == robot_list.end())
        std::cout << "未查询到该机器人" << std::endl;
    else
    {
        robot_list.erase(robot_name);
        std::cout << "机器人" << robot_name << "被删除" << std::endl;
    }
}

Robot* TaskScheduler::interrogate_robot(std::string robot_name)
{
    auto find = robot_list.find(robot_name);

    if (find == robot_list.end())
    {
        std::cout << "未查询到该机器人" << std::endl;
        return nullptr;
    }

    return &(find->second);
}

std::vector<std::string> TaskScheduler::get_list() const
{
    std::vector<std::string> name_list;
    name_list.reserve(10);

    if (robot_list.empty())
        std::cout << "列表为空" << std::endl;
    else
        for (const auto& name : robot_list)
            name_list.emplace_back(name.first);

    return  name_list;
}