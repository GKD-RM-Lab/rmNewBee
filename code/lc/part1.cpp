#include<iostream>

using namespace std;

void move(char command, int distance, int &position_x, int &position_y, int &direction);

void rotate(char command, int &direction);

void output(int position_x, int position_y, int direction);

int main()
{
    int direction = 0,
        distance = 0,
        position_x = 0,
        position_y = 0;
       
    char command;

    while (true)
    {
        cin >> command;

        if (command == 'w' || command == 's') 
        {
            move(command, distance, position_x, position_y, direction);

            output(position_x, position_y, direction);

        }
        else if (command == 'a' || command == 'd')
        {
            rotate(command, direction);

            output(position_x, position_y, direction);

        }

    }
       
    return 0;

}

void move(char command, int distance, int &position_x, int &position_y, int &direction)
{
    if (command == 'w') 
        cin >> distance;

        if (direction == 0)
        {
            position_y += distance;
        }
        else if (direction == 90)
        {
            position_x += distance;
        }
        else if (direction == 180)
        {
            position_y -= distance;
        }
        else if (direction == 270)
        {
            position_x -= distance;
        }

    }
    else if (command == 's')
    {
        cin >> distance;

        if (direction == 0)
        {
            position_y -= distance;
        } 
        else if (direction == 90)
        {
            position_x -= distance;
        }
        else if (direction == 180)
        {
            position_y += distance;
        }
        else if (direction == 270)
        {
            position_x += distance;
        }

    }

    return;

}    

void rotate( char command, int &direction)
{
    if (command == 'a') //转向
    {
        direction = (direction - 90 + 360) % 360;
    }
    else if (command == 'd')
    {
        direction = (direction + 90 + 360) % 360;
    }

    return;

}

void output(int position_x, int position_y, int direction) 
{
    cout << "位置:(" << position_x <<","<< position_y << "),方向: ";

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

    return;

}