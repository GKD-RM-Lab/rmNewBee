#include "task.hpp"

Task::Task(int id, std::string description, int importance){
    taskid = id;
    taskdescrtiption = description;
    taskimportance = importance;
    taskstatus = "未执行";
}

void Task::execute() const{
    taskstatus = "已执行";
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
