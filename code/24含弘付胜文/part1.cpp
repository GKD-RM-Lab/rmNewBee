#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int x = 0, y = 0;
int flag = 0;//0s1z2x3y
void rotate(char f){
    if(f == 'a'){
        flag--;//逆时
    }
    else if(f == 'd'){
        flag++;//瞬时
    }
    while(flag < 0){
        flag += 4;
    }
    if(flag >= 0){
        flag %= 4;
    }
}
void move(char fob, int dis){
    if(fob == 'w'){
        if(flag == 0){
            y += dis;
        }
        if(flag == 1){
            x += dis;
        }
        if(flag == 2){
            y -= dis;
        }
        if(flag == 3){
            x -= dis;
        }
    }
    if(fob == 's'){
        if(flag == 0){
            y -= dis;
        }
        if(flag == 1){
            x -= dis;
        }
        if(flag == 2){
            y += dis;
        }
        if(flag == 3){
            x += dis;
        }
    }
}
void speak(){
    cout << "位置:(" << x << ", " << y << "), 方向：";
    if(flag == 0){
        cout << "上";
    }
    if(flag == 1){
        cout << "右";
    }
    if(flag == 2){
        cout << "下";
    }
    if(flag == 3){
        cout << "左";
    }
    cout << endl;
}
int main(){
    char f;
    int dis;
    while(true){
        cin >> f;
        if(f == 'd' || f == 'a'){
            rotate(f);
        }
        else if(f == 'w' || f == 's'){
            cin >> dis;
            move(f, dis);
        }
        speak();
    }
    return 0;
}