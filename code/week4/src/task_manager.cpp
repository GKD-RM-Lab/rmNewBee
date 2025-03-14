#include "task_manager.h"

#include <iostream>

void TaskManager::run() {
    out_thread = std::thread(&TaskManager::out_check, this);
    while (true) {
        std::string cmd;
        std::cin >> cmd;
        if(cmd == "add") {
            int key, kind;
            std::cin >> key >> kind;
            add_task(key, kind);
            printf("add finish\n");
        } else if (cmd == "callback") {
            int key, msg;
            std::cin >> key >> msg;
            if(task_map.count(key)) {
                task_map[key]->callback(msg);
            } else {
                std::cerr << "Invalid key: " << key << std::endl;
            }
        } else if(cmd == "pop") {
            if(!task_list.empty()) {
                pop_task();
                printf("pop finish\n\n");
            } else {
                printf("task list is empty!\n");
            }
        }
    }
}

void TaskManager::out_check() {
    while(true) {
        int val = out.exchange(0);
        if(val != 0) {
            printf("out: %d\n\n", val);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void TaskManager::add_task(int key, int kind) {
    TaskBase *task_pointer = nullptr;
    auto p2 = a.empty() ? &out : a.back();
    a.push_back(new std::atomic<int>(0));
    auto p1 = a.back();
    if(kind == 1) {
        task_pointer = new Task1(key, p1, p2);
    } else if(kind == 2) {
        task_pointer = new Task2(key, p1, p2);
    } else {
        task_pointer = new Task3(key, p1, p2);
    }
    task_map[key] = task_pointer;
    task_list.push_back(task_pointer);
    task_pointer->start();
}

void TaskManager::pop_task() {
    auto task_pointer = task_list.back();
    task_list.pop_back();
    task_map.erase(task_pointer->key);
    task_pointer->stop();
    delete task_pointer;
    delete a.back();
    a.pop_back();
}
