/// part 1
#include<iostream>
#include<cmath>
using namespace std; 
void indicate(int n,int x,int i);//����һ����������ʾλ����Ϣ
int main(){    
    int x=0,y=0;
    int direction=0;//���ó�ʼλ���뷽��
    char godirection;   
    while(true){
        int distance=0;
        cin >> godirection;//���շ����ָ��
        if(godirection == 'w'){
            cin >>distance;//ǰ������
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
            cin >>distance;//���˾���
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
        if(godirection == 'a'){//��ʱ����ת
            direction =(direction-90+360)%360;//��ֹ����360��Ͷ�����Ϊ��
        }
        if(godirection == 'd'){//˳ʱ����ת
            direction = (direction+90)%360;//��ֹ����360��
        }
        indicate(x,y,direction);
    }
    return 0;
}
void indicate(int n,int x,int i){
    cout <<"λ�ã�(" <<n <<"," <<x <<")" <<",����:";
    if(i == 0){
        cout <<"��" <<endl;
    }
    else if(i == 90){
        cout <<"��" <<endl;
    }
    else if(i == 180){
        cout <<"��" <<endl;
    }
    else if(i == 270){
        cout <<"��" <<endl;
    }
}