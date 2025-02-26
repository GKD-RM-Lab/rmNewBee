#include<string>
#include<iostream>
using namespace std;
#include"TaskScheduler1.h"


int main()
{
    string command;
    string RobotID;
    TaskScheduler RobotTS;
    while (1)
    {
        cout << "Please rnter the command(Add_Robot,Add_Task,Can_Task,Exe_Task,Del_Robot,Inq_Task,Get_Robot_Name_List)" << endl;
        cin >> command;
        if (command == "quit") { break; }
        else if (command == "Add_Robot")
        {
            string robotname;
            cin >> robotname;
            Robot newrobot(robotname);
            RobotTS.AddRobot(newrobot);
        }
        else if (command == "Add_Task")
        {
            int TaskID;
            string TaskDS;
            cin>> RobotID;
            cin>> TaskID;
            cin>>TaskDS;
            RobotTS.RobotList[RobotID].AddTask(TaskID, TaskDS);
        }
        else if (command == "Can_Task")
        {
            cin >> RobotID;
            RobotTS.RobotList[RobotID].CanTask();
        }
        else if (command == "Exe_Task")
        {
            cin>>RobotID;
            RobotTS.RobotList[RobotID].ExeTask();
        }
        else if (command == "Del_Robot")
        {
            cin>> RobotID;
            RobotTS.DelRobot(RobotID);
        }
        else if (command == "Inq_Task")
        {
            cin >> RobotID;
            RobotTS.InquireRobot(RobotID);
        }
        else if (command == "Get_Robot_Name_List")
        {
            RobotTS.ShowNameList();
        }
        else
        {
            cout << "Invalid command,please re-enter" << endl;
            continue;
        }
    }
    return 0;
}