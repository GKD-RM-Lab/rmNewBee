#ifndef TASK_H
#define TASK_H
#include<string>
using namespace std;
class task
{
public:
    task(int ID, string Describe);
    task();
    void ExecuteTask();
    int TaskID;
    string TaskDescribe;
    string TaskState;
};
#endif