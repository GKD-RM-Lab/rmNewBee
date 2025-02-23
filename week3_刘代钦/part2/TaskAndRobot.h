#ifndef TASK_AND_ROBOT_H
#define TASK_AND_ROBOT_H

#include <bits/stdc++.h>
using namespace std;

class Task{
private:
    int task_id;
    string task_des;
    string task_state;
    int task_priority;
public:
    Task(int id,string des,int priority);
    //void T_initialize(int id,string des);//��ʼ������id�Լ���������
    bool operator<(const Task& other)const{
        return task_priority<other.task_priority;
    }
    void execute();//ִ������
    string get_state()const{return task_state;}//��ȡ����״̬
    string get_des()const{return task_des;}//��ȡ��������
    int get_id()const{return task_id;}//��ȡ����id
    int get_priority()const{return task_priority;}//��ȡ�������ȼ�
};

class Robot{
private:
    string robot_name;
    set<Task>robot_Task;
public:
    Robot(const string name);
    Robot(){};
    //void R_initialize(string name);//��ʼ�������˱�Ų�����������嵥
    ~Robot();
    //void undone_task();//�˳�����ʱ���δ�������
    void add_task(int id,string des,int priority);//�������
    void exeTask_R();//ִ�ж��������ȼ�����һ������
    void show();//��ʾ�����嵥�������������Ϣ
    string get_robName(){return robot_name;}//��ȡ����������
    void revoke();//ɾ�����ȼ���С������
};

class TaskScheduler{
private:
    map<string,Robot>rob_map;
    vector<string>rob_Name;
public:
    void add_rob(Robot rob);
    void delete_rob(const string Name);
    Robot* search_rob(const string Name);
    void show_all();
};
#endif //TASK_AND_ROBOT_H