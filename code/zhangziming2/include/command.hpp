#pragma once
#include "TaskScheduler.hpp"

void command_add_robot(TaskScheduler& obj, std::string robot_name);
void command_add_task(TaskScheduler& obj, std::string robot_name, int task_ID, std::string task_distription, int priority);
void command_quash_task(TaskScheduler& obj, std::string robot_name);
void command_execute_task(TaskScheduler& obj, std::string robot_name);
void command_delete_robot(TaskScheduler& obj, std::string robot_name);
void command_interrogate_task(TaskScheduler& obj, std::string robot_name);
void command_get_list(const TaskScheduler& obj);