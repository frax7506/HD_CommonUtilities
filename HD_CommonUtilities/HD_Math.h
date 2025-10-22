#pragma once

#include <math.h>

#define F_ONE_OVER_SQRT_TWO 0.707106769f
#define F_SMALL 0.0001f

#define HD_Max(a, b) ((a) > (b) ? (a) : (b))
#define HD_Min(a, b) ((a) < (b) ? (a) : (b))

#define HD_Abs(a) ((a) < 0 ? (-1 * (a)) : (a))
#define HD_Sqrtf(arg) sqrtf(arg)
#define HD_Powf(a, b) powf(a, b)
#define HD_Pow(a, b) static_cast<int>(powf(static_cast<float>(a), static_cast<float>(b)))
