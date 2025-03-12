#include "manage.hpp"
#include <mutex>
#include <chrono>
#include <iostream>

manage::manage()
:out(0)
{
    order.reserve(100);
    t.reserve(100);
}

void manage::add(int key, int kind)
{
    size_t location = task_storage.size();

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
    {
        a.emplace_back(new std::atomic<int>(0));
        temp->monitor(a[location-1], a[location]);
    }
    else
    {
        a.emplace_back(new std::atomic<int>(0));
        temp->monitor(&out, a[location]);
    }

    task_storage.emplace(key, temp);
    order.emplace_back(key);
    t.emplace_back(&task::run, temp);
}

void manage::monitor_out()
{
    while(button)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(out.load())
        {
            std::cout << "out=" << out.load() << std::endl << std::flush;
            out = 0;
        };
    }
}

void manage::pop()
{
    if(!task_storage.empty())
    {
        int location = order.back();
        auto it = task_storage.find(location);

        it->second->stop(t.back(), location);
        a[task_storage.size()-1] = 0;
        t.pop_back();
        task_storage.erase(location);
        order.pop_back();
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
        it->second->callback(msg); 
}

void manage::stop()
{
    button = false;
}

manage::~manage()
{
    button = false;
    int i = 0;
    for(auto& it : task_storage)
        (it.second)->stop(t[i++]);
    
    for(auto& it : a)
        delete it;

    std::cout << "任务全部结束" << std::endl;
}