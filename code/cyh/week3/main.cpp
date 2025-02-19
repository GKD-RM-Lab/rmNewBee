#include <iostream>
#include "robot.hpp"
#include "taskscheduler.hpp"

using namespace std;

int main(){
    cout << "������ָ��" << endl;
    TaskScheduler taskscheduler;
    
    while(1){
        string command;
        cin >> command;
        string robotname;
        if(command == "��ӻ�����"){           
            cin >> robotname;
            taskscheduler.addRobot(robotname);
        }else if(command == "�������"){
            int id;
            string description;
            int importance;
            cin >> robotname >> id >> description >> importance;
            Robot(robotname).addTask(id, description, importance);
        }else if(command == "��������"){
            cin >> robotname;
            Robot(robotname).deleteTask();
        }else if(command == "ִ������"){
            cin >> robotname;
            Robot(robotname).executeTasks();
        }else if(command == "ɾ��������"){
            cin >> robotname;
            taskscheduler.deleteRobot(robotname);
        }else if(command == "��ѯ����"){
            cin >> robotname;
            Robot(robotname).displayTasks();
        }else if(command == "��ȡ�����������б�"){
            taskscheduler.getRobotsName();
        }else if(command == "�˳�"){
            cout << "�˳�" << endl;
            return 0;
        }else{
            cout << "��Ч(δ֪)������" << endl;
            continue;
        }
    }
    cout << "����" << endl;

    return 0;
}