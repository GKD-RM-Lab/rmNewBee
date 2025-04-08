#pragma once
#include <string>
class task{
    private:
    int ID;
    std::string DESCRIPTION;
    std::string STATUS;
    public:
    task(int id=0,const std::string& description=" ");
    void execute();
    int getID() const;
    std::string getdescription() const;
    std::string getstatus() const;
} ;