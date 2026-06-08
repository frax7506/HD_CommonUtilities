#pragma once

#include "CppUnitTest.h"

#include "HD_Math.h"
#include "HD_String.h"

#define FLOAT_EQUAL_TOLERANCE F_SMALL

namespace TestUtils
{
	template<typename T>
	void Test_IsStringUninitialized(const HD_Str<T>& aStringToCheck)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(aStringToCheck.GetBuffer());
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetLength(), 0);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetCapacity(), 0);
	}
}
