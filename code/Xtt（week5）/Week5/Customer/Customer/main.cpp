#include<iostream>
#include"Customer.h"


int main()
{
    Customer customer;
    std::vector<std::thread> Customers;
    srand(std::time(0));
   
    for (int i = 0; i <  std::rand()%10; ++i) {
        
        
        
        Customers.emplace_back(&Customer::Order, &customer);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
    }

   
    for (auto& thread : Customers) {
        thread.join();
    }
    return 0;
}