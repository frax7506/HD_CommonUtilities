#include "HD_Timer.h"

HD_Timer::HD_Timer()
	: myCurrentTimeMS(HD_Time::GetCurrentTimeMS())
	, myDeltaTimeMS(0)
{
}

void HD_Timer::Update()
{
	TimeType currentTimeMS = HD_Time::GetCurrentTimeMS();

	myDeltaTimeMS = currentTimeMS - myCurrentTimeMS;
	myCurrentTimeMS = currentTimeMS;
}

f32 HD_Timer::GetDeltaTime() const
{
	f32 deltaTime = static_cast<f32>(myDeltaTimeMS) / 1000.f;
	return deltaTime;
}
