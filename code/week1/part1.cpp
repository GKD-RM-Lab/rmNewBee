#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x = 0, y = 0;  // 初始位置
    int direction = 0; // 初始方向为上（0°）

    char command;
    int distance;
    while (true)
    {
        cin >> command; // 输入命令

        if (command == 'w')
        { // 前进
            cin >> distance;
            if (direction == 0)
            {
                y += distance;
            }
            else if (direction == 90)
            {
                x += distance;
            }
            else if (direction == 180)
            {
                y -= distance;
            }
            else if (direction == 270)
            {
                x -= distance;
            }
        }
        else if (command == 's')
        { // 后退
            cin >> distance;
            if (direction == 0)
            {
                y -= distance;
            }
            else if (direction == 90)
            {
                x -= distance;
            }
            else if (direction == 180)
            {
                y += distance;
            }
            else if (direction == 270)
            {
                x += distance;
            }
        }
        else if (command == 'a')
        { // 逆时针旋转
            direction = (direction - 90 + 360) % 360;
        }
        else if (command == 'd')
        { // 顺时针旋转
            direction = (direction + 90) % 360;
        }
        cout << "位置: (" << x << ", " << y << "), 方向: ";
        if (direction == 0)
        {
            cout << "上" << endl;
        }
        else if (direction == 90)
        {
            cout << "右" << endl;
        }
        else if (direction == 180)
        {
            cout << "下" << endl;
        }
        else if (direction == 270)
        {
            cout << "左" << endl;
        }
    }

    return 0;
}
