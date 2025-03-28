#ifndef TASK_H
#define TASK_H
#include<iostream>
#include<set>
#include<string>
class Task
{
private:
int task_ID;
std::string task_desc;
std::string task_statue;
int task_priority;
public:
~Task();
Task();
Task(int ID,std::string desc,int priority);
void task_done();
int get_ID() const;
std::string get_desc() const;
std::string get_statues() const;
int get_priority() const;
bool operator <(const Task &other) const;
};
#endif