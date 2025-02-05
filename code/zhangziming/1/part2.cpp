#include <iostream>
#include <string>
#include <cmath>

struct enemy
{
    double x;
    double y;
    enemy():x(0), y(0) {};
};

class Robot
{
private:
    double m_x, m_y;
    int m_direction;
    enemy *enemy_manage;
public:
    Robot():m_x(0), m_y(0), m_direction(0)
    {
        enemy_manage = new enemy[100];
    }
    ~Robot() {}
    void Robot_set(char operate, int number = 0);
    void location_direction_outpot();
    int search_enemy(double enemy_x, double enemy_y);
    void shoot_enemy(int nearest);
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

int Robot::search_enemy(double enemy_x, double enemy_y)
{
    static int count = 0, nearest = 0;

    if (count < 100)
    {
        enemy_manage[count].x = enemy_x;
        enemy_manage[count].y = enemy_y;
    
        double delta_current = fabs(m_x - enemy_x) + fabs(m_y - enemy_y);
        double delta_min = fabs(m_x - enemy_manage[nearest].x) + fabs(m_y - enemy_manage[nearest].y);
        if (delta_current < delta_min)
            nearest = count;

        count++;
        return nearest;
    }
    else exit(1);
    
}

void Robot::shoot_enemy(int nearest)
{
    std::cout << "最近敌人的位置:(" << static_cast<int>(std::round(enemy_manage[nearest].x)) << "," 
            << static_cast<int>(std::round(enemy_manage[nearest].y)) << "),";

    //求出当前robot正方向的正交标准基表示在初始的坐标系时的过渡矩阵，求逆进行基变换
    double transform_m_x = m_x*cos(M_PI/180.0*m_direction) - m_y*sin(M_PI/180.0*m_direction);
    double transform_m_y = m_x*sin(M_PI/180.0*m_direction) + m_y*cos(M_PI/180.0*m_direction);
    double transform_nearest_x = enemy_manage[nearest].x*cos(M_PI/180.0*m_direction) - enemy_manage[nearest].y*sin(M_PI/180.0*m_direction);
    double transform_nearest_y = enemy_manage[nearest].x*sin(M_PI/180.0*m_direction) + enemy_manage[nearest].y*cos(M_PI/180.0*m_direction);
    std::cout << "所需控制操作:[";
    double delta_x = fabs(transform_m_x-transform_nearest_x);
    double delta_y = fabs(transform_m_y-transform_nearest_y);

    if (delta_x < 1e-9)
    {
        if (transform_m_y > transform_nearest_y)
            std::cout << "d,d"; 
    }
    else
    {
        if (transform_m_y > transform_nearest_y)
            std::cout << "s ";
        else
            std::cout << "w ";
        std::cout << static_cast<int>(std::round(delta_y)) << ",";

        if (transform_m_x > transform_nearest_x)
            std::cout << "a";
        else
            std::cout << "d";
    }
    std::cout << "]" << std::endl; 
}

int main()
{
    Robot robot;
    char operate;
    int number;

    while (true)
    {
        std::cin >> operate;
        if (operate != 'x')
        {
            if (operate == 'w' || operate == 's')
            {
                std::cin >> number;
                robot.Robot_set(operate, number);
            }
            else
                robot.Robot_set(operate);
            robot.location_direction_outpot();
        }
        else
        {
            int nearest = 0;
            double enemy_x = 0, enemy_y = 0;
            std::cin >>enemy_x >>enemy_y;
            nearest = robot.search_enemy(enemy_x, enemy_y);
            robot.shoot_enemy(nearest);
        }
        
    }
    return 0;
}