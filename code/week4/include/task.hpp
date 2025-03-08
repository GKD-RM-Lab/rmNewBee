#pragma once
#include <thread>
#include <atomic>
#include <mutex>
extern std::mutex mtx;
class task
{
protected:
    int key;
    std::atomic<bool> is_running;
    std::atomic<int> *p1, *p2;
public:
    task (int key);
    virtual void run() = 0;
    virtual void callback(int msg);
    void monitor(std::atomic<int>& pre, std::atomic<int>& sub);
    void stop(std::thread& t, int i);
    void stop(std::thread& t);
};

class task1 : public task
{
public:
    task1(int key);
    void run() override;
};

class task2 : public task
{
private:
    std::atomic<int> k;
public:
    task2(int key);
    void run() override;
    void callback(int msg) override;
};

class task3 : public task
{
public:
    task3(int key);
    void run() override;   
};