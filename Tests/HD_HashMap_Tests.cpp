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
			map1[2] = 3;

			HD_HashMap<s32, s32> map2(map1);

			Assert::AreEqual(map1.mySize, map2.mySize);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2(HD_Move(map1));

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySize, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Destructor)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			map.~HD_HashMap();
			Assert::IsNull(map.myData);
		}

		TEST_METHOD(GetIfExists)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);
			const s32* value4 = map.GetIfExists(4);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);

			Assert::IsNull(value4);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			Assert::AreEqual(map.mySize, 2);
			Assert::AreEqual(map.myCapacity, 16);

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);

			map[0] = 5;
			value0 = map.GetIfExists(0);
			value2 = map.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 5);
			Assert::AreEqual(*value2, 3);

			map[4];

			Assert::AreEqual(map.mySize, 3);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2;
			map2 = map1;

			Assert::AreEqual(map1.mySize, map2.mySize);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySize, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Remove)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			map.Remove(0);

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);

			Assert::IsNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value2, 3);

			// Size should be unaffected since Remove creates tombstones
			Assert::AreEqual(map.mySize, 2);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Clear)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			map.Clear();

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);

			Assert::IsNull(value0);
			Assert::IsNull(value2);

			Assert::AreEqual(map.mySize, 0);
		}

		TEST_METHOD(Iterator)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			s32 i = 0;
			for (auto& entry : map)
			{
				s32 key = entry.myFirst;
				s32 value = entry.mySecond;

				Assert::AreEqual(key, i * 2);
				Assert::AreEqual(value, i * 2 + 1);

				i++;
			}

			i = 0;
			for (auto it = map.begin(); it != map.end(); it++)
			{
				s32 key = it->myFirst;
				s32 value = it->mySecond;

				Assert::AreEqual(key, i * 2);
				Assert::AreEqual(value, i * 2 + 1);

				i++;
			}

			const HD_HashMap<s32, s32> constMap(map);

			i = 0;
			for (const auto& entry : constMap)
			{
				s32 key = entry.myFirst;
				s32 value = entry.mySecond;

				Assert::AreEqual(key, i * 2);
				Assert::AreEqual(value, i * 2 + 1);

				i++;
			}

			i = 0;
			for (auto it = constMap.begin(); it != constMap.end(); it++)
			{
				s32 key = it->myFirst;
				s32 value = it->mySecond;

				Assert::AreEqual(key, i * 2);
				Assert::AreEqual(value, i * 2 + 1);

				i++;
			}
		}

		TEST_METHOD(InitWithCapacity)
		{
			HD_HashMap<s32, s32> map;
			map.~HD_HashMap();

			map.InitWithCapacity(32);

			Assert::AreEqual(map.mySize, 0);
			Assert::AreEqual(map.myCapacity, 32);
		}

		TEST_METHOD(InsertKeyValueAtIndex)
		{
			HD_HashMap<s32, s32> map;
			map.InsertKeyValueAtIndex(0, 1, 0);

			size_t hashCode = HD_Hash(0);

			bool isSlotFullAtIndex = map.GetIsSlotFullAtIndex(0);
			bool isHashLevel2Set = map.GetLevel2Hash(map.myControlBytes[0]) == map.GetLevel2Hash(hashCode);
			Assert::IsTrue(isSlotFullAtIndex);
			Assert::IsTrue(isHashLevel2Set);

			Assert::AreEqual(map.myKeyValuePairs[0].myFirst, 0);
			Assert::AreEqual(map.myKeyValuePairs[0].mySecond, 1);
		}

		TEST_METHOD(Rehash)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;
			map[4] = 5;
			map[6] = 7;
			map[8] = 9;
			map[10] = 11;
			map[12] = 13;
			map[14] = 15;
			map[16] = 17; // Should trigger a rehash

			Assert::AreEqual(map.mySize, 9);
			Assert::AreEqual(map.myCapacity, 32);

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);
			const s32* value4 = map.GetIfExists(4);
			const s32* value6 = map.GetIfExists(6);
			const s32* value8 = map.GetIfExists(8);
			const s32* value10 = map.GetIfExists(10);
			const s32* value12 = map.GetIfExists(12);
			const s32* value14 = map.GetIfExists(14);
			const s32* value16 = map.GetIfExists(16);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsNotNull(value4);
			Assert::IsNotNull(value6);
			Assert::IsNotNull(value8);
			Assert::IsNotNull(value10);
			Assert::IsNotNull(value12);
			Assert::IsNotNull(value14);
			Assert::IsNotNull(value16);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
			Assert::AreEqual(*value4, 5);
			Assert::AreEqual(*value6, 7);
			Assert::AreEqual(*value8, 9);
			Assert::AreEqual(*value10, 11);
			Assert::AreEqual(*value12, 13);
			Assert::AreEqual(*value14, 15);
			Assert::AreEqual(*value16, 17);
		}

		TEST_METHOD(GetSlotIndexForKey)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::AreEqual(map.GetSlotIndexForKey(0), 7);
		}

		TEST_METHOD(GetFirstSlotIndex)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::AreEqual(map.GetFirstSlotIndex(), 7);
		}

		TEST_METHOD(GetIsSlotFullAtIndex)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::IsTrue(map.GetIsSlotFullAtIndex(7));
			Assert::IsFalse(map.GetIsSlotFullAtIndex(0));
		}

		TEST_METHOD(GetLevel1Hash)
		{
			HD_HashMap<s32, s32> map;

			size_t madeUpHashCode = 0x7F;
			Assert::AreEqual(map.GetLevel1Hash(madeUpHashCode), 0ull);
		}

		TEST_METHOD(GetLevel2Hash)
		{
			HD_HashMap<s32, s32> map;

			size_t madeUpHashCode = 0x7F;
			Assert::AreEqual(map.GetLevel2Hash(madeUpHashCode), static_cast<ControlByte_t>(0x7F));
		}
	};
}
