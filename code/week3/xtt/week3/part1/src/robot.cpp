#include"robot1.h"
#include<iostream>
#include<string>
using namespace std;
Robot::Robot(){}
Robot::Robot(string name)
{
    this->RobotName = name;
    TaskList.push_back(task());
    
}
void Robot::AddTask(int ID, string Describe)
{
    TaskList.push_back(task(ID, Describe));
}
void Robot::ExeTask()
{
    for (int i = 0; i < TaskList.size(); i++)
    {
        if (TaskList[i].TaskID != 0)
        {
            TaskList[i].ExecuteTask();
        }
    }
}
void Robot::ShowTask()
{
    for (int i = 0; i < TaskList.size(); i++)
    {
        if (TaskList[i].TaskID != 0)
        {
            cout << "Task_ID:" << TaskList[i].TaskID << ", Describe:" << TaskList[i].TaskDescribe << ",State:" << TaskList[i].TaskState << endl;
        }
    }
}
void Robot::CanTask()
{
    TaskList.pop_back();
}
Robot::~Robot()
{
    for (int i = 0; i < TaskList.size(); i++)
    {
        if (TaskList[i].TaskID != 0 && TaskList[i].TaskState == "non_execution")
        {
            cout <<"Name,"<<this->RobotName<< "UnfinishedTask_ID:" << TaskList[i].TaskID << ",Describe:" << TaskList[i].TaskDescribe << endl;
        }
    }
}