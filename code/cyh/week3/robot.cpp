#include "robot.hpp"
#include <iostream>


Robot::Robot(std::string name){
    robotname = name;
}


void Robot::addTask(int id, std::string description, int importance){
    tasks.insert(Task(id, description, importance));
}

void Robot::executeTasks()  {
    if (!tasks.empty()) {
        auto it = tasks.rbegin();
        it->execute();
    }
}


void Robot::displayTasks()  {
    if (tasks.empty()) {
        std::cout << "任务列表为" << std::endl;
        return;
    }
    for(auto it = tasks.rbegin(); it != tasks.rend(); it++) {
        std::cout << "任务ID: " << it->getTaskID() << ", 描述: " << it->getTaskDescription() << ", 状态: " << it->getTaskStatus() << std::endl;
    }
}

void Robot::deleteTask(){
   if(!tasks.empty()){
    auto it = tasks.begin();
    tasks.erase(*it);
   }
}

