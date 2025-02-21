#pragma once
#include<string>

class task
{
private:
    int task_ID;
    int task_priority;
    std::string task_distription;
    std::string task_status;
public:
    task();
    task(int id, std::string distription, int priority);
    void task_execute();
    void task_show() const;
    void unexecute_show() const;
    bool operator<(const task& obj) const;
};