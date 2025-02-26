#include"task.h"
#include<string>
task::task(int ID, string Describe,int Priority)
{
    this->TaskID = ID;
    this->TaskDescribe = Describe;
    this->TaskState = "Non_execution";
    this->TaskPriority = Priority;
}
task::task()
{
    this->TaskID = 0;
    this->TaskDescribe = "";
    this->TaskState = "";
    this->TaskPriority = 0;
}
void task::ExecuteTask()const{
    this->TaskState = "Executed";
}
bool task::operator<(const task &p)const{
    return this->TaskPriority > p.TaskPriority;
}

