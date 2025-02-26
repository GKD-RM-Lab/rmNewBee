#include"task1.h"
#include<string>
task::task(int ID, string Describe)
{
    this->TaskID = ID;
    this->TaskDescribe = Describe;
    this->TaskState = "Non_execution";
}
task::task()
{
    this->TaskID = 0;
    this->TaskDescribe = "";
    this->TaskState = "";
}
void task::ExecuteTask()
{
    this->TaskState = "Executed";
}

