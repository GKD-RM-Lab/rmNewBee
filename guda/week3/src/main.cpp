#include "Robot.h"
#include "Task.h"
#include "TaskScheduler.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm> 

using namespace std;

int main()
{ 
    TaskScheduler list1;
    string command;
    vector<string> valid_command={"add_robot", "add_task", "delete_task", "task_done", "delete_robot", "indicate", "list","exit" };
    while(true)
    {   
        std::cout <<"1.add_robot 2.add_task 3.delete_task 4.task_done 5.delete_robot 6.indicate 7.list 8.exit" <<endl;
        std::cout <<"Please enter the command:";
        cin >>command;
        if(command=="exit")
        {
            break;
        }
        else if(command=="list"){    
            auto list=list1.get_robotlist();
            std::cout <<"机器人名称列表:" <<endl;
            for(const auto &name :list)
            {
                std::cout <<"name:" <<name <<endl;
            }
            continue;
        }
        else if(std::find(valid_command.begin(),valid_command.end(),command)==valid_command.end()){
            std::cout <<"invalid command" <<std::endl;
            continue;
        }
        
    string name;
    std::cout <<"请输入机器人名称：";
    cin >>name;
    if(command=="add_robot")
    {
        list1.add_Robot(name); 
    }
    else if(command =="add_task")
    {
        int ID;
        string desc;
        cin >>ID >>desc;
        list1.find_robot(name)->add_task(ID,desc);
    }
    else if(command=="delete_task")
    {
        list1.find_robot(name)->delete_task();
    }
    else if(command =="task_done")
    {
        list1.find_robot(name)->task_done();
    }
    else if(command =="delete_robot")        
    {
        list1.delete_robot(name);
    }
    else if(command=="indicate")
    {
        list1.find_robot(name)->indicate();
    }
}
    return 0;
}
