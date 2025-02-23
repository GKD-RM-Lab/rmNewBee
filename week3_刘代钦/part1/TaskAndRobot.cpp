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

Robot::Robot(const string name){
    robot_name=name;
    robot_Task.clear();
}

Robot::~Robot(){
    int judge=-1;
    if(robot_Task.size()==0){
        return;
    }
    for (auto i : robot_Task)
    {
        if(i.get_state()!="��ִ��"){
            cout<<"����δȫ��ִ�л���������: "<<robot_name<<"δִ������ID: "<<i.get_id()<<", ����: "<<i.get_des()<<endl;
            judge=0;
        }
        else if(i.get_state()=="��ִ��"){
            judge=1;
        }
    }
    if(judge){
        cout<<"������"<<robot_name<<"������ȫ��ִ��";
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

void TaskScheduler::delete_rob(string Name){
    auto p=rob_map.find(Name);
    if(p!=rob_map.end()){
        rob_map.erase(p);
        cout<<"��ɾ������������Ϊ  "<<Name<<"  �Ļ�����"<<endl;
    }
    else{
        cerr<<"δ���ҵ��û�����\n"<<endl;
    }
}

Robot* TaskScheduler::search_rob(string Name){
    auto p=rob_map.find(Name);
    if(p!=rob_map.end()){
        // (p->second).show();
        cout<<endl;
        return &(p->second);
    }
    else{
        cerr<<"δ���ҵ��û�����\n"<<endl;
        return nullptr;
    }
}

void TaskScheduler::show_all(){
    for(auto p=rob_map.begin();p!=rob_map.end();p++){
        rob_Name.push_back(p->first);
    }
    cout<<endl<<"�����������б�:"<<endl;
    for (auto i = rob_Name.begin(); i!=rob_Name.end(); i++)
    {
        cout<<*i<<endl;
    }
    cout<<endl;
}

void TaskScheduler::add_rob(Robot rob){
    if(rob_map.count(rob.get_robName())){
        cout<<"���л�����: "<<rob.get_robName()<<endl;
    }
    else{
        rob_map[rob.get_robName()]=rob;
    }
}