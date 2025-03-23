#pragma once

#ifndef TASK_H
#define TASK_H
#include <iostream>
class Task
{
private:
int task_ID;
std::string task_desc;
std::string task_statue;
public:
~Task();
Task();
Task(int ID,std::string desc);
void do_task();
int get_ID() const;
std::string get_desc() const;
std::string get_statue() const;
};
#endif