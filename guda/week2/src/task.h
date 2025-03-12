///task.h
#ifndef TASK_H
#define TASK_H
#include<string>


class task{
private:
    int taskID;
    std::string task_description;
    std::string task_status;

public:
    task(int id =-1,std::string desc="");
    ~task();
    void task_done();
    int getID() const;
    std::string get_description() const;
    std::string get_status() const;
    

};
#endif //TASK_H
