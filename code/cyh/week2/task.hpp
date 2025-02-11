#ifndef TASK_HPP
#define TASK_HPP

#include <string>

class Task{
    private:
        int TaskID;
        std::string TaskDescription;
        std::string TaskStatus;
    public:
        Task(int id, std::string description);
        void execute();
        int getTaskID();
        std::string getTaskDescription();
        std::string getTaskStatus();


};
#endif