#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x = 0, y = 0;  // 初始位置
    int direction = 0; // 初始方向为上（0°）

    int enemyX[100], enemyY[100]; // 保存敌人位置
    int enemyCount = 0;           // 敌人数量

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
        else if (command == 'x')
        { // 新增敌人
            int enemyXPos, enemyYPos;
            cin >> enemyXPos >> enemyYPos;
            enemyX[enemyCount] = enemyXPos;
            enemyY[enemyCount] = enemyYPos;
            enemyCount++;

            // 计算最近的敌人
            int minDist = 1000000;
            int nearestEnemyIndex = -1;
            for (int i = 0; i < enemyCount; i++)
            {
                int dist = abs(x - enemyX[i]) + abs(y - enemyY[i]);
                if (dist < minDist)
                {
                    minDist = dist;
                    nearestEnemyIndex = i;
                }
            }

            // 输出最近敌人
            int targetX = enemyX[nearestEnemyIndex];
            int targetY = enemyY[nearestEnemyIndex];

            cout << "最近敌人位置: (" << targetX << ", " << targetY << "), 所需控制操作: [";

            // 输出控制操作
            // step是要往前走多少步能和敌人在同一行或列
            // right是敌人在右边多少格
            int step;
            int right;
            if (direction == 0)
            {
                step = targetY - y;
                right = targetX - x;
            }
            else if (direction == 90)
            {
                step = targetX - x;
                right = y - targetY;
            }
            else if (direction == 180)
            {
                step = y - targetY;
                right = x - targetX;
            }
            else
            {
                step = x - targetX;
                right = targetY - y;
            }

            if (right != 0)
            {
                if (step > 0)
                    cout << "w " << step << ',';
                else if (step < 0)
                    cout << "s " << -step << ',';
            }

            if (right > 0)
                cout << "d";
            else if (right < 0)
                cout << "a";
            else
            {
                if (step < 0)
                    cout << "d,d";
            }
            cout << "]" << endl;
            continue;
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
