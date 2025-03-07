#include "task_manager.hpp"

int main(){
    TaskManager taskmanager;
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}
