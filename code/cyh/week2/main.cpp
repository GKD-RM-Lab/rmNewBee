#include <iostream>
#include "robot.hpp"

using namespace std;

int main(){
    string robotname;
    cout << "请输入机器人名称" << endl;
    cin >> robotname;
    Robot robot(robotname);

    cout << "请输入指令" << endl;

    while(1){
        string command;
        cin >> command;
        if(command == "退出"){
            break;
        }else if(command == "显示"){
            robot.displayTasks();
        }else if(command == "执行"){
            robot.executeTasks();
        }else if(command == "添加"){
            int id;
            string description;
            cin >> id >> description;
            robot.addTask(id, description);
        }else{
            cout << "错误指令" << endl;
        }
    }

    cout << "结束" << endl;

    return 0;
}