#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int x = 0, y = 0;  // ��ʼλ��
    int direction = 0; // ��ʼ����Ϊ�ϣ�0�㣩

    char command;
    int distance;
    while (true)
    {
        cin >> command; // ��������

        if (command == 'w')
        { // ǰ��
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
        { // ����
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
        { // ��ʱ����ת
            direction = (direction - 90 + 360) % 360;
        }
        else if (command == 'd')
        { // ˳ʱ����ת
            direction = (direction + 90) % 360;
        }
        cout << "λ��: (" << x << ", " << y << "), ����: ";
        if (direction == 0)
        {
            cout << "��" << endl;
        }
        else if (direction == 90)
        {
            cout << "��" << endl;
        }
        else if (direction == 180)
        {
            cout << "��" << endl;
        }
        else if (direction == 270)
        {
            cout << "��" << endl;
        }
    }

    return 0;
}
