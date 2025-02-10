#include "robot.h"
#include <iostream>

Robot::Robot(std::string robotName) : name(robotName), taskCount(0)
{
    // 初始化机器人名称并清空任务队列
}

Robot::~Robot()
{
    // 输出所有未完成的任务信息
    for (int i = 0; i < taskCount; ++i)
    {
        if (taskQueue[i].getStatus() == "待执行")
        {
            std::cout << "未执行任务ID: " << taskQueue[i].getID()
                      << ", 描述: " << taskQueue[i].getDescription() << std::endl;
        }
    }
}

void Robot::addTask(int id, std::string desc)
{
    if (taskCount < 100)
    {
        taskQueue[taskCount++] = Task(id, desc); // 添加新任务
    }
}

void Robot::executeTasks()
{
    for (int i = 0; i < taskCount; ++i)
    {
        taskQueue[i].execute(); // 执行任务
    }
}

void Robot::displayTasks()
{
    for (int i = 0; i < taskCount; ++i)
    {
        std::cout << "任务ID: " << taskQueue[i].getID()
                  << ", 描述: " << taskQueue[i].getDescription()
                  << ", 状态: " << taskQueue[i].getStatus() << std::endl;
    }
}
