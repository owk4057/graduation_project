#pragma once
#include "common.h"
#include "mutex"
#include <thread>


class Target_Sim {
private:
	int id;
	Type type;
	Data data;
public:
	Target_Sim(int id, Type type, Rect rect);
	void CalcLoc(int x, int y, float vel, float dir); // 추가
	void CalcLoc_z(); //추가2
	void Update(Time_t time);
	Data getData();
	Type getType();
};

class Simulator {
private:
	static const int TARGET_MAX_CNT = 10000;
	static const int QUEUE_MAX_SIZE = 1000000;
	queue<Data> * q;
	mutex * q_sem;
	list<Target_Sim*> target_list;
	int target_cnt;
	Time_t time;
	bool running;
	thread sim_thread;
	mutex target_list_mtx;

public:
	Simulator(queue<Data> * q, mutex * q_sem);
	int Add(Type type, int target_num, Rect rect);
	bool PushQueue();
	void start(); // 수정
	void stop();
	void clear();
	map<string, int> target_type_map;
};

string getTypeName(Type type);
Type getType(string type_name);
