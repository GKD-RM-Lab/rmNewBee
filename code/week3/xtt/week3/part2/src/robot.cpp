#include"robot.h"
#include<iostream>
#include<string>
using namespace std;
Robot::Robot(){}
Robot::Robot(string name)
{
    this->RobotName = name;
 }
void Robot::AddTask(int ID, string Describe,int Priority)
{
    TaskList.insert(task(ID, Describe, Priority));
}
void Robot::ExeTask()
{
    set<task>::iterator it = TaskList.begin(); 
    while (it->TaskState != "non_execution") { it++; }
    it->ExecuteTask();
    
}
void Robot::ShowTask()
{
    for (set<task>::iterator it = TaskList.begin(); it != TaskList.end(); it++)
    {
        cout << "Task_ID:" << it->TaskID << ", Describe:" << it->TaskDescribe << ",State:" << it->TaskState<<",Priority:" <<it->TaskPriority<< endl;
    }
}
void Robot::CanTask()
{
    set<task>::iterator it = --TaskList.end();
    TaskList.erase(it);
}
Robot::~Robot()
{
    for (set<task>::iterator it = TaskList.begin(); it != TaskList.end(); it++)
    {
        if ( it->TaskState== "non_execution")
        {
            cout <<"Name:"<<this->RobotName<< "UnfinishedTask_ID:" << it->TaskID << ",Describe:" <<it->TaskDescribe << endl;
        }
    }
}