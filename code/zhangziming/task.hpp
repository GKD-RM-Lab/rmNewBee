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
    void task_set(int id, std::string distription);
    void task_execute();
    void execute_show();
    void unexecute_show();
};