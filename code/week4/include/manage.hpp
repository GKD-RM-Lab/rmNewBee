#pragma once
#include "task.hpp"
#include <vector>
#include <thread>
#include <memory>
#include <atomic>
#include <array>
#include <map>

class manage
{
private:
    std::atomic<int> out = 0;
    std::map<int, std::shared_ptr<task>> task_storage;
    std::vector<std::thread> t;
    std::array<std::atomic<int>,100> a{};
public:
    void add(int key, int kind);
    void monitor_out();
    void pop();
    void f(int key, int msg);
    ~manage();
};
