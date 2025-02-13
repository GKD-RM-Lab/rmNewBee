#include<iostream>
#include<string>
using namespace std;
class task
{
public:
    task(int ID, string Describe)
    {
        this->TaskID = ID;
        this->TaskDescribe = Describe;
        this->TaskState = "未执行";
    }
    task()
    {
        this->TaskID = 0;
        this->TaskDescribe = "";
        this->TaskState = "";
    }
    void ExecuteTask()
    {
        this->TaskState = "已执行";
    }
    int TaskID;
    string TaskDescribe;
    string TaskState;
};