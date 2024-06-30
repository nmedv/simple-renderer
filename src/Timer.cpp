#include "Timer.h"

#include <chrono>

#define I(n) reinterpret_cast<LARGE_INTEGER*>(&n)


using namespace std::chrono;


int64_t Timer::getMicroseconds()
{
	return duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
}