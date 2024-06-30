#ifndef TIMER_H
#define TIMER_H

#include <cstdint>


class Timer
{
public:
	Timer() {}

	static int64_t getMicroseconds();

private:
	uint64_t _now = 0;
};

#endif