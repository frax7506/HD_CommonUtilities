#include "HD_Random.h"

#include <random>

namespace HD_Random
{
	static std::random_device rndSeed;
	static std::mt19937 rndEngine(rndSeed());
	static std::uniform_real_distribution<f32> rndDist(std::uniform_real_distribution<f32>(0.f, 1.f));

	f32 GetRandomFloat(f32 aMin, f32 aMax)
	{
		return rndDist(rndEngine) * (aMax - aMin) + aMin;
	}
}
