#ifndef ROBOT_H
#define ROBOT_H
#include "task.h"
#include <iostream>
class Robot
{
private:
    std::string Robot_name;
    task quest[100];
    int taskcount;
public:
    Robot(std::string robotname);
    ~Robot();
    void add_quest(int id,std::string desc);
    void do_task();
    void indicate(); 
};

#endif