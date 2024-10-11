#pragma once

#include <random>

class Random
{
private:
	static Random* P_SHARED_INSTANCE;

	std::random_device rd;
	std::mt19937 mt;

public:
	static int range(int minInclusive, int maxExclusive);
	static float range(float minInclusive, float maxInclusive);

private:
	Random();
	~Random();
	Random(Random const&);
	Random& operator = (Random const&);

public:
	static void initialize();
};

