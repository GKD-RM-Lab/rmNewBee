#pragma once
#include"task.h"
#include<string>
#include<set>
using namespace std;
class Robot
{
public:
    Robot();
    Robot(string name);
    void AddTask(int ID, string Describe,int Priority);
    void ExeTask();
    void ShowTask();
    void CanTask();
    ~Robot();
    string RobotName;
    set<task>TaskList;
};
