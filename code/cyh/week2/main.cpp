#include <iostream>
#include "robot.hpp"

using namespace std;

int main(){
    string robotname;
    cout << "���������������" << endl;
    cin >> robotname;
    Robot robot(robotname);

    cout << "������ָ��" << endl;

    while(1){
        string command;
        cin >> command;
        if(command == "�˳�"){
            break;
        }else if(command == "��ʾ"){
            robot.displayTasks();
        }else if(command == "ִ��"){
            robot.executeTasks();
        }else if(command == "���"){
            int id;
            string description;
            cin >> id >> description;
            robot.addTask(id, description);
        }else{
            cout << "����ָ��" << endl;
        }
    }

    cout << "����" << endl;

    return 0;
}