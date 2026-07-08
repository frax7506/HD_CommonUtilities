#pragma once

#include "HD_Types.h"

template<typename T>
struct HD_IsFundamental { enum { Result = false, }; };

template<>
struct HD_IsFundamental<s8> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<u8> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<s16> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<u16> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<s32> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<u32> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<s64> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<u64> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<f32> { enum { Result = true, }; };

template<>
struct HD_IsFundamental<f64> { enum { Result = true, }; };
