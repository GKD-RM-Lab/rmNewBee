#ifndef TASK_HPP
#define TASK_HPP

#include <string>

class Task{
    private:
        int taskid;
        mutable std::string taskdescrtiption;
        mutable std::string taskstatus;
        mutable int taskimportance;
    public:
        Task(int id, std::string description, int importance);
        void execute() const;
        int getTaskID() const;
        std::string getTaskDescription() const;
        std::string getTaskStatus() const;
        int getTaskImportance();
        bool operator<(const Task& other) const;

};


#endif