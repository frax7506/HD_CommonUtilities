#pragma once

#include <math.h>

#define F_ONE_OVER_SQRT_TWO 0.7071067811f
#define F_SMALL 0.0001f

#define F_PI 3.1415926535f
#define F_PI_HALF (F_PI / 2.f)

#define DEG_TO_RAD(a) (a * (F_PI / 180.f))
#define RAD_TO_DEG(a) (a * (180.f / F_PI))

#define HD_Max(a, b) ((a) > (b) ? (a) : (b))
#define HD_Min(a, b) ((a) < (b) ? (a) : (b))

#define HD_Abs(a) ((a) < 0 ? (-1 * (a)) : (a))
#define HD_Sqrtf(arg) sqrtf(arg)
#define HD_Powf(a, b) powf(a, b)
#define HD_Pow(a, b) static_cast<int>(powf(static_cast<float>(a), static_cast<float>(b)))

template<typename T> inline T HD_Sin(T aAngleInRadians);
template<typename T> inline T HD_Cos(T aAngleInRadians);
template<typename T> inline T HD_Tan(T aAngleInRadians);

template<typename T> inline T HD_ArcSin(T aAngleInRadians);
template<typename T> inline T HD_ArcCos(T aAngleInRadians);
template<typename T> inline T HD_ArcTan(T aAngleInRadians);

template<> inline float HD_Sin(float aAngleInRadians) { return sinf(aAngleInRadians); }
template<> inline float HD_Cos(float aAngleInRadians) { return cosf(aAngleInRadians); }
template<> inline float HD_Tan(float aAngleInRadians) { return tanf(aAngleInRadians); }

template<> inline double HD_Sin(double aAngleInRadians) { return sin(aAngleInRadians); }
template<> inline double HD_Cos(double aAngleInRadians) { return cos(aAngleInRadians); }
template<> inline double HD_Tan(double aAngleInRadians) { return tan(aAngleInRadians); }

template<> inline float HD_ArcSin(float aAngleInRadians) { return asinf(aAngleInRadians); }
template<> inline float HD_ArcCos(float aAngleInRadians) { return acosf(aAngleInRadians); }
template<> inline float HD_ArcTan(float aAngleInRadians) { return atanf(aAngleInRadians); }

template<> inline double HD_ArcSin(double aAngleInRadians) { return asin(aAngleInRadians); }
template<> inline double HD_ArcCos(double aAngleInRadians) { return acos(aAngleInRadians); }
template<> inline double HD_ArcTan(double aAngleInRadians) { return atan(aAngleInRadians); }
