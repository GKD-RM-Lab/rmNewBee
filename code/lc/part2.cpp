#include<iostream>

using namespace std;

void move(char command, int distance, int &position_x, int &position_y, int &direction);

void rotate(char command, int &direction);

void output_self(int position_x, int position_y, int direction);

void output_enemy(int enemy_pos_x[], int enemy_pos_y[], int enemy_number, int position_x, int position_y, int direction);

void enemy_generate(int enemy_pos_x[], int enemy_pos_y[], int &enemy_number);

int main()
{
    int direction = 0,
        distance = 0,
        position_x = 0,
        position_y = 0,
        enemy_number = 0;

    int enemy_pos_x[10] = {0},
        enemy_pos_y[10] = {0};
       
    char command;

    while (true)
    {
        cin >> command;

        if (command == 'w' || command == 's')
        {
            move(command, distance, position_x, position_y, direction);

            output_self(position_x, position_y, direction);

        }
        else if (command == 'a' || command == 'd')
        {
            rotate(command, direction);

            output_self(position_x, position_y, direction);

        }
        else if (command == 'x')
        {
            enemy_generate(enemy_pos_x, enemy_pos_y, enemy_number);

            output_enemy(enemy_pos_x, enemy_pos_y, enemy_number, position_x, position_y, direction);

        }

    }
       
    return 0;

}

void move(char command, int distance, int &position_x, int &position_y, int &direction)
{
    if (command == 'w')
    {
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
    if (command == 'a')
    {
        direction = (direction - 90 + 360) % 360;
    }
    else if (command == 'd')
    {
        direction = (direction + 90 + 360) % 360;
    }

    return;

}

void output_self(int position_x, int position_y, int direction)
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

void enemy_generate(int enemy_pos_x[], int enemy_pos_y[], int &enemy_number)
{
    cin >> enemy_pos_x[enemy_number] >> enemy_pos_y[enemy_number];

    enemy_number++;

    return;

}

void output_enemy(int enemy_pos_x[], int enemy_pos_y[], int enemy_number, int position_x, int position_y, int direction)
{
    int temp = 0;
    int enemy_distance;  
    
    enemy_distance = abs(position_x - enemy_pos_x[0]) + abs(position_y - enemy_pos_y[0]);

    for (int i = 0; i < enemy_number; i++)
    {
        if(abs(position_x - enemy_pos_x[i]) + abs(position_y - enemy_pos_y[i]) < enemy_distance)
        {
            enemy_distance = abs(position_x - enemy_pos_x[i]) + abs(position_y - enemy_pos_y[i]);

            temp = i;

        }

        if (enemy_distance == 0)
        {
            cout << "最近敌人位置:(" << enemy_pos_x[i] <<","<< enemy_pos_y[i] << "),操作: []" << endl;

            return;

        }

    }

    cout << "最近敌人位置:(" << enemy_pos_x[temp] <<","<< enemy_pos_y[temp] << "),操作: ";

    int step;
    int right;

    if (direction == 0)
    {
        step = enemy_pos_y[temp] - position_y;
        right = enemy_pos_x[temp] - position_x;

    }
    else if (direction == 90)
    {
        step = enemy_pos_x[temp] - position_x;
        right = position_y - enemy_pos_y[temp];
    
    }
    else if (direction == 180)
    {
        step = position_y - enemy_pos_y[temp];
        right = position_x - enemy_pos_x[temp];

    }
    else
    {
        step = position_x - enemy_pos_x[temp];
        right = enemy_pos_y[temp] - position_y;

    }

    if (right != 0)
    {
        if (step > 0)
            cout << "w " << step << ',';
        else if (step < 0)
            cout << "s " << -step << ',';

    }

    if (right > 0)
    {
        cout << "d";
    }
    else if (right < 0)
    {
        cout << "a";
    }
    else
    {
        if (step < 0)
            cout << "d,d";

    }
        
    cout << "]" << endl;

    return;
    
}