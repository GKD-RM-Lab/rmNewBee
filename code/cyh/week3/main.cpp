#include <iostream>
#include "robot.hpp"
#include "taskscheduler.hpp"

using namespace std;

int main(){
    cout << "请输入指令" << endl;
    TaskScheduler taskscheduler;
    
    while(true){
        string command;
        cin >> command;
        string robotname;

        if(command == "添加机器人"){           
            cin >> robotname;
            taskscheduler.addRobot(robotname);
            
        } else if(command == "添加任务"){
            int id;
            string description;
            int importance;

            cin >> robotname >> id;
            cin.ignore();
            getline(cin, description);
            cin >> importance;

            Robot &robot = taskscheduler.getRobot(robotname);
            robot.addTask(id, description, importance);
            
        } else if(command == "撤销任务"){
            cin >> robotname;
            Robot &robot = taskscheduler.getRobot(robotname);
            robot.deleteTask();
            
        } else if(command == "执行任务"){
            cin >> robotname;
            Robot &robot = taskscheduler.getRobot(robotname);
            robot.executeTasks();
            
        } else if(command == "删除机器人"){
            cin >> robotname;
            taskscheduler.deleteRobot(robotname);
            
        } else if(command == "查询任务"){
            cin >> robotname;
            Robot &robot = taskscheduler.getRobot(robotname);
            robot.displayTasks();

        } else if(command == "获取机器人名称列表"){
            for (const string& name : taskscheduler.getRobotsName()) {
                cout << name << endl;
            }
        } else if(command == "退出"){
            cout << "成功退出" << endl;
            return 0;
        } else{
            cout << "无效(未知)的命令" << endl;
            continue; 
        }

        cout << "执行成功" << endl;
    }
    return 0;
}
