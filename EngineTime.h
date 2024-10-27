#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Window;
class EngineTime
{
private:
	static EngineTime* P_SHARED_INSTANCE;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&);
	EngineTime& operator = (EngineTime const&);

	friend class Window;

public:
	static void initialize();
	static double getDeltaTime();

private:
	static void LogFrameStart();
	static void LogFrameEnd();
};