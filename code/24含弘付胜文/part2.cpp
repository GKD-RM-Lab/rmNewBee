#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<string>
using namespace std;

const int boundary = 200;
vector<vector<int>> map(boundary, vector<int>(boundary, 0));
int x = 0, y = 0, mx, my;
double dist = 100000; // 初始化最近的距离
int flag = 0; // 0s1z2x3y
void rotate(char f) {
    if (f == 'a') {
        flag--; // 逆时针旋转
    }
    else if (f == 'd') {
        flag++; 
    }
    flag = (flag + 4) % 4; 
}
void move(char fob, int dis) {
    switch (fob) {
    case 'w':
        switch (flag) {
        case 0: y += dis; break;
        case 1: x += dis; break;
        case 2: y -= dis; break;
        case 3: x -= dis; break;
        }
        break;
    case 's':
        switch (flag) {
        case 0: y -= dis; break;
        case 1: x -= dis; break;
        case 2: y += dis; break;
        case 3: x += dis; break;
        }
        break;
    }
}
void detect() {
    // 可以将 map[99][99] 当作坐标的原点，那么就是 x + 99 = j，y + 99 = i;
    for (int i = 0; i < boundary; i++) { // 其中 i 代表的是纵坐标，j 代表的是横坐标
        for (int j = 0; j < boundary; j++) {
            if (map[i][j] == 1) {
                double temp = sqrt(pow(abs(j - 99 - x), 2) + pow(abs(i - 99 - y), 2));
                if (temp < dist) {
                    dist = temp;
                    mx = j - 99;
                    my = i - 99;
                }
            }
        }
    }
}

// 输出自身位置和方向的函数
void speakself() {
    cout << "位置:(" << x << ", " << y << "), 方向：";
    switch (flag) {
    case 0: cout << "上"; break;
    case 1: cout << "右"; break;
    case 2: cout << "下"; break;
    case 3: cout << "左"; break;
    }
    cout << endl;
}

// 输出最近敌人位置和所需操作的函数
void speakenemy() {
    // 不要求最少操作那就投机只动 x
    int cha = x - mx, cha2 = y - my;
    vector<string> action(10); // 操作
    int cnt = 0; // 操作数

    if (cha == 0 || cha2 == 0) {
        if (cha == 0) { // 同竖直
            if (cha2 > 0) { // 在下面
                if (flag == 0) {
                    action[cnt++] = "a";
                    action[cnt++] = "a";
                }
                else if (flag == 2) {
                    cout << "最近敌人位置：（" << mx << "," << my << "),";
                    cout << "所需操作:[]" << endl;
                    return;
                }
                else if (flag == 1) { // 向右
                    action[cnt++] = "d";
                }
                else if (flag == 3) {
                    action[cnt++] = "a";
                }
            }
            else if (cha2 < 0) {
                if (flag == 2) {
                    action[cnt++] = "a";
                    action[cnt++] = "a";
                }
                else if (flag == 0) {
                    cout << "最近敌人位置：（" << mx << "," << my << "),";
                    cout << "所需操作：[]" << endl;
                    return;
                }
                else if (flag == 3) { // 向右
                    action[cnt++] = "d";
                }
                else if (flag == 1) {
                    action[cnt++] = "a";
                }
            }
        }
        else if (cha2 == 0) { // 同水平
            if (cha > 0) { // 在左面
                if (flag == 1) {
                    action[cnt++] = "a";
                    action[cnt++] = "a";
                }
                else if (flag == 3) {
                    cout << "最近敌人位置：（" << mx << "," << my << "),";
                    cout << "所需操作:[]" << endl;
                    return;
                }
                else if (flag == 2) {
                    action[cnt++] = "d";
                }
                else if (flag == 0) {
                    action[cnt++] = "a";
                }
            }
            else if (cha < 0) { // 右
                if (flag == 3) {
                    action[cnt++] = "a";
                    action[cnt++] = "a";
                }
                else if (flag == 1) {
                    cout << "最近敌人位置：（" << mx << "," << my << "),";
                    cout << "所需操作：[]" << endl;
                    return;
                }
                else if (flag == 0) {
                    action[cnt++] = "d";
                }
                else if (flag == 2) {
                    action[cnt++] = "a";
                }
            }
        }
    }
    else {
        if (flag == 0 || flag == 2) {
            action[cnt++] = "a"; // 是逆时针
            if (flag == 0) { // 方向向左
                if (cha > 0) {
                    string tmp = "w " + to_string(cha);
                    action[cnt++] = tmp;
                }
                else if (cha < 0) {
                    string tmp = "s " + to_string(-cha);
                    action[cnt++] = tmp;
                }
                if (cha2 > 0) { // 在下面
                    action[cnt++] = "a";
                }
                else if (cha2 < 0) {
                    action[cnt++] = "d";
                }
            }
            else if (flag == 2) { // 方向向右
                if (cha > 0) {
                    string tmp = "s " + to_string(cha);
                    action[cnt++] = tmp;
                }
                else if (cha < 0) {
                    string tmp = "w " + to_string(-cha);
                    action[cnt++] = tmp;
                }
                if (cha2 > 0) { // 在下面
                    action[cnt++] = "d";
                }
                else if (cha2 < 0) {
                    action[cnt++] = "a";
                }
            }
        }
        else if (flag == 1 || flag == 3) {
            if (flag == 1) {
                if (cha > 0) {
                    string tmp = "s " + to_string(cha);
                    action[cnt++] = tmp;
                }
                else if (cha < 0) {
                    string tmp = "w " + to_string(-cha);
                    action[cnt++] = tmp;
                }
                if (cha2 > 0) { // 在下面
                    action[cnt++] = "d";
                }
                else if (cha2 < 0) {
                    action[cnt++] = "a";
                }
            }
            else if (flag == 3) {
                if (cha > 0) {
                    string tmp = "w " + to_string(cha);
                    action[cnt++] = tmp;
                }
                else if (cha < 0) {
                    string tmp = "s " + to_string(-cha);
                    action[cnt++] = tmp;
                }
                if (cha2 > 0) { // 在下面
                    action[cnt++] = "a";
                }
                else if (cha2 < 0) {
                    action[cnt++] = "d";
                }
            }
        }
    }

    cout << "最近敌人位置：（" << mx << "," << my << "),";
    cout << "所需操作[";
    for (int i = 0; i < cnt; i++) {
        cout << action[i];
        if (i != cnt - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    char f;
    int dis;
    while (true) {
        cin >> f;
        if (f != 'x') {
            if (f == 'd' || f == 'a') {
                rotate(f);
            }
            else if (f == 'w' || f == 's') {
                cin >> dis;
                move(f, dis);
            }
            speakself();
        }
        else if (f == 'x') {
            int ex, ey;
            cin >> ex >> ey;
            map[ey + 99][ex + 99] = 1;
            dist = 100000; // 每次检测前重置最近距离
            detect();
            speakenemy();
        }
    }
    return 0;
}