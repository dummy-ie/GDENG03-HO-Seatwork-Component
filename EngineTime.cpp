#include "EngineTime.h"

using namespace engine;

EngineTime* EngineTime::P_SHARED_INSTANCE = NULL;

EngineTime::EngineTime() {}
EngineTime::~EngineTime() {}
EngineTime::EngineTime(EngineTime const&) {}

void EngineTime::initialize()
{
	P_SHARED_INSTANCE = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return P_SHARED_INSTANCE->deltaTime;
}

void EngineTime::LogFrameStart()
{
	P_SHARED_INSTANCE->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	P_SHARED_INSTANCE->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = P_SHARED_INSTANCE->end - P_SHARED_INSTANCE->start;

	P_SHARED_INSTANCE->deltaTime = elapsed_seconds.count();
}