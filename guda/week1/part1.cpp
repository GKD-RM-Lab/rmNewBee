/// part 1
#include<iostream>
#include<cmath>
using namespace std; 
void indicate(int n,int x,int i);//定义一个函数来显示位置信息
int main(){    
    int x=0,y=0;
    int direction=0;//设置初始位置与方向
    char godirection;   
    while(true){
        int distance=0;
        cin >> godirection;//接收方向的指令
        if(godirection == 'w'){
            cin >>distance;//前进距离
            if(direction == 0){
                y+=distance;
            }
            else if(direction == 90){
                x+=distance;
            }
            else if(direction == 180){
                y-=distance;
            }
            else if(direction == 270){
                x-=distance;
            }       
        }
        if(godirection == 's'){
            cin >>distance;//后退距离
            if(direction == 0){
                y -= distance;
            }
            else if(direction == 90){
                x -= distance;
            }
            else if(direction == 180){
                y += distance;
            }
            else if(direction ==270){
                x += distance;
            }
        }
        if(godirection == 'a'){//逆时针旋转
            direction =(direction-90+360)%360;//防止超出360°和度数变为负
        }
        if(godirection == 'd'){//顺时针旋转
            direction = (direction+90)%360;//防止超出360°
        }
        indicate(x,y,direction);
    }
    return 0;
}
void indicate(int n,int x,int i){
    cout <<"位置：(" <<n <<"," <<x <<")" <<",方向:";
    if(i == 0){
        cout <<"上" <<endl;
    }
    else if(i == 90){
        cout <<"右" <<endl;
    }
    else if(i == 180){
        cout <<"下" <<endl;
    }
    else if(i == 270){
        cout <<"左" <<endl;
    }
}