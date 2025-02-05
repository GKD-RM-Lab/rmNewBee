#include <iostream>
#include <string>
#include <cmath>

class Robot
{
private:
    double m_x, m_y;
    int m_direction;
public:
    Robot():m_x(0), m_y(0), m_direction(0) {}
    ~Robot() {}
    void Robot_set(char operate, int number = 0);
    void location_direction_outpot();
};

void Robot::Robot_set(char operate, int number)
{
    //对于s和w，用三角函数求出移动后的坐标。a和d为得出新方向
    switch (operate)
    {   
        case 'w':
            m_x += number*sin(M_PI/180.0*m_direction);
            m_y += number*cos(M_PI/180.0*m_direction);
            break;
        case 's':
            m_x -= number*sin(M_PI/180.0*m_direction);
            m_y -= number*cos(M_PI/180.0*m_direction);
            break;
        case 'd':
            m_direction = (m_direction + 90)%360;
            break;
        case 'a':
            m_direction = (m_direction - 90 + 360)%360; //右转90即左转270
            break;
        default:
            std::cout << "输入错误" << std::endl;
            break;
    }
}

void Robot::location_direction_outpot()
{
    //将角度于方位进行对照，输出访问和坐标
    std::string direction("上");
    if (m_direction == 90)
        direction = "右";
    else if (m_direction == 180)
        direction = "下";
    else if (m_direction == 270)
        direction = "左";

    std::cout << "位置:(" << static_cast<int>(std::round(m_x)) << "," 
              << static_cast<int>(std::round(m_y)) << "),方向:" 
              << direction << std::endl;
}

int main()
{
    char operate; // 定义一个char变量来存储第一个指令
    int number = 0; // 定义int变量来存储移动距离
    Robot robot;

    while (true)
    {
        std::cin >> operate;
        //当char变量为d或a时不进行number的赋值
        if (operate == 'w' || operate == 's')
        {
            std::cin >> number;
            robot.Robot_set(operate, number);
        }
        else
            robot.Robot_set(operate);

        robot.location_direction_outpot();
    }

    return 0;
}