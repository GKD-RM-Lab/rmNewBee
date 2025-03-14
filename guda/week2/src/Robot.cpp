//Robot.cpp
#include "Robot.h"
#include <vector>

Robot::Robot(std::string robotName) : Robot_name(robotName), taskcount(0)
{
    // 初始化机器人名称并清空任务队列
}

Robot::~Robot()
{
    //显示所有未完成任务
    for(int i=0;i<taskcount;++i)
    {
        if(quest[i].get_status()=="待执行"){
            std::cout << "未完成任务ID:" <<quest[i].getID() <<",描述:" <<quest[i].get_description() <<std::endl;                           
        }
    }

}
 
void Robot::add_quest(int id,std::string desc)
{
    //将新任务添加到任务列表中
    if(taskcount<100)
    {
        quest[taskcount++]=task(id,desc);
    }   
}

void Robot::do_task()
{
    //ִ执行队列中的任务，并更新任务状态
    std::cout << "开始执行任务..." << std::endl;
    for(int i=0;i<taskcount;++i)
    {
        quest[i].task_done();
    } 
    std::cout << "任务执行完成。" << std::endl;
    
}

void Robot::indicate(){
    //显示所有任务的描述和状态
    for(int i=0;i<taskcount;i++){
        std::cout <<"任务ID:" <<quest[i].getID() 
             <<",描述:" <<quest[i].get_description() <<",状态" <<quest[i].get_status() <<std::endl;
    }
}
