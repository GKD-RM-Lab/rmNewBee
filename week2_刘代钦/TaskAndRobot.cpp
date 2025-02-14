#include "TaskAndRobot.h"
#include <bits/stdc++.h>
using namespace std;

Task::Task(int id,string des){
    task_id=id;
    task_des=des;
    task_state="��ִ��";
}

void Task::execute(){
    task_state="��ִ��";
}

Robot::Robot(string name){
    robot_name=name;
    robot_Task.clear();
}

Robot::~Robot(){
    int judge=1;
    for (auto i : robot_Task)
    {
        if(i.get_state()!="��ִ��"){
            cout<<"δִ������ID: "<<i.get_id()<<", ����: "<<i.get_des()<<endl;
            judge=0;
        }
    }
    if(judge){
        cout<<"������ȫ��ִ��";
    }
    cout<<endl;
}

void Robot::add_task(int id,string des){
    Task index_rob(id,des);
    robot_Task.push_back(index_rob);
}

void Robot::exeTask_R(){
    for (size_t k=0;k<robot_Task.size();k++)
    {
        robot_Task[k].execute();
    }
}

void Robot::show(){
    for (auto j : robot_Task)
    {
        cout<<"����ID: "<<j.get_id()<<", ����: "<<j.get_des()<<", ״̬: "<<j.get_state()<<endl;
    }
    cout<<endl;
}