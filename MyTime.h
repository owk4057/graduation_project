#pragma once
#include <chrono>


typedef std::chrono::system_clock::time_point Time_t;
typedef std::chrono::duration<__int64, std::ratio<1, 10000000>> Range_t;

Time_t getCurrentTime();
