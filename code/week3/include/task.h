#pragma once

#include <string>

class Task {

private:
    int taskID;
    std::string description;
    bool executed;

public:
    Task(int id = -1, const std::string &desc = "");

    void execute();

    int getID() const;

    std::string getDescription() const;

    bool isExecuted() const;
};
