#include "stdafx.h"
#include "simul.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#define PI 3.1415926535f
using namespace std;

/*
  2018-08-20
  <Type>
  Ÿ�� ����ȭ - �������� ���
  �� Ÿ�Ժ� Location, vel �� ���ѻ��� ����(�ѱ۹���)
  �ùķ��̼��� Ÿ�� �������� / �������� ����
  Target_Sim�� �����ɶ�, Ÿ�Կ� �´� vel ���� �����ǰ���
*/

Target_Sim::Target_Sim(int id, Type type, Rect rect) {
	int rand_x = rand() % (rect.x2 - rect.x1) + rect.x1;
	int rand_y = rand() % (rect.y2 - rect.y1) + rect.y1;
	int rand_vel = rand();
	int rand_dir = rand() % 90;

	/*Ÿ�Ժ��� �ٸ��� �����ؾ� �ϴ� �� : �ӵ�, ���� ���� �Ӽ��� */
	if (type.a == 0)
		type.a = rand() % 3 + 1;
	if (type.b == 0)
		type.b = rand() % 3 + 1;
	if (type.a == 3)
		type.b = 1;

	int typeval = type.a * 10 + type.b;
	switch (typeval) {
	case 11:  //airliner
		data.max_vel = 194; 
		data.changeable_vel = 19; 
		data.changeable_dir = 10;
		data.little_dir = 1; 
		data.dir_timetohold = 5;
		break;
	case 12: //helicopter
		data.max_vel = 55; 
		data.changeable_vel = 5; 
		data.changeable_dir = 70;
		data.little_dir = 7; 
		data.dir_timetohold = 5;
		break;
	case 13: //fighter
		data.max_vel = 305; 
		data.changeable_vel = 31; 
		data.changeable_dir = 120;
		data.little_dir = 12; 
		data.dir_timetohold = 2;
		break;
	case 21: //fishingboat
		data.max_vel = 8; 
		data.changeable_vel = 1; 
		data.changeable_dir = 3;
		data.little_dir = 1; 
		data.dir_timetohold = 3;
		break;
	case 22: //cruise
		data.max_vel = 14; data.changeable_vel = 1; data.changeable_dir = 10;
		data.little_dir = 1; data.dir_timetohold = 5;
		break;
	case 23: //surface
		data.max_vel = 28; data.changeable_vel = 2; data.changeable_dir = 30;
		data.little_dir = 3; data.dir_timetohold = 3;
		break;
	case 31: //submarine
		data.max_vel = 14; data.changeable_vel = 1; data.changeable_dir = 10;
		data.little_dir = 1; data.dir_timetohold = 3;
		break;
	default:
		break;
	}

	data.id = this->id = id;
	data.type = this->type = type;
	data.time = getCurrentTime();
	data.loc.x = rand_x;
	data.loc.y = rand_y;
	if (data.type.a == 1) data.loc.z = 3;
	else if (data.type.a == 2) data.loc.z = 0;
	else data.loc.z = -2;
	data.vel = rand_vel % (data.max_vel / 2) + data.max_vel / 2;

	data.moving = (quadrant)(rand() % 4);
	data.dir = rand_dir + (int)data.moving * 90;
	data.dir_timetohold = 0;
}

/* ������ġ (x,y)���� dir �������� vel �ӷ¸�ŭ �̵��� �� ��ġ (x', y')�� ������Ʈ�Ѵ� */
void Target_Sim::CalcLoc(int x, int y, float vel, float dir) {
	float rad = dir / 180.0f * PI;
	//(vel, 0) �� dir��ŭ ȸ����ȯ  
	float fx = x + cos(rad)*vel - sin(rad) * 0;
	float fy = y + sin(rad)*vel + cos(rad) * 0;
	int newx = floor(fx + 0.5);
	int newy = floor(fy + 0.5);
	//cout << newx << " " << newy << endl;
	data.loc.x = newx;
	data.loc.y = newy;
	CalcLoc_z();
}

void Target_Sim::CalcLoc_z() {
	if (data.type.a == 1) {
		data.loc.z += rand() % 3 - 1; // z�� +- 1 ���������� ����
		if (data.loc.z < 1) data.loc.z = 1;
		if (data.type.b == 1 && data.loc.z > 10) data.loc.z = 10; // 1<= z <=10
		else if (data.type.b == 2 && data.loc.z > 5) data.loc.z = 5; // 1 <= z <= 5
		else if (data.type.b == 3 && data.loc.z > 20) data.loc.z = 20; // 1 <= z <= 20

	}
	else if (data.type.a == 3) {
		data.loc.z += rand() % 3 - 1; // z�� +- 1 ���������� ����
		if (data.loc.z < -5) data.loc.z = -5;
		else if (data.loc.z > -2) data.loc.z = -2;
	}
}

