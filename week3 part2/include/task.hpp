#pragma once
#include <string>
class task{
    private:
    int ID;
    std::string DESCRIPTION;
    mutable std::string STATUS;
    int x;
    public:
    bool operator<(const task& other)const{
        return x<other.x;
    }
    task(int id=0,const std::string& description=" ",int X=0);
    void execute() const;
    int getID() const;
    std::string getdescription() const;
    std::string getstatus() const;
} ;