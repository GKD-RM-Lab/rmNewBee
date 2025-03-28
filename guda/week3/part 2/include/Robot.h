#pragma once

#ifndef ROBOT_H
#define ROBOT_H
#include "task.h"
#include <iostream>
#include <set>
class Robot 
{
private:
    std::string robot_name;
    std::set <Task> queue;
public:
    ~Robot();
    Robot(std::string name);
    void add_task(int ID,std::string desc,int priority);
    void do_task();
    void indicate_task() const;
    void delete_task();   
};
#endif
