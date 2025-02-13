#include <iostream>
#include <string>
#include "Robot.hpp"
#include "task.hpp"

int main()
{
    std::cout << "输入robot_name：" << std::endl;
    std::string robot_name;
    std::cin >> robot_name;
    Robot robot(robot_name);
    
    while(true)
    {
        std::cout << "输入command：" << std::endl;
        std::string command;
        std::cin >> command;
        if (!command.compare("添加"))
        {
            int id;
            std::string distription;
            std::cin >> id >> distription;
            robot.add_task(id, distription);
        }
        else if (!command.compare("执行"))
            robot.execute_task();
        else if (!command.compare("显示"))
            robot.show_task();
        else if (!command.compare("退出"))
            break;
        else
            std::cout << "输入错误,重新输入" << std::endl;
    }
    return 0;
}