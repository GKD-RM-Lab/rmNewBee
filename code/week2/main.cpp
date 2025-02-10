#include <iostream>
#include "robot.h"
using namespace std;

int main() {
    string robotName;
    cout << "请输入机器人名称: ";
    cin >> robotName;
    
    Robot robot(robotName);
    string command;

    while (true) {
        cout << "请输入命令（添加/执行/显示/退出）: ";
        cin >> command;

        if (command == "退出") {
            break;
        } else if (command == "添加") {
            int id;
            string desc;
            cin >> id >> desc;
            robot.addTask(id, desc);
        } else if (command == "执行") {
            robot.executeTasks();
        } else if (command == "显示") {
            robot.displayTasks();
        } else {
            cout << "无效命令，请重试。" << endl;
        }
    }

    return 0;
}
