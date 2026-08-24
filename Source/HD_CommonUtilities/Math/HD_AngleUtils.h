#pragma once

#include "HD_Math.h"
#include "HD_Types.h"
#include "HD_Vector.h"

namespace HD_AngleUtils
{
	f32 SignedAngleBetweenVectors(const HD_Vector2_f32& aVector1, const HD_Vector2_f32& aVector2);
	f32 AngleBetweenVectors(const HD_Vector2_f32& aVector1, const HD_Vector2_f32& aVector2);
}
