#include <iostream>
#include "robot.hpp"
#include "taskscheduler.hpp"

using namespace std;

int main(){
    cout << "请输入指令" << endl;
    TaskScheduler taskscheduler;
    
    while(1){
        string command;
        cin >> command;
        string robotname;
        if(command == "添加机器人"){           
            cin >> robotname;
            taskscheduler.addRobot(robotname);
        }else if(command == "添加任务"){
            int id;
            string description;
            int importance;
            cin >> robotname >> id >> description >> importance;
            Robot(robotname).addTask(id, description, importance);
        }else if(command == "撤销任务"){
            cin >> robotname;
            Robot(robotname).deleteTask();
        }else if(command == "执行任务"){
            cin >> robotname;
            Robot(robotname).executeTasks();
        }else if(command == "删除机器人"){
            cin >> robotname;
            taskscheduler.deleteRobot(robotname);
        }else if(command == "查询任务"){
            cin >> robotname;
            Robot(robotname).displayTasks();
        }else if(command == "获取机器人名称列表"){
            taskscheduler.getRobotsName();
        }else if(command == "退出"){
            cout << "退出" << endl;
            return 0;
        }else{
            cout << "无效(未知)的命令" << endl;
            continue;
        }
    }
    cout << "结束" << endl;

    return 0;
}