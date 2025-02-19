#include "robot.hpp"
#include <iostream>


Robot::Robot(std::string name){
    robotname = name;
}

Robot::~Robot(){
    for(auto task : tasks){
        if(task.getTaskStatus() == "δִ��")
        {
            std::cout << "δ�������ID: " << task.getTaskID() << ",����: " << task.getTaskDescription() << std::endl;
        }
    }    
}

void Robot::addTask(int id, std::string description, int importance){
    tasks.insert(Task(id, description, importance));
}

void Robot::executeTasks() const{
    if (!tasks.empty()) {
        auto it = tasks.rbegin();
        it->execute();
    }
}


void Robot::displayTasks() const{
    for(auto it = tasks.rbegin(); it != tasks.rend(); it--){
        
        
        std::cout << "����ID: " << it->getTaskID() << ", ����: " << it->getTaskDescription() << ", ״̬: " << it->getTaskStatus() << std::endl;
    }
}

void Robot::deleteTask(){
   if(!tasks.empty()){
    auto it = tasks.begin();
    tasks.erase(*it);
   }
}

