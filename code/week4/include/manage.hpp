#pragma once
#include "task.hpp"
#include <vector>
#include <thread>
#include <memory>
#include <atomic>
#include <array>
#include <unordered_map>

class manage
{
private:
    std::atomic<int> out;
    std::unordered_map<int, std::shared_ptr<task>> task_storage;
    std::vector<int> order;
    std::vector<std::thread> t;
    std::vector<std::atomic<int>*> a;
    std::atomic<bool> button{true};
public:
    manage();
    void add(int key, int kind);
    void monitor_out();
    void pop();
    void f(int key, int msg);
    void stop();
    ~manage();
};
