#include "task.h"

Task::Task(int id, std::string desc) : taskID(id), description(desc), status("��ִ��") {}

void Task::execute()
{
    status = "��ִ��";
}

int Task::getID()  
{
    return taskID;
}

std::string Task::getDescription()  
{
    return description;
}

std::string Task::getStatus()  
{
    return status;
}
