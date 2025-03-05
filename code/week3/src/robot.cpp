#include "robot.h"
#include <iostream>

Robot::Robot(std::string robotName) : name(robotName) {
    // 初始化机器人名称并清空任务队列
}

Robot::~Robot() {
    // 输出所有未完成的任务信息
    std::cout << "List of unexecuted tasks:" << std::endl;
    for (int i = 0; i < taskQueue.size(); ++i) {
        if (!taskQueue[i].isExecuted()) {
            std::cout << "id: " << taskQueue[i].getID()
                      << ", description: " << taskQueue[i].getDescription() << std::endl;
        }
    }
}

void Robot::addTask(int id, const std::string& desc) {
    taskQueue.emplace_back(id, desc);
}

void Robot::executeTasks() {
    for (int i = 0; i < taskQueue.size(); ++i) {
        taskQueue[i].execute(); // 执行任务
    }
}

void Robot::displayTasks() {
    std::cout << std::boolalpha << std::fixed;
    for (int i = 0; i < taskQueue.size(); ++i) {
        std::cout << "id: " << taskQueue[i].getID()
                  << ", description: " << taskQueue[i].getDescription()
                  << ", executed: " << taskQueue[i].isExecuted() << std::endl;
    }
}

void Robot::undoTask() {
    taskQueue.pop_back();
}
