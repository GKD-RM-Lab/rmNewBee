#pragma once

#ifndef ROBOT_H
#define ROBOT_H
#include "Task.h"
#include <iostream>
#include <vector> 
class Robot
{
private:
std::string Robot_name;
std::vector <Task> queue;
public:
~Robot();
Robot(std::string name);
void add_task(int ID,std::string desc);
void task_done();
void indicate();
void delete_task();
};
#endif