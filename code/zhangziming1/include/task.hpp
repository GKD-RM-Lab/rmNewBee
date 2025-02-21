#pragma once
#include<string>
class task
{
private:
    int task_ID;
    std::string task_distription;
    std::string task_status;
public:
    task();
    task(int id, std::string distription);
    void task_execute();
    void task_show() const;
    void unexecute_show() const;
};