#include "stdafx.h"
#include "MyTime.h"

Time_t getCurrentTime() {
	return std::chrono::system_clock::now();
}
