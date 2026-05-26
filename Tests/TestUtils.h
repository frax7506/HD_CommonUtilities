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
}
