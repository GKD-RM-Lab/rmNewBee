#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Robot.hpp"

class TaskScheduler
{
private:
    std::map<std::string, Robot> robot_list;
public:
    void add_robot(std::string robot_name);
    void delete_robot(std::string robot_name);
    Robot* interrogate_robot(std::string robot_name);
    std::vector<std::string> get_list();
};