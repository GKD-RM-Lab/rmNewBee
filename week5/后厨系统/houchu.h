#pragma once
#include"houchu.cpp"
//判断是否充足
void read(int linenum);
//判断食物信息对应哪种
int *judge(int linenum);
//用去某种食材
void write(int linenum);
//写log文件
void log(int a);
void* working(void* arg);