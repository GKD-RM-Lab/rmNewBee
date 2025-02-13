#include<string>
#include<iostream>
using namespace std;
#include"robot.h"


int main()
{
    string RobotName;
    cout << "请输入机器人名称" << endl;
    cin >> RobotName;
    Robot newrobot(RobotName);
    string command;
    while (1)
    {
        cout << "请输入命令" << endl;
        cin >> command;
        if (command == "退出") { break; }
        else if (command == "添加")
        {
            int ID;
            string Description;
            cin >> ID >> Description;
            newrobot.AddTask(ID, Description);
        }
        else if (command == "显示")
        {
            newrobot.ShowTask();
        }
        else if (command == "执行")
        {
            newrobot.ExeTask();
        }
        else
        {
            cout << "无效命令，请重新输入" << endl;
            continue;
        }
    }
    return 0;
}