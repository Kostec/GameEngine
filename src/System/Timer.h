#pragma once

#include <functional>

#include "../System/Events/Event.h"

class Timer
{
public:
	Timer();

	Event<> onTimerElapsed;

	void update(const double delta);
	void start(double duration);
	void stop();
	void setCallback(std::function<void()> callback);

private:
	std::function<void()> m_callback;
	double m_timeLeft;
	bool m_isRunning;
};