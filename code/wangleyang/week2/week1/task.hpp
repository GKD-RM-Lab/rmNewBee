#include <string>
class task{
    public:
    int ID;
    std::string MIAOSHU;
    std::string ZHUANGTAI;
    task(int id=0,std::string miaoshu=" "):ID(id),MIAOSHU(miaoshu),ZHUANGTAI("待执行"){}
    void zhuangtai(){
        ZHUANGTAI="已执行";
    }
} ;