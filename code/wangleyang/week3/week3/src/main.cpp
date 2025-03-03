#include<iostream>
#include "robot.hpp"
#include "TaskScheduler.hpp"
using namespace std;
int main(){
    scheduler Scheduler;
    string commend;
    string nameRobot;
    while (true){
    cout << "Please enter the command"<<endl;
    cin>>commend;
    if(commend=="添加机器人"){
        cin>>nameRobot;
        Scheduler.addrobot(nameRobot);
    }
    else if(commend=="添加任务"){
        int id;
        string description;
        cin>>nameRobot>>id>>description;
        auto it=Scheduler.getRobot(nameRobot);
        it->addtask(id, description);
    }
    if(commend=="撤销任务"){
        cin>>nameRobot;
        auto it=Scheduler.getRobot(nameRobot);
        it->remove();
    }
    if(commend=="执行任务"){
        cin>>nameRobot;
        auto it=Scheduler.getRobot(nameRobot);
        it->executetasks();
    }
    if(commend=="删除机器人"){
        cin>>nameRobot;
        Scheduler.deletrobot(nameRobot);
    }
    if(commend=="查询任务"){
        cin>>nameRobot;
        auto it=Scheduler.getRobot(nameRobot);
        it->displaytasks();
    }
    if(commend=="获取机器人名称列表"){
        Scheduler.gainRobot();
    }
    if(commend=="退出"){
        break;
    }
}
    return 0;
}
