#include "task.h"

Task::Task(int id, const std::string &desc) : taskID(id), description(desc), executed(false) {}

void Task::execute() {
    executed = true;
}

int Task::getID() const {
    return taskID;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isExecuted() const {
    return executed;
}
