#include "TaskScheduler.h"
#include <iostream>
void TaskScheduler::add_Robot(const std::string &name)
{
    if(Robotlist.count(name))
    {
        std::cerr <<"has:" <<name <<"in the list" <<std::endl;
        return;
    }
    Robotlist[name]=new Robot(name);
}

void TaskScheduler::delete_robot(const std::string &name)
{
    if(Robotlist.count(name)==0)
    {
        std::cerr <<"The name "<<name <<" is not existed." <<std::endl;
        return;
    }
    delete Robotlist[name];//释放键为name所对应的指针指向的动态分配内存，调用Robot的析构函数
    Robotlist.erase(name);//移除键为name的函数，但并不会释放该指针对应的内存
}

Robot* TaskScheduler::find_robot(const std::string &name)
{
    if(Robotlist.count(name)==0)
    {
        std::cerr <<"The robot " <<name <<" is not esisted." <<std::endl;
        return nullptr;
    }
    return Robotlist[name];
}

std::vector<std::string> TaskScheduler::get_robotlist()
{
    // 定义 name_list 容器，用于存储机器人名称
    std::vector<std::string> name_list;
    // 遍历 robot_list 容器，将键添加到 name_list 容器中
    //for循环新形式，基于范围的for循环
    for(auto [key,val]:Robotlist)
    {
        name_list.push_back(key);
    }
    return name_list;
}