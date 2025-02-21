#pragma once
#include <vector>
#include <string>
#include <set>
#include "task.hpp"

class Robot
{
private:
    std::string robot_name;
    std::set<task> manager;
    std::set<task> unexecute_list;
public:
    Robot(std::string name);
    ~Robot();
    void add_task(int id, std::string distription, int priority);
    void execute_task();
    void show_task() const;
    void quash_task();
};