#pragma once

#include "CppUnitTest.h"

#include "HD_String.h"

#include <cassert>
#include <cstring>

namespace TestUtils
{
	template<typename T>
	void StringDataCheck(const HD_Str<T>& aStringToCheck, const T* aExpectedString)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(aStringToCheck.GetBuffer());

		int expectedLength = HD_Strlen(aExpectedString);
		assert(expectedLength < 128);

		T buffer[128]{ 0 };
		memcpy(buffer, aExpectedString, expectedLength * sizeof(T));
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(memcmp(aStringToCheck.GetBuffer(), buffer, (expectedLength + 1) * sizeof(T)), 0);
	}

	template<typename T>
	void StringDataCheckIsUninitialized(const HD_Str<T>& aStringToCheck)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(aStringToCheck.GetBuffer());
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetLength(), 0);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetCapacity(), 0);
	}
}
