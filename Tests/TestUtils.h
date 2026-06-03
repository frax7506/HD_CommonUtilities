#pragma once

#include "CppUnitTest.h"

#include "HD_Math.h"
#include "HD_String.h"

namespace TestUtils
{
	template<typename T>
	void StringDataCheckIsUninitialized(const HD_Str<T>& aStringToCheck)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(aStringToCheck.GetBuffer());
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetLength(), 0);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetCapacity(), 0);
	}

	inline bool AreFloatValuesClose(f32 aFirst, f32 aSecond)
	{
		f32 diff = HD_Abs(aFirst - aSecond);
		return diff < F_SMALL;
	}
}
