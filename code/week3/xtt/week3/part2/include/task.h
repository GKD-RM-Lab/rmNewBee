#pragma once
#include<string>
using namespace std;
class task
{
public:
    task(int ID, string Describe, int Priority);
    task();
    void ExecuteTask() const;
    bool operator<(const task &p)const;
    int TaskID;
    string TaskDescribe;
    mutable string TaskState;
    int TaskPriority;
};