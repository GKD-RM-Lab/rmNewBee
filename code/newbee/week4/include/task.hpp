#pragma once
#include<iostream>
#include<thread>
#include<atomic>
class task{
public:
    int key;
    virtual void callback(int msg)=0;
    virtual void run()=0;
    void stop();
    void start();
    task(int a,std::atomic<int>* P1,std::atomic<int>* P2):key(a),p1(P1),p2(P2){}
    virtual ~task(){};
protected:
    std::atomic<int> *p1 = nullptr, *p2 = nullptr;
    std::atomic<bool> finish;
private:
    std::thread handler;
};
class Task1:public task{
public:
    void run() override;
    void callback(int msg) override;
    Task1(int key,std::atomic<int>* p1,std::atomic<int>* p2):task(key,p1,p2){}
};
class Task2:public task{
public:
    int k=1;
    void run() override;
    void callback(int msg) override;
    Task2(int key,std::atomic<int>* p1,std::atomic<int>* p2):task(key,p1,p2){}
};
class Task3:public task{
public:
    int t;
    void run() override;
    void callback(int msg) override;
    Task3(int key,std::atomic<int>* p1,std::atomic<int>* p2):task(key,p1,p2){}
};