#pragma once

#include "HD_Types.h"

#include <math.h>

#define F_SQRT_TWO 1.4142135623f
#define F_ONE_OVER_SQRT_TWO 0.7071067811f
#define F_SMALL 0.0001f

#define F_PI 3.1415926535f
#define F_PI_HALF (F_PI / 2.f)

#define DEG_TO_RAD(a) (a * (F_PI / 180.f))
#define RAD_TO_DEG(a) (a * (180.f / F_PI))

#define HD_Max(a, b) ((a) > (b) ? (a) : (b))
#define HD_Min(a, b) ((a) < (b) ? (a) : (b))
#define HD_Abs(a) ((a) < 0 ? (-1 * (a)) : (a))

#define HD_ARE_FLOAT_VALUES_CLOSE(a, b) (HD_Abs(a - b) < F_SMALL)

inline f32 HD_Sqrt(f32 aValue) { return sqrtf(aValue); }
inline f64 HD_Sqrt(f64 aValue) { return sqrt(aValue); }

inline f32 HD_Pow(f32 aBase, f32 aExponent) { return powf(aBase, aExponent); }
inline f64 HD_Pow(f64 aBase, f64 aExponent) { return pow(aBase, aExponent); }

inline f32 HD_Log2(f32 aValue) { return log2f(aValue); }
inline f64 HD_Log2(f64 aValue) { return log2(aValue); }

inline f32 HD_Sin(f32 aAngleInRadians) { return sinf(aAngleInRadians); }
inline f64 HD_Sin(f64 aAngleInRadians) { return sin(aAngleInRadians); }

inline f32 HD_Cos(f32 aAngleInRadians) { return cosf(aAngleInRadians); }
inline f64 HD_Cos(f64 aAngleInRadians) { return cos(aAngleInRadians); }

inline f32 HD_Tan(f32 aAngleInRadians) { return tanf(aAngleInRadians); }
inline f64 HD_Tan(f64 aAngleInRadians) { return tan(aAngleInRadians); }

inline f32 HD_ArcSin(f32 aAngleInRadians) { return asinf(aAngleInRadians); }
inline f64 HD_ArcSin(f64 aAngleInRadians) { return asin(aAngleInRadians); }

inline f32 HD_ArcCos(f32 aAngleInRadians) { return acosf(aAngleInRadians); }
inline f64 HD_ArcCos(f64 aAngleInRadians) { return acos(aAngleInRadians); }

inline f32 HD_ArcTan(f32 aAngleInRadians) { return atanf(aAngleInRadians); }
inline f64 HD_ArcTan(f64 aAngleInRadians) { return atan(aAngleInRadians); }

inline f32 HD_ArcTan2(f32 aAngleYInRadians, f32 aAngleXInRadians) { return atan2f(aAngleYInRadians, aAngleXInRadians); }
inline f64 HD_ArcTan2(f64 aAngleYInRadians, f64 aAngleXInRadians) { return atan2(aAngleYInRadians, aAngleXInRadians); }

template<typename T> inline T HD_Sign(T aValue);

template<typename T> inline T HD_Remap(T aValue, T aOldMin, T aOldMax, T aNewMin, T aNewMax);
template<typename T> inline T HD_RemapClamped(T aValue, T aOldMin, T aOldMax, T aNewMin, T aNewMax);

template<typename T> inline T HD_Lerp(T aStart, T aEnd, T aBlendValue);
template<typename VectorType> inline VectorType HD_Lerp(const VectorType& aStart, const VectorType& aEnd, typename VectorType::DataType aBlendValue);

template<typename T>
inline T HD_Sign(T aValue)
{
	return aValue < static_cast<T>(0) ? static_cast<T>(-1) : static_cast<T>(1);
}

template<typename T>
inline T HD_Remap(T aValue, T aOldMin, T aOldMax, T aNewMin, T aNewMax)
{
	return (((aValue - aOldMin) / (aOldMax - aOldMin)) * (aNewMax - aNewMin)) + aNewMin;
}

template<typename T>
inline T HD_RemapClamped(T aValue, T aOldMin, T aOldMax, T aNewMin, T aNewMax)
{
	if (aValue < aOldMin)
	{
		return aNewMin;
	}

	if (aValue > aOldMax)
	{
		return aNewMax;
	}

	return HD_Remap(aValue, aOldMin, aOldMax, aNewMin, aNewMax);
}

template<typename T>
inline T HD_Lerp(T aStart, T aEnd, T aBlendValue)
{
	return aStart * (1 - aBlendValue) + aEnd * aBlendValue;
}

template<typename VectorType>
inline VectorType HD_Lerp(const VectorType& aStart, const VectorType& aEnd, typename VectorType::DataType aBlendValue)
{
	return aStart + (aEnd - aStart) * aBlendValue;
}
