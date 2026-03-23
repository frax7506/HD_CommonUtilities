// WIP

#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_HashMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_HashMap_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_HashMap<s32, s32> map;
			Assert::IsNotNull(map.myData);
			Assert::IsNotNull(map.myControlBytes);
			Assert::IsNotNull(map.myKeyValuePairs);
			Assert::AreEqual(map.mySize, 0);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[1] = 2;

			HD_HashMap<s32, s32> map2(map1);

			Assert::AreEqual(map1.mySize, map2.mySize);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value1 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);
		}

		TEST_METHOD(Iterator)
		{
			HD_HashMap<s32, s32> map1;
			auto it1 = map1.begin();

			const HD_HashMap<s32, s32> map2;
			auto it2 = map2.begin();

			it1;
			it2;
		}
	};
}
