#pragma once

#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H
#include "Robot.h"
#include <map>
#include <vector>
#include "Task.h"
class TaskScheduler
{
private:
std::map<std::string,Robot *> robot_list;
public:
void add_Robot(const std::string &name);
void delete_robot(const std::string &name);
Robot* find_robot(const std::string &name);
std::vector<std::string> get_robotlist(); 
};

#endif