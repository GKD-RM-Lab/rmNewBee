#include<iostream>
#include"robot.hpp"
robot::~robot(){
    for(int i=0;i<LIST;i++){
    if(newtask[i].ZHUANGTAI=="待执行"){
        std::cout<<"未执行任务ID: "<<newtask[i].ID<<", 描述："<<newtask[i].MIAOSHU<<std::endl;
    }
    }
}
void robot::zhuangtai(){
    for(int i=0;i<LIST;i++){
    newtask[i].zhuangtai();
    }
}

void robot::xianshi(){
    for(int i=0;i<LIST;i++){
        std::cout<<"任务ID:"<<newtask[i].ID<<", 描述："<<newtask[i].MIAOSHU<<", 状态："<<newtask[i].ZHUANGTAI<<std::endl;
    }
}