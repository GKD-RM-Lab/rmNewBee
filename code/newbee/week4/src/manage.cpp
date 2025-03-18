#include"manage.hpp"
#include<iostream>
#include<thread>
#include<string>
void manage::checkout(){
    while(true){
        int val=out.exchange(0);
        if(val!=0){
            printf("%d\n",val);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void manage::run(){
    out_thread = std::thread(&manage::checkout, this);
    std::string name;
    while(true){
    std::cin>>name;
    if(name=="add"){
        int key,kind;
        task*p=nullptr;
        printf("输入 key kind\n");
        std::cin>>key>>kind;
        tasks.insert({key,p});
        auto p2 = a.empty() ? &out : a.back();
        a.push_back(new std::atomic<int>(0));
        auto p1 = a.back();
        printf("add finish\n");
        if(kind==1){
            p=new Task1(key,p1,p2);
        }
        else if(kind==2){
            p=new Task2(key,p1,p2);
        }
        else{
            p=new Task3(key,p1,p2);
        }
        task_list.push_back(p);
        tasks[key] = p;
        p->start();
        printf("run finish\n");
    }
    else if(name=="delete"){
        printf("delete start\n");
        auto p = task_list.back();
        task_list.pop_back();
        tasks.erase(p->key);
        p->stop();
        delete p;
        delete a.back();
        a.pop_back();
        printf("delete finish\n");
    }
    if(name=="callback"){
        printf("输入 key msg\n");
        int msg,key;
        std::cin>>key>>msg;
        task*p=tasks[key];
        p->callback(msg);
        printf("callback finish\n");
    }
}
}
