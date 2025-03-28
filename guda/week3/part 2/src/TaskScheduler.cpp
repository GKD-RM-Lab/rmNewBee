#include "TaskScheduler.h"
void TaskScheduler::add_Robot(const std::string &name)
{
    if(robot_list.count(name))
    {
        std::cerr <<"has:" <<name <<" in the robotlist." <<std::endl;
        return;
    }
    else
    {
        robot_list[name]=new Robot(name);
    }
}

void TaskScheduler::delete_robot(const std::string &name)
{
    if(!robot_list.count(name)){
        std::cerr <<"The robot " <<name <<"is not in the list." <<std::endl;
        return; 
    }
    else
    {
        delete robot_list[name];//释放键对应空间内存
        robot_list.erase(name);//移除键，不会释放内存
    }
}

Robot* TaskScheduler::find_robot(const std::string& name)
{
    if(!robot_list.count(name)){
        std::cerr<<"The robot "<<name <<" is not existed." <<std::endl;
        return nullptr;
    }
    return robot_list[name];
}

std::vector<std::string> TaskScheduler::get_robotlist()
{
    std::vector<std::string> name_list;
    for(auto [key,val]:robot_list)
    {
        name_list.push_back(key);
    }
    return name_list;
}

