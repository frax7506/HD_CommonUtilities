#pragma once

#include "HD_Time.h"
#include "HD_Types.h"

class HD_Timer
{
public:
	HD_Timer();

	void Update();

	f32 GetDeltaTime() const;

private:
	TimeType myCurrentTimeMS;
	TimeType myDeltaTimeMS;
};
