#include <bits/stdc++.h>
#include "TaskAndRobot.h"
// #include "TaskAndRobot.cpp"
using namespace std;

int main(){
    TaskScheduler task_schedule;
    cout<<"�����������¿�������:"<<endl<<
    "-��ӻ�����"<<endl<<"-�������"<<endl<<"-��������(��ɾ�����ȼ���С������)"<<
    endl<<"-ִ������"<<endl<<"-ɾ��������"<<endl<<"-��ѯ����"<<
    endl<<"-��ȡ�����������б�"<<endl<<"-�˳�����"<<endl;
    cout<<"����������Ҫִ�е�����:";

    while (1)//�Ȼ�ȡ�û�ָ��
    {   
        cout<<"����������Ҫִ�е�����:";
        string order;/*�û����������*/
        cin>>order;   
        // Robot* buffer_rob=new Robot(rob_name);
        if(order=="��ӻ�����"){
            cout<<"--����������:";
            string rob_name;
            cin>>rob_name;
            Robot buffer_rob(rob_name);
            task_schedule.add_rob(buffer_rob);
            // Robot* buffer_rob=new Robot(rob_name);
            // task_schedule.add_rob(*buffer_rob);
            // delete buffer_rob;
            // buffer_rob==nullptr;
        }
        else if(order=="�������"){
            cout<<"--������������� ����ID �������� �������ȼ�: "<<endl;
            string addTask_name;
            int task_id,task_priority;
            string task_des;
            cin>>addTask_name>>task_id>>task_des>>task_priority;
            Robot* Rob_addTask=task_schedule.search_rob(addTask_name);
            if(Rob_addTask!=nullptr)
            {
                Rob_addTask->add_task(task_id,task_des,task_priority);
            }
            else 
                continue;
        }
        else if(order=="��������"){
            cout<<"--����������:";
            string Name;
            cin>>Name;
            Robot* Rob_revoke=task_schedule.search_rob(Name);
            if(Rob_revoke!=nullptr)
            {
                Rob_revoke->revoke();
                Rob_revoke->show();
            }
            else 
                continue;
        }
        else if(order=="ִ������"){
            cout<<"--����������:";
            string exe_robName;
            cin>>exe_robName;
            Robot* Rob_exe=task_schedule.search_rob(exe_robName);
            if(Rob_exe!=nullptr)
            {
                Rob_exe->exeTask_R();
                Rob_exe->show();
            }
            else 
                continue;
        }
        else if(order=="ɾ��������"){
            cout<<"--����������:";
            string delete_robName;
            cin>>delete_robName;
            Robot* Rob_delete=task_schedule.search_rob(delete_robName);
            if(Rob_delete!=nullptr)
            {
                task_schedule.delete_rob(delete_robName);
                Rob_delete->show();
            }
            else 
                continue;
        }
        else if(order=="��ѯ����"){
            cout<<"--����������:";
            string search_robName;
            cin>>search_robName;
            Robot* Rob_search=task_schedule.search_rob(search_robName);
            if(Rob_search!=nullptr)
            {
                Rob_search->show();
            }
            else 
                continue;
        }
        else if(order=="��ȡ�����������б�"){
            task_schedule.show_all();
        }
        else if(order=="�˳�����"){
            break;
        }
        else
            cerr<<"*�������ʹ�õ�����*"<<endl;
    }
    
    return 0;
}
