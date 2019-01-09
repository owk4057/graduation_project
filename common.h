#pragma once
//#include "stdafx.h"
#include "MyTime.h"
#include <string>
#include <queue>
#include <map>
#include <Windows.h>

//юс╫ц
#define TRACK_LEN 5
#define TARGET_MAX_NUM 100
#define MAX_X 800
#define MAX_Y 500
#define DRAW_LEN 3

using namespace std;

typedef struct __Rect {
	int x1;
	int y1;
	int x2;
	int y2;
	__Rect(int x1, int y1, int x2, int y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
} Rect;

typedef struct __Location {
	int x;
	int y;
	int z;
} Location;

typedef struct __Type {
	int a;
	int b;
} Type;


enum quadrant { first, second, third, fourth };

typedef struct __Data {
	int id;       
	Type type;    
	Time_t time; 
	Location loc; 
	float vel;      
	float dir;       
	quadrant moving;  
	int dir_timetohold;
	int dir_holingtime;
	int max_vel;
	int changeable_vel;
	int changeable_dir;
	int little_dir;
} Data;

//const Data BLANK_DATA = { -1,{ 0, 0, 0 }, 0,{ 0, 0, 0 }, 0, 0, first, 5,0,1,1,1,1,false };


