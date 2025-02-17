#include<iostream>
#include<string>
#include"robot.cpp"
using namespace std;
int main(){
    string nameRobot;
    cin>>nameRobot;
    robot namerobot(nameRobot);
    while (true){
    string commend;
    cin>>commend;
    if(commend=="添加"){
        cin>>namerobot.newtask[namerobot.LIST].ID;
        cin>>namerobot.newtask[namerobot.LIST].MIAOSHU;
        namerobot.LIST+=1;
    }
    if(commend=="执行"){
        namerobot.zhuangtai();
    }
    if(commend=="显示"){
        namerobot.xianshi();
    }
    if(commend=="退出"){
    break;
    }
}
}