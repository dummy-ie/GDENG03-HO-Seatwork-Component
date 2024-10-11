#include "Random.h"

int Random::range(int minInclusive, int maxInclusive)
{
	std::uniform_int_distribution<int> randomizer(minInclusive, maxInclusive);
	return randomizer(P_SHARED_INSTANCE->mt);
}

float Random::range(float minInclusive, float maxInclusive)
{
	maxInclusive += 0.0001f;
	std::uniform_real_distribution<float> randomizer(minInclusive, maxInclusive);
	return randomizer(P_SHARED_INSTANCE->mt);
}

Random* Random::P_SHARED_INSTANCE = NULL;

Random::Random() : mt(rd()) {}
Random::~Random() {}
Random::Random(Random const&) {}


void Random::initialize()
{
	P_SHARED_INSTANCE = new Random();
	P_SHARED_INSTANCE->mt.seed(::time(NULL));
}
