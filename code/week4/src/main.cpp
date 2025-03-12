#include "manage.hpp"
#include "task.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>

int main()
{
    manage manager;
    std::thread t1(&manage::monitor_out, &manager);

    while(true)
    {
        mtx.lock();
        std::cout << "请输入:" << std::endl;
        mtx.unlock();
        std::string command;
        std::cin >> command;
        if(command == "添加任务")
        {
            std::cout << "输入任务类型(task1:1, task2:2, task3:3)和标识:" << std::endl;
            int kind;
            int key;
            std::cin >> kind >> key;
            manager.add(key, kind);
        }
        else if(command == "删除任务")
            manager.pop();
        else if(command == "修改监测值")
        {
            std::cout << "输入标识和参数" << std::endl;
            int key, msg;
            std::cin >> key >> msg;
            manager.f(key, msg);
        }
        else if(command == "退出")
        {
            manager.stop();
            t1.join();
            break;
        }
        else
            std::cout << "输入错误" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}