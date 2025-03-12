#pragma once
#include<atomic>
#include<thread>
class taskBase
{
public:
	taskBase() {};
	taskBase(int key, std::atomic<int>* p1, std::atomic<int>* p2);
	virtual~taskBase() {};
	virtual void callback(int msg)=0;
	virtual void run()=0;
	void start();
	void stop();
public:
	int key;
	std::atomic<int>* p1 = nullptr;
	std::atomic<int>* p2 = nullptr;
	std::thread monitor;
	std::atomic<bool> Finish;
};

class task1 :public taskBase
{
public:
	task1(int key, std::atomic<int>* p1, std::atomic<int>* p2):taskBase(key,p1,p2){}
	void callback(int msg)override;
	void run()override;
};
class task2 :public taskBase
{
public:
	task2(int key, std::atomic<int>* p1, std::atomic<int>* p2);
	void callback(int msg)override;
	void run()override;
private:
	int k = 1;
};
class task3 :public taskBase
{
public:
	task3(int key, std::atomic<int>* p1, std::atomic<int>* p2);
	void callback(int msg)override;
	void run()override;
private:
	int t;

};