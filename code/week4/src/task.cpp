#include "task.h"

#include <iostream>

void sleep_ms(int val) {
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
}

void TaskBase::start() {
    handler = std::thread(&TaskBase::run, this);
}

void TaskBase::stop() {
    finish = true;
    handler.join();
}

void Task1::callback(int msg) {
    *p1 = msg;
}

void Task1::run() {
    while (!finish) {
        int val = p1->exchange(0);
        if(val != 0) {
            *p2 = val + 1;
            printf("write 1-%d: %d\n\n", key, val + 1);
        }
        sleep_ms(1);
    }
}

void Task2::callback(int msg) {
    k = msg;
    *p1 = 1;
}

void Task2::run() {
    while (!finish) {
        int val = p1->exchange(0);
        if(val != 0) {
            *p2 = val * k;
            printf("write 2-%d: %d\n\n", key, val * k);
        }
        sleep_ms(1);
    }
}

void Task3::callback(int msg) {
    *p1 = msg;
}

void Task3::run() {
    while (!finish) {
        int val = p1->exchange(0);
        if(val != 0) {
            *p2 = val;
            printf("write 3-%d: %d\n\n", key, val);
            sleep_ms(1);
            *p2 = val + 1;
            printf("write 3-%d: %d\n\n", key, val + 1);
        }
        sleep_ms(1);
    }
}
