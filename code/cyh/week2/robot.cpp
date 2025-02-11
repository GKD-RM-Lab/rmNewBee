#include "robot.hpp"
#include <iostream>


Robot::Robot(std::string name){
    Robotname = name;
}

Robot::~Robot(){
    for(int i = 0;  i < Robot::tasks.size(); i++){
        if(tasks[i].getTaskStatus() == "δִ��")
        {
            std::cout << "δ�������ID: " << tasks[i].getTaskID() << " ,����: " << tasks[i].getTaskDescription() << std::endl;
        }
    }    
}

void Robot::addTask(int id, std::string description){
    tasks.push_back(Task(id, description));
}

void Robot::executeTasks(){
    for(int i = 0;  i < tasks.size(); i++){
            tasks[i].execute();
    }
}

void Robot::displayTasks(){
    for(int i = 0;  i < tasks.size(); i++){
        std::cout << "����ID: " << tasks[i].getTaskID() << " ,����: " << tasks[i].getTaskDescription() << " ,״̬: " << tasks[i].getTaskStatus() << std::endl;
    }
}

