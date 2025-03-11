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
        std::atomic<int> out;
        std::list<std::atomic<int> *> a;
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
            
            for(auto& task : tasks){
                if(task->get_key() == key){
                    //std::cout << "invalid key" << std::endl;
                    printf("Invalid key!\n");
                    return;
                }
            }
            
            // *a.push_back(0);
            // auto rit = a.rbegin();
            // ++rit;
            // auto p1 = &a.back();
            // auto p2 = (a.size() == 1) ? &out : &(*rit);
            auto p2 = a.empty() ? &out : a.back();
            a.push_back(new std::atomic<int>(0));
            auto p1 = a.back();
    
            

            if (kind == "1"){
                tasks.push_back(std::make_unique<Task1>(key, p1, p2));
                //std::cout << "succeed in creating Task1" << std::endl;
                printf("succeed in creating Task1\n");
            }else if (kind == "2"){
                tasks.push_back(std::make_unique<Task2>(key, p1, p2));
                //std::cout << "succeed in creating Task2" << std::endl;
                printf("succeed in creating Task2\n");
            }else if (kind == "3"){
                tasks.push_back(std::make_unique<Task3>(key, p1, p2));
                //std::cout << "succeed in creating Task3" << std::endl;
                printf("succeed in creating Task3\n");
            }
            tasks.back()->run();
        }

        void pop_task(){
            std::lock_guard<std::mutex> lock(mtx);
            if(!a.empty()){
                tasks.back()->stop();
                tasks.pop_back();
                a.pop_back();
               //std::cout << "succeed in deleting a task" << std::endl;
               printf("succeed in deleting a task\n");
            }else{
                //std::cout << "No tasks left" << std::endl;
                printf("No tasks left\n");
                return;
            }
        }

        void trigger_callback(int key, int msg){
            std::lock_guard<std::mutex> lock(mtx);
            for(auto& task : tasks){
                if(task->get_key() == key){
                    task->call_back(msg);
                    //std::cout << "succeed in callbacking" << std::endl;
                    break;
                }
            }
        }

        void mo_out(){
            while(running){
                if(out != 0){
                    //std::cout << "out: " << out << std::endl;
                    int o = out.exchange(0);
                    printf("out: %d\n", o);
                    
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