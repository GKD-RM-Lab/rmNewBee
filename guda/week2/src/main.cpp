//main.h
#include "Robot.h"
#include <stdio.h>
int main(){
    std::string robotname;
    std::cout <<"请输入机器人名字:";
    std::cin >> robotname;

    Robot robot1(robotname);

    while(1)
    {
        int i;
        std::cout <<"请输入命令:" <<std::endl
             <<"1.添加\n2.ִ执行\n3.显示\n4.退出" <<std::endl;
        switch (i)
        {
        case 1:
        { 
            int id;
            std::string desc;
            std::cin >>id >>desc;
            robot1.add_quest(id,desc);
            break;
        }
        case 2:
        {
            robot1.do_task();
        }
        case 3:
        {
            robot1.indicate();
        }
        case 4:
            break;
        } 
    }
    return 0;
}
