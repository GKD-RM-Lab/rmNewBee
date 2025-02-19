#include "task.hpp"

Task::Task(int id, std::string description, int importance){
    taskid = id;
    taskdescrtiption = description;
    taskimportance = importance;
    taskstatus = "δִ��";
}

void Task::execute() const{
    taskstatus = "��ִ��";
}

int Task::getTaskID() const{
    return taskid;
}

std::string Task::getTaskDescription() const{
    return taskdescrtiption;
}

std::string Task::getTaskStatus() const{
    return taskstatus;
}

int Task::getTaskImportance(){
    return taskimportance;
}

bool Task::operator<(const Task& other) const {
    return this->taskimportance > other.taskimportance;
}
