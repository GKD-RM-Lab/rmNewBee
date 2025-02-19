#ifndef TASK_H
#define TASK_H

#include <string>

class Task
{
private:
    int taskID;
    std::string description;
    std::string status;

public:
    Task(int id = -1, std::string desc = "");
    void execute();
    int getID()  ;
    std::string getDescription()  ;
    std::string getStatus()  ;
};

#endif // TASK_H
