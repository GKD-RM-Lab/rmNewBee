#include<string>
#include"task.hpp"
class robot{
    public:
    std::string NAME;
    int LIST;
    task newtask[100];
    robot(std::string name):NAME(name),LIST(0){
        for(int i=0;i<100;i++){
            newtask[i]=task();
        }
    }
    ~robot();
    void zhuangtai();
    void xianshi();
};