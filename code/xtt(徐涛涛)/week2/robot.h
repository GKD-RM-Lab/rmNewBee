#include"task.h"
#include<string>
#include<iostream>
using namespace std;
class Robot
{
public:
    Robot(string name)
    {
        this->RobotName = name;
        for (int i = 0; i < 10; i++)
        {
            this->TaskList[i] = task();
        }
    }
    void AddTask(int ID, string Describe)
    {
        this->TaskList[ID] = task(ID, Describe);
    }
    void ExeTask()
    {
        for (int i = 0; i < 10; i++)
        {
            if (TaskList[i].TaskID != 0)
            {
                TaskList[i].ExecuteTask();
            }
        }
    }
    void ShowTask()
    {
        for (int i = 0; i < 10; i++)
        {
            if (TaskList[i].TaskID != 0)
            {
                cout << "任务 ID：" << TaskList[i].TaskID << ", 描述：" << TaskList[i].TaskDescribe << "，状态：" << TaskList[i].TaskState << endl;
            }
        }
    }
    ~Robot()
    {
        for (int i = 0; i < 10; i++)
        {
            if (TaskList[i].TaskID != 0 && TaskList[i].TaskState == "未执行")
            {
                cout << "未完成任务 ID：" << TaskList[i].TaskID << "，描述：" << TaskList[i].TaskDescribe << endl;
            }
        }
    }
    string RobotName;
    task TaskList[10];
};