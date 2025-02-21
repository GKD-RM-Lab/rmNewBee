#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include "Robot.hpp"

class TaskScheduler
{
private:
    std::map<std::string, Robot> robot_list;
public:
    void add_robot(std::string robot_name);
    void delete_robot(std::string robot_name);
    bool is_end(std::map<std::string, Robot>::const_iterator it) const;
    std::map<std::string, Robot>::iterator interrogate_robot(std::string robot_name);
    std::vector<std::string>& get_list() const;
};