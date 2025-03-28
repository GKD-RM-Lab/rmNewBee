#include "Robot.h"
#include "Task.h"
Robot::Robot(std::string name): robot_name(name) {
    // 初始化机器人名称并清空任务队列
}

Robot::~Robot()
{
    //打印所有未执行任务信息
    std::cout <<"未执行任务:" <<std::endl;
    for(const auto &item:queue)
    {
        if(item.get_statues()!="已执行")
        {
            std::cout <<"ID:" <<item.get_ID() <<",Description:" <<item.get_desc() 
            <<",Priority:"<<item.get_priority() <<std::endl; 
        }
    }
}

void Robot::add_task(int ID,std::string desc,int priority)
{
    queue.emplace(ID,desc,priority);
}

void Robot::do_task()
{
    if(!queue.empty())
    {
        //由于it是const对象不能调用非const函数task_done，所以采用先移除元素再插入的办法
        auto it = queue.begin();
        Task task = *it;
        queue.erase(it);

        std::cout <<"Task execute:" <<task.get_ID() 
        <<" " <<task.get_desc()<<" Priority:" <<task.get_priority() <<std::endl;
        task.task_done();
        queue.insert(task);  
    }
    else{
        std::cerr <<"No task is existed now." <<std::endl;
        return;
    }
}

void Robot::delete_task()
{
    if(!queue.empty())
    {
        auto it = --queue.end();
        std::cout <<"Removing task:" <<it->get_ID() <<"," <<it->get_desc()
                  <<",Priority:" <<it->get_priority() <<"," <<it->get_statues() <<std::endl;
        queue.erase(it);
    }
    else
    {
        std::cerr <<"No tasks to remove." <<std::endl;
        return;
    }
}

void Robot::indicate_task() const
{   if(queue.empty())
    {
      std::cerr <<"No tasks to indicate." <<std::endl;
      return;
    }else
    {
    for(const auto& item:queue)
    {
        std::cout   <<"Priority:" <<item.get_priority()
                    <<",ID:" <<item.get_ID()
                    <<",Description:" <<item.get_desc()
                    <<",Statue:" <<item.get_statues()
                    <<std::endl;
    }
}
}