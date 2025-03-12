#include"task.h"
#include<Windows.h>

void sleep_ms(int val) {
	std::this_thread::sleep_for(std::chrono::milliseconds(val));
}

taskBase::taskBase(int key, std::atomic<int>* p1, std::atomic<int>* p2) :key(key), p1(p1), p2(p2){}
void taskBase::start() {
	monitor = std::thread(&taskBase::run, this);
}
void taskBase::stop() {
	Finish = true;
	monitor.join();
}
void task1::callback(int msg)
{
	*p1 = msg;
}
void task1::run()
{
	while (!Finish)
	{
		int val = p1->exchange(0);
		if (val != 0)
		{
			*p2 = val + 1;
			printf("write : 1-%d %d\n", key, val+1);
		}
		sleep_ms(1);
	}
	
}
task2::task2(int key, std::atomic<int>* p1, std::atomic<int>* p2)
{
	this->key = key;
	this->p1 = p1;
	this->p2 = p2;
	

}
void task2::run()
{
	
	while (!Finish) {
		int val = p1->exchange(0);
		if (val != 0)
		{
			*p2 = val * k;
			printf("write : 2-%d %d\n", key, val*k);
		}
		sleep_ms(1);
		
	}
	
}
void task2::callback(int msg)
{
	k = msg;
	*p1 = 1;
}
task3::task3(int key, std::atomic<int>* p1, std::atomic<int>* p2)
{
	this->key = key;
	this->p1 = p1;
	this->p2 = p2;
	this->t = 0;
}
void task3::callback(int msg)
{
	*p1 = msg;
}
void task3::run()
{
	
	while (!Finish) {
		t = p1->exchange(0);
		if (t != 0)
		{
			*p2 = t;
			printf("write : 3-%d %d\n", key, t);
			sleep_ms(4);   //将延迟值修改为4，以便可以每次获取到task3两次改变p2输出的Out
			*p2 = t + 1;
			printf("write : 3-%d %d\n", key, t+1);
		}
		sleep_ms(1);
	}
	 


	
	
}