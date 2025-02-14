#ifndef TASK_AND_ROBOT_H
#define TASK_AND_ROBOT_H

#include <bits/stdc++.h>
using namespace std;

class Task{
private:
    int task_id;
    string task_des;
    string task_state;
public:
    Task(int id,string des);
    //void T_initialize(int id,string des);//��ʼ������id�Լ���������
    void execute();//ִ������
    string get_state()const{return task_state;}//��ȡ����״̬
    string get_des()const{return task_des;}//��ȡ��������
    int get_id()const{return task_id;}//��ȡ����id
};

class Robot{
private:
    string robot_name;
    vector<Task>robot_Task;
public:
    Robot(string name);
    //void R_initialize(string name);//��ʼ�������˱�Ų�����������嵥
    ~Robot();
    //void undone_task();//�˳�����ʱ���δ�������
    void add_task(int id,string des);//�������
    void exeTask_R();//ִ�ж�������������
    void show();//��ʾ�����嵥�������������Ϣ
    string get_robName(){return robot_name;}
};

#endif //TASK_AND_ROBOT_H