/*
  < Update ���� >
  1. vel
  ���� �ӵ��� ����Ͽ�, �ѹ��� Ÿ�Ժ� �ְ�ӵ��� 10% ����(changeable_vel)�� �����ǵ�����
  �ӵ��� 0���Ϸ� �������ų�, Ÿ�Ժ� �ְ�(max_vel)�� �Ѵ� ��� ó��

  2. dir
  ���� ������ ����Ͽ�, �ѹ��� ���� ������ ����(changeable_dir)�� �����ǵ�����
  �׷��� ���� ��ȯ�� ���Ӿ��� �Ͼ ���� ���� ������
  dir���� �ð�����(dir_timetohold)�� �ξ�, �� �ð��������� �ִ뺯������ 10%(little_dir)�� �����ǵ�����
  �ǹ̾��� �����̴� ǥ���� �����ϱ� ����, �� ǥ���� ������ �������(moving)�� ���´�
  quadrant�� ��и� ���� ����, ����, ����, �ϵ�, �ϼ� �� �������θ� �̵��ϵ��� ��

  3. Loc
  ��ǥ��鿡�� ������ x,y���� ���� ������ vel, dir �� �°� �̵��� ��ǥ ��� (CalcLoc)
  z��ǥ�� +- 1 ���������� ����, ����Ÿ�� ���� (CalcLoc_z)
*/

void Target_Sim::Update(Time_t time) {

	if (time < data.time)
		return;

	data.time = time;

	/* vel update */
	(data.vel) += rand() % (2 * data.changeable_vel + 1) - data.changeable_vel;
	if (data.vel <= 0) data.vel = 1;
	if (data.vel > data.max_vel) data.vel = data.max_vel;

	/* dir update */
	if (data.dir_holingtime < data.dir_timetohold) {
		data.dir += rand() % (2 * data.little_dir + 1) - data.little_dir;
		data.dir_holingtime++;
	}
	else {
		data.dir += rand() % (2 * data.changeable_dir + 1) - data.changeable_dir;
		data.dir_holingtime = 0;
	}
	if (data.dir < (int)data.moving * 90) data.dir = (int)data.moving * 90;
	else if (data.dir > (int)data.moving * 90 + 90) data.dir = (int)data.moving * 90 + 90;

	CalcLoc(data.loc.x, data.loc.y, data.vel, data.dir);
}

Data Target_Sim::getData() { return data; }
Type Target_Sim::getType() { return type; }


Simulator::Simulator(queue<Data> * q, mutex * q_sem) {
	running = false;
	this->q = q;
	this->q_sem = q_sem;
	time = getCurrentTime();
	target_cnt = 0;
	target_type_map.emplace("airliner", 0);
	target_type_map.emplace("helicopter", 0);
	target_type_map.emplace("fighter", 0);
	target_type_map.emplace("fishingboat", 0);
	target_type_map.emplace("cruise", 0);
	target_type_map.emplace("surface", 0);
	target_type_map.emplace("submarine", 0);
	target_type_map.emplace("undefined", 0);
}

int Simulator::Add(Type type, int add_num, Rect rect) {
	// ( �߰��� ���� + ���� target ���� ) �� MAX�� ���� �ʵ���
	target_list_mtx.lock();
	add_num = (target_list.size() + add_num <= TARGET_MAX_CNT) ? add_num : TARGET_MAX_CNT - target_list.size();

	for (int i = 0; i < add_num; i++) {
		Target_Sim * target = new Target_Sim(target_cnt + i, type, rect);
		target_type_map.at(getTypeName(target->getType())) += 1;
		target_list.emplace_back(target);
	}
	target_cnt += add_num;
	target_list_mtx.unlock();
	return target_cnt;
}

bool Simulator::PushQueue() {
	if (q->size() + target_list.size() <= QUEUE_MAX_SIZE) {
		q_sem->lock(); // ť ������ ȹ��
		for (auto target : target_list)
			q->push(target->getData());
		q_sem->unlock(); // ť ������ ������
		return true;
	}
	return false;
}

void Simulator::start() {
	if (running == false) {
		running = true;
		sim_thread = thread([this]() {
			while (this->running) {
				Sleep(1000);
				this->time = getCurrentTime();
				target_list_mtx.lock();
				for (auto target : this->target_list)
					target->Update(this->time);
				while (!PushQueue());
				target_list_mtx.unlock();
			}
		});
	}
}

void Simulator::stop() {
	if (running) {
		running = false;
		sim_thread.join();
	}
}
void Simulator::clear() {
	stop();
	for (auto target : target_list)
		delete target;
	target_list.clear();
	for (auto& p : target_type_map) 
		p.second = 0;
	target_cnt = 0;
}
string getTypeName(Type type) {
	int typeval = type.a * 10 + type.b;
	if (typeval == 11)
		return "airliner";
	else if (typeval == 12)
		return "helicopter";
	else if (typeval == 13)
		return "fighter";
	else if (typeval == 21)
		return "fishingboat";
	else if (typeval == 22)
		return "cruise";
	else if (typeval == 23)
		return "surface";
	else if (typeval == 31)
		return "submarine";
	else
		return "undefined";
}
Type getType(string type_name) {
	if (type_name == "airliner")
		return { 1, 1 };
	else if (type_name == "helicopter")
		return { 1, 2 };
	else if (type_name == "fighter")
		return { 1, 3 };
	else if (type_name == "fishingboat")
		return { 2, 1 };
	else if (type_name == "cruise")
		return { 2, 2 };
	else if (type_name == "surface")
		return { 2, 3 };
	else if (type_name == "submarine")
		return { 3, 1 };
	else
		return { 0, 0 };
}
