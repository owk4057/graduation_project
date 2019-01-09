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
  타입 세분화 - 착수보고서 기반
  각 타입별 Location, vel 의 제한사항 설정(한글문서)
  시뮬레이션할 타입 직접설정 / 랜덤설정 가능
  Target_Sim이 생성될때, 타입에 맞는 vel 값이 설정되게함
*/

Target_Sim::Target_Sim(int id, Type type, Rect rect) {
	int rand_x = rand() % (rect.x2 - rect.x1) + rect.x1;
	int rand_y = rand() % (rect.y2 - rect.y1) + rect.y1;
	int rand_vel = rand();
	int rand_dir = rand() % 90;

	/*타입별로 다르게 지정해야 하는 것 : 속도, 방향 관련 속성들 */
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

/* 현재위치 (x,y)에서 dir 방향으로 vel 속력만큼 이동한 새 위치 (x', y')로 업데이트한다 */
void Target_Sim::CalcLoc(int x, int y, float vel, float dir) {
	float rad = dir / 180.0f * PI;
	//(vel, 0) 을 dir만큼 회전변환  
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
		data.loc.z += rand() % 3 - 1; // z는 +- 1 범위에서만 변동
		if (data.loc.z < 1) data.loc.z = 1;
		if (data.type.b == 1 && data.loc.z > 10) data.loc.z = 10; // 1<= z <=10
		else if (data.type.b == 2 && data.loc.z > 5) data.loc.z = 5; // 1 <= z <= 5
		else if (data.type.b == 3 && data.loc.z > 20) data.loc.z = 20; // 1 <= z <= 20

	}
	else if (data.type.a == 3) {
		data.loc.z += rand() % 3 - 1; // z는 +- 1 범위에서만 변동
		if (data.loc.z < -5) data.loc.z = -5;
		else if (data.loc.z > -2) data.loc.z = -2;
	}
}

/*
  < Update 관련 >
  1. vel
  현재 속도에 기반하여, 한번에 타입별 최고속도의 10% 정도(changeable_vel)만 변동되도록함
  속도가 0이하로 떨어지거나, 타입별 최고값(max_vel)을 넘는 경우 처리

  2. dir
  현재 각도에 기반하여, 한번에 일정 정도의 각도(changeable_dir)만 변동되도록함
  그러나 방향 전환이 끊임없이 일어날 수는 없기 때문에
  dir변동 시간제한(dir_timetohold)을 두어, 그 시간내에서는 최대변동각의 10%(little_dir)만 변동되도록함
  의미없이 움직이는 표적을 방지하기 위해, 각 표적은 잠정적 진행방향(moving)을 갖는다
  quadrant의 사분면 값에 따라, 남동, 남서, 북동, 북서 쪽 방향으로만 이동하도록 함

  3. Loc
  좌표평면에서 기존의 x,y값에 대해 구해진 vel, dir 에 맞게 이동한 좌표 계산 (CalcLoc)
  z좌표는 +- 1 범위에서만 변동, 수상타입 제외 (CalcLoc_z)
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
	// ( 추가할 개수 + 현재 target 개수 ) 가 MAX를 넘지 않도록
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
		q_sem->lock(); // 큐 세마포 획득
		for (auto target : target_list)
			q->push(target->getData());
		q_sem->unlock(); // 큐 세마포 릴리즈
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
