#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(Math)
	{
	public:
		TEST_METHOD(SquareRoot)
		{
			Assert::AreEqual(HD_Sqrtf(4.f), 2.f);
		}

		TEST_METHOD(AbsoluteValue)
		{
			Assert::AreEqual(HD_Abs(2), 2);
			Assert::AreEqual(HD_Abs(-2), 2);
			Assert::AreEqual(HD_Abs(2.f), 2.f);
			Assert::AreEqual(HD_Abs(-2.f), 2.f);
		}

		TEST_METHOD(Power)
		{
			Assert::AreEqual(HD_Pow(2, 2), 4);
			Assert::AreEqual(HD_Powf(3.f, 3.f), 27.f);
		}

		TEST_METHOD(Max)
		{
			Assert::AreEqual(HD_Max(0, 0), 0);
			Assert::AreEqual(HD_Max(1, 2), 2);
			Assert::AreEqual(HD_Max(2, 1), 2);
			Assert::AreEqual(HD_Max(-1.f, 1.f), 1.f);
			Assert::AreEqual(HD_Max(1.f, -1.f), 1.f);
		}

		TEST_METHOD(Min)
		{
			Assert::AreEqual(HD_Min(0, 0), 0);
			Assert::AreEqual(HD_Min(1, 2), 1);
			Assert::AreEqual(HD_Min(2, 1), 1);
			Assert::AreEqual(HD_Min(-1.f, 1.f), -1.f);
			Assert::AreEqual(HD_Min(1.f, -1.f), -1.f);
		}
	};
}
