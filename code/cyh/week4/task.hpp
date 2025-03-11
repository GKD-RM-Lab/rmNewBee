#pragma once

#include <thread>
#include <atomic> 
#include <mutex>
#include <iostream>

class Task {
    public:  
        int key;
        std::atomic<int> *p1;
        std::atomic<int> *p2;
        std::atomic<bool> running;
        std::thread ex_thread;
        std::mutex mtx;


        Task(int key, std::atomic<int>* p1, std::atomic<int>* p2) : key(key), p1(p1), p2(p2), running(false) {}
        virtual ~Task(){
            stop();
        }
    
        virtual void run(){
            running.store(true);
            ex_thread = std::thread(&Task::execute, this);
        }
    
        virtual void stop(){
            if (running.load()) {
                running.store(false);
                if (ex_thread.joinable()){
                    ex_thread.join();
                }
               
            }
        }

        virtual int get_key(){
            return this->key;
        }
    
        virtual void call_back(int msg) = 0;
        virtual void execute() = 0;
    };


    class Task1 : public Task {
        public:
            Task1(int key, std::atomic<int>* p1, std::atomic<int>* p2) : Task(key, p1, p2) {}
        
            void call_back(int msg) override{
                *p1 = msg;
            }
        
            void execute() override{
                while (running.load()){
                    int val = p1->exchange(0);
                    if (val != 0){
                        *p2 = val + 1;
                        //std::cout << "write Task1-" << key << ": " << *p2 << std::endl;
                        printf("write Task1-%d: %d\n", key, val + 1);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };
        
        class Task2 : public Task {
        private:
            int k;
        
        public:
            Task2(int key, std::atomic<int>* p1, std::atomic<int>* p2) : Task(key, p1, p2), k(1) {}
        
            void call_back(int msg) override{
                k = msg;
                *p1 = 1;
            }
        
            void execute() override{
                while (running.load()) {
                    int val = p1->exchange(0);
                    if (val != 0) {
                        *p2 = val * k;
                       
                        //std::cout << "write Task2-" << key << ": " << *p2 << std::endl;
                        printf("write Task2-%d: %d\n", key, val * k);                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };
        
        class Task3 : public Task{
        public:
            Task3(int key, std::atomic<int>* p1, std::atomic<int>* p2) : Task(key, p1, p2) {}
        
            void call_back(int msg) override{
                *p1 = msg;
            }
        
            void execute() override{
                while (running.load()){
                    int val = p1->exchange(0);
                    if (val != 0){
                        *p2 = val;
                        //std::cout << "write Task3-" << key << ": " << *p2 << std::endl;
                        printf("write Task3-%d: %d\n", key, val);
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        *p2 = val + 1;
                        //std::cout << "write Task3-" << key << ": " << *p2 << std::endl;
                        printf("write Task3-%d: %d\n", key, val + 1);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };