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
    int i;
    while(true)
    {   
        std::cout <<"1.add_robot 2.add_task 3.delete_task 4.task_done 5.delete_robot 6.indicate 7.list_robot 8.exit" <<endl;
        std::cout <<"Please enter the command(number):";
        cin >>i;
        switch (i)
        {
        case 1://add_robot
        {
            string name;
            std::cout <<"Please enter the robot name:";
            cin >>name;
            list1.add_Robot(name);             
            break;
        }
        case 2://add_tasks
        {
            string name;
            int ID;
            string desc;
            cout <<"Please enter the robot name:";
            cin >> name;
            Robot* robot = list1.find_robot(name);
            if (robot) {
                cout <<"Please enter the task ID and description:";
                cin >> ID >> desc;
                robot->add_task(ID, desc);
            } else {
                cout << "Robot not found." << endl;
            }
            break;
        }
        case 3://delete_task
        {
            string name;
            std::cout <<"Please enter the robot name:";
            cin >> name;
            Robot* robot = list1.find_robot(name);
            if (robot) {
                robot->delete_task();
            } else {
                cout << "Robot not found." << endl;
            }
            break;
        }
        case 4://task_done
        {
            string name;
            std::cout <<"Please enter the robot name:";
            cin >> name;
            Robot* robot=list1.find_robot(name);
            if(robot)
            {
            list1.find_robot(name)->task_done();
            }
            else {
                cout << "Robot not found." << endl;
            }
            break;
        }
        case 5://delete_robot
        {
            string name;
            std::cout <<"Please enter the robot name:";
            cin >> name;
            Robot *robot=list1.find_robot(name);
            if(robot)
        {
            list1.delete_robot(name);
        }
        else{
            cout <<"Robot not found" <<endl;
        }
            break;
        }
        case 6://indicate_tasks
        {   
            string name;
            std::cout <<"Please enter the robot name:";
            cin >> name;
            Robot *robot=list1.find_robot(name);
            if(robot)
        {
            list1.find_robot(name)->indicate();
        }
        else{
            cout <<"Robot not found" <<endl;
        }
            break;
        }
        case 7://list_robots
        {
            auto list=list1.get_robotlist();
            std::cout <<"Robot name list:" <<endl;
            for(const auto &name :list)
            {
                std::cout <<"name:" <<name <<endl;
            }
            break;
        }
        case 8://exit
           return 0;
        default:
            cout<<"Invalid command."<<endl;
            break;
        }  
}
    return 0;
}
