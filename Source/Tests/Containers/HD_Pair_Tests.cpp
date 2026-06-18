#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Pair.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Pair_Test)
	{
	public:
		TEST_METHOD(Construtor_Default)
		{
			HD_Pair<s32, s32> pair;
			Assert::AreEqual(pair.myFirst, 0);
			Assert::AreEqual(pair.mySecond, 0);
		}

		TEST_METHOD(Construtor_First_And_Second_As_Args)
		{
			HD_Pair<s32, s32> pair(1, 2);
			Assert::AreEqual(pair.myFirst, 1);
			Assert::AreEqual(pair.mySecond, 2);
		}
	};
}
