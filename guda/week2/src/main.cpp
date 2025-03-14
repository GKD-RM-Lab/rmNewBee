//main.h
#include "Robot.h"
int main(){
    std::string robotname;
    std::cout <<"请输入机器人名字:";
    std::cin >> robotname;
    Robot robot1(robotname);    
    while(true)
    {
        int i;
        // 重新编写菜单字符串
        const std::string menu = "1.添加\n2.执行\n3.显示\n4.退出\n";
        std::cout <<"////////\n";
        std::cout << menu;
        std::cout <<"////////\n";
        std::cin >>i;
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
            break;
        }
        case 3:
        {
            robot1.indicate();
            break;
        }
        case 4:
            return 0; // 退出程序
        default:
            std::cout << "无效的选择，请重新输入。" << std::endl;
        } 
    }
    return 0;
}

