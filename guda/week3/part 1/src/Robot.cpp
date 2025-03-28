#include "Robot.h"
#include <iostream>
#include <vector>
Robot::Robot(std::string name): Robot_name(name) {
    // 初始化机器人名称并清空任务队列
}

Robot::~Robot()
{
    //打印所有未执行任务的信息
    std::cout <<"未执行任务：" <<std::endl;
    for(int i=0;i<queue.size();i++)
    {
        if(queue[i].get_statue()!="已执行")
        {
            std::cout <<"ID:" <<queue[i].get_ID() 
                      <<",Description:" <<queue[i].get_desc()
                      <<std::endl;            
        }
    }
}

void Robot::add_task(int ID,std::string desc)
{
    queue.emplace_back(ID,desc);
}

void Robot::task_done()
{
    for (auto& task : queue) {
        task.do_task(); // 执行任务
    }
}

void Robot::indicate()
{
    for (const auto& task : queue) {
        std::cout << "ID: " << task.get_ID() 
                  << ", description: " << task.get_desc()
                  << ", status: " << task.get_statue()
                  << std::endl;
    }
}

void Robot::delete_task()
{
    queue.pop_back();
}