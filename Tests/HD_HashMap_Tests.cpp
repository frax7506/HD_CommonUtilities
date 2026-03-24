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

		TEST_METHOD(Constructor_Move)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[1] = 2;

			HD_HashMap<s32, s32> map2(HD_Move(map1));

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySize, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value1 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);
		}

		TEST_METHOD(Destructor)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[1] = 2;

			map.~HD_HashMap();
			Assert::IsNull(map.myData);
		}

		TEST_METHOD(GetIfExists)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[1] = 2;

			const s32* value1 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(1);
			const s32* value3 = map.GetIfExists(2);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);

			Assert::IsNull(value3);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[1] = 2;

			Assert::AreEqual(map.mySize, 2);
			Assert::AreEqual(map.myCapacity, 16);

			const s32* value1 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);

			map[0] = 3;
			value1 = map.GetIfExists(0);
			value2 = map.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 3);
			Assert::AreEqual(*value2, 2);

			map[2];

			Assert::AreEqual(map.mySize, 3);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[1] = 2;

			HD_HashMap<s32, s32> map2;
			map2 = map1;

			Assert::AreEqual(map1.mySize, map2.mySize);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value1 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[1] = 2;

			HD_HashMap<s32, s32> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySize, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value1 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);
		}

		TEST_METHOD(Remove)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Clear)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Iterator)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(InitWithCapacity)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(InsertKeyValueAtIndex)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Rehash)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(GetSlotIndexForKey)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(GetFirstSlotIndex)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(GetIsSlotFullAtIndex)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(GetLevel1Hash)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(GetLevel2Hash)
		{
			Assert::IsTrue(false);
		}
	};
}
