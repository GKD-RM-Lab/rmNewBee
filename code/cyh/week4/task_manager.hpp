#pragma once

#include "task.hpp"
#include <thread>
#include <list>
#include <mutex>
#include <atomic>
#include <memory>
#include <string>
#include <iostream>

class TaskManager{
    private:
        int out;
        std::list<int> a;
        std::mutex mtx;
        std::thread mo_thread;
        std::thread run_thread;
        std::atomic<bool> running; 
        std::list<std::unique_ptr<Task>> tasks;
    public:

        TaskManager() : out(0), running(true){
            std::cout << "begin" << std::endl;
            mo_thread = std::thread(&TaskManager::mo_out, this);
            run_thread = std::thread(&TaskManager::ct_input, this);
        }

        ~TaskManager(){
            running = false;
            if(mo_thread.joinable()){
                mo_thread.join();
            }
            if(run_thread.joinable()){
                run_thread.join();
            }
        }
        
        void add_task(int key, const std::string& kind){
            std::lock_guard<std::mutex> lock(mtx);
            
            a.push_back(0);
            auto rit = a.rbegin();
            ++rit;
            int* p1 = &a.back();
            int * p2 = (a.size() == 1) ? &out : &(*rit);
    
            for(auto& task : tasks){
                if(task->get_key() == key){
                    std::cout << "invalid key" << std::endl;
                    return;
                }
            }

            if (kind == "Task1"){
                tasks.push_back(std::make_unique<Task1>(key, p1, p2));
                std::cout << "succeed in creating Task1" << std::endl;
            }else if (kind == "Task2"){
                tasks.push_back(std::make_unique<Task2>(key, p1, p2));
                std::cout << "succeed in creating Task2" << std::endl;

            }else if (kind == "Task3"){
                tasks.push_back(std::make_unique<Task3>(key, p1, p2));
                std::cout << "succeed in creating Task3" << std::endl;
            }
            tasks.back()->run();
        }

        void pop_task(){
            std::lock_guard<std::mutex> lock(mtx);
            if(!a.empty()){
                tasks.back()->stop();
                tasks.pop_back();
                a.pop_back();
                std::cout << "succeed in deleting a task" << std::endl;
            }else{
                std::cout << "No tasks left" << std::endl;
                return;
            }
        }

        void trigger_callback(int key, int msg){
            std::lock_guard<std::mutex> lock(mtx);
            for(auto& task : tasks){
                if(task->get_key() == key){
                    task->call_back(msg);
                    std::cout << "succeed in callbacking" << std::endl;
                    break;
                }
            }
        }

        void mo_out(){
            while(running){
                if(out != 0){
                    std::cout << "out: " << out << std::endl;
                    out = 0;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        void ct_input(){
            std::string command;
            while(running){
                std::cin >> command;
                if(command == "add"){
                    int key;
                    std::string kind;
                    std::cin >> key >> kind;
                    add_task(key, kind);                
                   
                }else if(command == "pop"){
                    pop_task();
                   
                }else if(command == "callback"){
                    int key;
                    int msg;
                    std::cin >> key >> msg;
                    trigger_callback(key, msg);
                }
            }
        }

};