#pragma once
#include <vector>
#include <string>
#include "task.hpp"

class Robot
{
private:
    std::string robot_name;
    std::vector<task> manager;
    int task_count;
    int execute_count;
public:
    Robot(std::string name);
    ~Robot();
    void add_task(int id, std::string distription);
    void execute_task();
    void show_task();
};