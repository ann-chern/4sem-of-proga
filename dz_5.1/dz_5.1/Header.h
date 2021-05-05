#pragma once
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	Timer();
	~Timer();
	void pause();
	void cont();
private:
	time_point_t m_begin;
	std::chrono::microseconds dur;
	bool paused;
};