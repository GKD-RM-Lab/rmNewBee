#include<iostream>
#include "robot.hpp"
robot::robot(std::string name):NAME(name){}
robot::~robot(){
    for(auto it=tasks.begin();it!=tasks.end();it++){
        const task& t=*it;
    if(t.getstatus()=="待执行"){
        std::cout<<"未执行任务ID: "<<t.getID()<<", 描述："<<t.getdescription()<<std::endl;
    }
    }
}
void robot::addtask(int id, const std::string& description,int x){
    task newtask(id,description,x);
    tasks.insert(newtask);
}
void robot::executetasks(){
    auto it=tasks.end();
    it--;
    it->execute();
    }
void robot::displaytasks(){
    for(auto it=tasks.begin();it!=tasks.end();it++){
        const task& t=*it;
        std::cout<<"任务ID:"<<t.getID()<<", 描述："<<t.getdescription()<<", 状态："<<t.getstatus()<<std::endl;
    }
}

void robot::remove(){
    auto it=tasks.begin();
    tasks.erase(it);
}