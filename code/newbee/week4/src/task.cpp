#include<iostream>
#include<thread>
#include"task.hpp"
void sleep_ms(int val) {
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
}
void Task1::run(){
    while(!finish){
    int val =p1->exchange(0);
    if(val!=0){
    *p2=val+1;
    printf("write {task1}-{%d}: {%d\n}",key,val+1);
    }
    sleep_ms(1);
    }
}
void Task2::run(){
    while(!finish){
    int val =p1->exchange(0);
    if(val!=0){
    *p2=val*k;
    printf("write {task2}-{%d}: {%d\n}",key,val*k);
    }
    sleep_ms(1);
    }
}
void Task3::run(){
    while(!finish){
    int val =p1->exchange(0);
    if(val!=0){
    t=val;
    *p2=t;
    printf("write {task3}-{%d}: {%d\n}",key,val);
    sleep_ms(1);
    *p2=t+1;
    printf("write {task3}-{%d}: {%d\n}",key,val+1);
    }
    sleep_ms(1);
    }
}
void Task1::callback(int msg){
    *p1=msg;
}
void Task2::callback(int msg){
    k=msg;
    *p1=1;
}
void Task3::callback(int msg){
    *p1=msg;
}
void task::stop(){
    finish = true;
    handler.join();
}
void task::start(){
    handler = std::thread(&task::run, this);
}