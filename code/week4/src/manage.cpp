#include "manage.hpp"
#include <mutex>
#include <chrono>
#include <iostream>

void manage::add(int key, int kind)
{
    std::lock_guard<std::mutex> lock(mtx);
    size_t location = task_storage.size();

    if(location >= a.size())
    {
        std::cerr << "任务数量超过限制!" << std::endl;
        return;
    }

    std::shared_ptr<task> temp;
    switch(kind) 
    {
        case 1:
            temp = std::make_shared<task1>(key);
            break;
        case 2:
            temp = std::make_shared<task2>(key);
            break;
        case 3:
            temp = std::make_shared<task3>(key);
            break;
        default:
            std::cout << "输入错误" << std::endl;
            return;
    }

    if(location > 0)
        temp->monitor(a[location-1], a[location]);
    else
        temp->monitor(out, a[location]);

    task_storage.emplace(key, temp);
    t.emplace_back(&task::run, temp);
}

void manage::monitor_out()
{
    while(t.size())
    {
        mtx.lock();
        if(out.load())
        {
            std::cout << "out=" << out.load() << std::endl << std::flush;
            out = 0;
        };
        mtx.unlock();
    }
}

void manage::pop()
{
    if(!task_storage.empty())
    {
        auto temp = std::prev(task_storage.end());
        (temp->second)->stop(t.back(), temp->first);
        mtx.lock();
        t.pop_back();
        a[task_storage.size()-1] = 0;
        task_storage.erase(temp);
        mtx.unlock();
    }
}

void manage::f(int key, int msg)
{   
    mtx.lock();
    auto it = task_storage.find(key);
    mtx.unlock();
    if (it == task_storage.end())
        std::cout << "未找到" << std::endl;
    else
        (it->second)->callback(msg); 
}

manage::~manage()
{
    int i = 0;
    for(auto it : task_storage)
        it.second->stop(t[i++]);
    std::cout << "任务全部结束" << std::endl;
}