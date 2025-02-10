#include "task.h"

Task::Task(int id, std::string desc) : taskID(id), description(desc), status("´ıÖ´ĞĞ") {}

void Task::execute()
{
    status = "ÒÑÖ´ĞĞ";
}

int Task::getID() const
{
    return taskID;
}

std::string Task::getDescription() const
{
    return description;
}

std::string Task::getStatus() const
{
    return status;
}
