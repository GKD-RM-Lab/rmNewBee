#pragma once

#include <thread>
#include <atomic> 
#include <mutex>
#include <iostream>

class Task {
    public:
    
        int key;
        int* p1;
        int* p2;
        std::atomic<bool> running;
        std::thread ex_thread;
        std::mutex mtx;


        Task(int key, int* p1, int* p2) : key(key), p1(p1), p2(p2), running(false) {}
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
            Task1(int key, int* p1, int* p2) : Task(key, p1, p2) {}
        
            void call_back(int msg) override{
                std::lock_guard<std::mutex> lock(mtx);
                *p1 = msg;
            }
        
            void execute() override{
                while (running.load()){
                    if (*p1 != 0){
                        *p2 = *p1 + 1;
                        *p1 = 0;
                        std::cout << "write Task1-" << key << ": " << *p2 << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };
        
        class Task2 : public Task {
        private:
            int k;
        
        public:
            Task2(int key, int* p1, int* p2) : Task(key, p1, p2), k(1) {}
        
            void call_back(int msg) override{
                std::lock_guard<std::mutex> lock(mtx);
                k = msg;
                *p1 = 1;
            }
        
            void execute() override{
                while (running.load()) {
                    if (*p1 != 0) {
                        *p2 = *p1 * k;
                        *p1 = 0;
                        std::cout << "write Task2-" << key << ": " << *p2 << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };
        
        class Task3 : public Task{
        public:
            Task3(int key, int* p1, int* p2) : Task(key, p1, p2) {}
        
            void call_back(int msg) override{
                std::lock_guard<std::mutex> lock(mtx);
                *p1 = msg;
            }
        
            void execute() override{
                while (running.load()){
                    if (*p1 != 0){
                        int t = *p1;
                        *p1 = 0;
                        *p2 = t;
                        std::cout << "write Task3-" << key << ": " << *p2 << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                        *p2 = t + 1;
                        std::cout << "write Task3-" << key << ": " << *p2 << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        };