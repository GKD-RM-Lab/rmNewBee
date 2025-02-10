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
    int getID() const;
    std::string getDescription() const;
    std::string getStatus() const;
};

#endif // TASK_H
