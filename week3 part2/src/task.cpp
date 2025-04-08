#include "task.hpp"
task::task(int id,const std::string& description,int X):ID(id),DESCRIPTION(description),STATUS("待执行"),x(X){};
void task::execute() const{
    STATUS="已执行";
}
int task::getID() const{
    return ID;
}
std::string task::getdescription() const{
    return DESCRIPTION;
}
std::string task::getstatus() const{
    return STATUS;
} 