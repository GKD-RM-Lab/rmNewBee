#include <bits/stdc++.h>
#include "TaskAndRobot.h"
// #include "TaskAndRobot.cpp"
using namespace std;

int main(){
    queue<Robot>rob_queue;
    while (1)//���ѭ���Ȼ�ȡ�����˱��
    {   
        cout<<"���������������:";
        string rob_name;
        cin>>rob_name;   
        Robot buffer_rob(rob_name);
        while (1)//�ڲ�ѭ����Ӧÿ�������������嵥
        {
            fflush(stdin);
            cout<<"����������(���/ִ��/��ʾ/�˳�): ";
            string user_input;
            cin>>user_input;
            if(user_input=="���"){
                // cout<<"����������id����������: ";
                int buffer_id;
                string buffer_des;
                cin>>buffer_id>>buffer_des;
                buffer_rob.add_task(buffer_id,buffer_des);
            }
            else if(user_input=="ִ��"){
                buffer_rob.exeTask_R();
            }
            else if(user_input=="��ʾ"){
                buffer_rob.show();
            }
            else if(user_input=="�˳�"){
                rob_queue.push(buffer_rob);
                buffer_rob.~Robot();
                break;
            }
            else{
                cout<<"��������Ч����\n";
            }
        }
    cout<<"�ѽ�����"<<rob_name<<"������\n"<<endl;
   
    cout<<"�Ƿ��˳���ϵͳ(���롰�ǡ����˳�): ";
    string input;
    cin>>input;
    if(input=="��"){
        break;
    }
    cout<<endl;
    }
    return 0;
}
