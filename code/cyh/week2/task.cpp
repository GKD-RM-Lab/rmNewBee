#include "task.hpp"

Task::Task(int id, std::string description){
    TaskID = id;
    TaskDescription = description;
    TaskStatus = "δִ��";
}

void Task::execute(){
    TaskStatus = "��ִ��";
}

int Task::getTaskID(){
    return TaskID;
}

std::string Task::getTaskDescription(){
    return TaskDescription;
}

std::string Task::getTaskStatus(){
    return TaskStatus;
}