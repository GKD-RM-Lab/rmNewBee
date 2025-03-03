#include<iostream>
#include "robot.hpp"
robot::robot(std::string name):NAME(name){}
robot::~robot(){
    for(int i=0;i<tasks.size();i++){
    if(tasks[i].getstatus()=="待执行"){
        std::cout<<"未执行任务ID: "<<tasks[i].getID()<<", 描述："<<tasks[i].getdescription()<<std::endl;
    }
    }
}
void robot::addtask(int id, const std::string& description){
    tasks.emplace_back(id,description);
}
void robot::executetasks(){
    for(int i=0;i<tasks.size();i++){
    tasks[i].execute();
    }
}

void robot::displaytasks(){
    for(int i=0;i<tasks.size();i++){
        std::cout<<"任务ID:"<<tasks[i].getID()<<", 描述："<<tasks[i].getdescription()<<", 状态："<<tasks[i].getstatus()<<std::endl;
    }
}

void robot::remove(){
    tasks.pop_back();
}