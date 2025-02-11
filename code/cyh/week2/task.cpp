#include "task.hpp"

Task::Task(int id, std::string description){
    TaskID = id;
    TaskDescription = description;
    TaskStatus = "Î´Ö´ÐÐ";
}

void Task::execute(){
    TaskStatus = "ÒÑÖ´ÐÐ";
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