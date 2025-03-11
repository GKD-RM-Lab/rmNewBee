#pragma once

#include <atomic>
#include <vector>
#include <thread>

class TaskBase {
public:
    TaskBase(int key, std::atomic<int> *p1, std::atomic<int> *p2) : key(key), p1(p1), p2(p2) {}

    virtual void callback(int msg) = 0;
    virtual void run() = 0;
    virtual ~TaskBase() = default;

    void start();
    void stop();

    int key;

protected:
    std::atomic<int> *p1 = nullptr, *p2 = nullptr;
    std::atomic<bool> finish;

private:
    std::thread handler;
};

class Task1 : public TaskBase {
public:
    Task1(int key, std::atomic<int> *p1, std::atomic<int> *p2) : TaskBase(key, p1, p2) {}

    void callback(int msg) override;
    void run() override;
};

class Task2 : public TaskBase {
public:
    Task2(int key, std::atomic<int> *p1, std::atomic<int> *p2) : TaskBase(key, p1, p2) {}

    void callback(int msg) override;
    void run() override;

    int k = 1;
};

class Task3 : public TaskBase {
public:
    Task3(int key, std::atomic<int> *p1, std::atomic<int> *p2) : TaskBase(key, p1, p2) {}

    void callback(int msg) override;
    void run() override;
};