#include "Random.h"

#include "Logger.h"

int Random::range(int minInclusive, int maxInclusive)
{
	std::uniform_int_distribution<int> randomizer(minInclusive, maxInclusive);
	return randomizer(P_SHARED_INSTANCE->mt);
}

float Random::range(float minInclusive, float maxInclusive)
{
	std::uniform_real_distribution<float> randomizer(minInclusive, std::nextafter(maxInclusive, FLT_MAX));
	return randomizer(P_SHARED_INSTANCE->mt);
}

Random* Random::P_SHARED_INSTANCE = NULL;

Random::Random() : mt(std::random_device{}())
{
	mt.seed(time(nullptr));
	debug::Logger::log(P_SHARED_INSTANCE, "Initialized");
}
Random::~Random()
{
	debug::Logger::log(P_SHARED_INSTANCE, "Released");
}
Random::Random(Random const&) {}


void Random::initialize()
{
	P_SHARED_INSTANCE = new Random();
	
}

void Random::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
