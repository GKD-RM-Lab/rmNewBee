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
            m_direction = (m_direction - 90 + 360)%360;
            break;
        default:
            std::cout << "输入错误" << std::endl;
            break;
    }
}

void Robot::location_direction_outpot()
{
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
    char operate;
    int number;
    Robot robot;

    while (true)
    {
        std::cin >> operate;
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