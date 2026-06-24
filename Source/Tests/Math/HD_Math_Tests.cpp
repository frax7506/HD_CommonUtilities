#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Math.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(Math)
	{
	public:
		TEST_METHOD(Max)
		{
			Assert::AreEqual(HD_Max(0, 0), 0);
			Assert::AreEqual(HD_Max(1, 2), 2);
			Assert::AreEqual(HD_Max(2, 1), 2);
			Assert::AreEqual(HD_Max(-1.f, 1.f), 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_Max(1.f, -1.f), 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Min)
		{
			Assert::AreEqual(HD_Min(0, 0), 0);
			Assert::AreEqual(HD_Min(1, 2), 1);
			Assert::AreEqual(HD_Min(2, 1), 1);
			Assert::AreEqual(HD_Min(-1.f, 1.f), -1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_Min(1.f, -1.f), -1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Abs)
		{
			Assert::AreEqual(HD_Abs(2), 2);
			Assert::AreEqual(HD_Abs(-2), 2);
			Assert::AreEqual(HD_Abs(2.f), 2.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_Abs(-2.f), 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Sqrt)
		{
			Assert::AreEqual(HD_Sqrt(4.f), 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Pow)
		{
			Assert::AreEqual(HD_Pow(2, 2), 4);
			Assert::AreEqual(HD_Pow(3.f, 3.f), 27.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Remap)
		{
			Assert::AreEqual(HD_Remap(5.f, 0.f, 10.f, 100.f, 200.f), 150.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_Remap(-5.f, 0.f, 10.f, 100.f, 200.f), 50.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_Remap(15.f, 0.f, 10.f, 100.f, 200.f), 250.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(RemapClamped)
		{
			Assert::AreEqual(HD_RemapClamped(5.f, 0.f, 10.f, 100.f, 200.f), 150.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_RemapClamped(-5.f, 0.f, 10.f, 100.f, 200.f), 100.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(HD_RemapClamped(15.f, 0.f, 10.f, 100.f, 200.f), 200.f, FLOAT_EQUAL_TOLERANCE);
		}
	};
}
