#include "task.hpp"
#include <iostream>
#include <mutex>
#include <chrono>
///////////////////////task
std::mutex mtx;

task::task(int key)
:key(key), is_running(false), p1(nullptr), p2(nullptr) {}

void task::callback(int msg)
{
    *p1 = msg;
}

void task::monitor(std::atomic<int>& pre, std::atomic<int>& sub)
{
    p2 = &pre;
    p1 = &sub;
}

void task::stop(std::thread& t, int i)
{
    is_running = false;
    t.join();
    std::cout << "任务" << i << "结束" << std::endl;
}

void task::stop(std::thread& t)
{
    is_running = false;
    t.join();
}

////////////////////////task1
task1::task1(int key)
:task(key) {}

void task1::run()
{
    if(!is_running.load())
    {
        is_running = true;
        while(is_running.load())
        {
            mtx.lock();
            if(p1->load())
            {
                *p2 = p1->exchange(0);
                p2->fetch_add(1);
                std::cout << "write {task1}-{" << key << "}: " <<
                "{" << p2->load() << "}" << std::endl << std::flush;
            }
            mtx.unlock();
        }    
    }   
}

////////////////////////task2
task2::task2(int key)
:task(key), k(1) {}

void task2::callback(int msg)
{
    k = msg;
    *p1 = 1;
}

void task2::run()
{
    if(!is_running.load())
    {
        is_running = true;
        while(is_running.load())
        {
            mtx.lock();
            if(p1->load())
            {
                *p2 = (*p1)*k;
                *p1 = 0;
                std::cout << "write {task2}-{" << key << "}: " <<
                "{" << p2->load() << "}" << std::endl << std::flush;
            }
            mtx.unlock();
        }
    }
}
///////////////////////////task3
task3::task3(int key)
:task(key) {}

void task3::run()
{
    if(!is_running.load())
    {
        is_running = true;
        while(is_running.load())
        {
            mtx.lock();
            if(p1->load())
            {
                int t = p1->load();
                *p1 = 0;
                *p2 = t;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                *p2 += 1;
                std::cout << "write {task3}-{" << key << "}: " <<
                "{" << p2->load() << "}" << std::endl << std::flush;
            }
            mtx.unlock();
        }
    }
}