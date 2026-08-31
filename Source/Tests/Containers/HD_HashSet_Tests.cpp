#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_HashSet.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_HashSet_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_HashSet<s32> set;
			Assert::IsNull(set.myData);
			Assert::IsNull(set.myControlBytes);
			Assert::IsNull(set.myValues);
			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 0u);
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_HashSet<HD_String> set;
			Assert::IsNull(set.myData);
			Assert::IsNull(set.myControlBytes);
			Assert::IsNull(set.myValues);
			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 0u);
		}

		TEST_METHOD(Constructor_Capacity_POD)
		{
			HD_HashSet<s32> set(16);
			Assert::IsNotNull(set.myData);
			Assert::IsNotNull(set.myControlBytes);
			Assert::IsNotNull(set.myValues);
			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Constructor_Capacity_NonPOD)
		{
			HD_HashSet<HD_String> set(16);
			Assert::IsNotNull(set.myData);
			Assert::IsNotNull(set.myControlBytes);
			Assert::IsNotNull(set.myValues);
			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Constructor_Copy_POD)
		{
			HD_HashSet<s32> set1;
			set1.Insert(0);
			set1.Insert(1);

			HD_HashSet<s32> set2(set1);

			Assert::AreEqual(set1.mySizeIncludingTombstones, set2.mySizeIncludingTombstones);
			Assert::AreEqual(set1.myCapacity, set2.myCapacity);

			const s32* value0 = set2.GetIfExists(0);
			const s32* value1 = set2.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);
		}

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			HD_HashSet<HD_String> set1;
			set1.Insert("0");
			set1.Insert("1");

			HD_HashSet<HD_String> set2(set1);

			Assert::AreEqual(set1.mySizeIncludingTombstones, set2.mySizeIncludingTombstones);
			Assert::AreEqual(set1.myCapacity, set2.myCapacity);

			const HD_String* value0 = set2.GetIfExists("0");
			const HD_String* value1 = set2.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");
		}

		TEST_METHOD(Constructor_Move_POD)
		{
			HD_HashSet<s32> set1;
			set1.Insert(0);
			set1.Insert(1);

			HD_HashSet<s32> set2(HD_Move(set1));

			Assert::IsNull(set1.myData);
			Assert::IsNotNull(set2.myData);

			Assert::AreEqual(set2.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set2.myCapacity, 16u);

			const s32* value0 = set2.GetIfExists(0);
			const s32* value1 = set2.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);
		}

		TEST_METHOD(Constructor_Move_NonPOD)
		{
			HD_HashSet<HD_String> set1;
			set1.Insert("0");
			set1.Insert("1");

			HD_HashSet<HD_String> set2(HD_Move(set1));

			Assert::IsNull(set1.myData);
			Assert::IsNotNull(set2.myData);

			Assert::AreEqual(set2.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set2.myCapacity, 16u);

			const HD_String* value0 = set2.GetIfExists("0");
			const HD_String* value1 = set2.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");
		}

		TEST_METHOD(Destructor_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			set.~HD_HashSet();
			Assert::IsNull(set.myData);
		}

		TEST_METHOD(Destructor_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			set.~HD_HashSet();
			Assert::IsNull(set.myData);
		}

		TEST_METHOD(Operator_Assignment_Copy_POD)
		{
			HD_HashSet<s32> set1;
			set1.Insert(0);
			set1.Insert(1);

			HD_HashSet<s32> set2;
			set2 = set1;

			Assert::AreEqual(set1.mySizeIncludingTombstones, set2.mySizeIncludingTombstones);
			Assert::AreEqual(set1.myCapacity, set2.myCapacity);

			const s32* value0 = set2.GetIfExists(0);
			const s32* value1 = set2.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);
		}

		TEST_METHOD(Operator_Assignment_Copy_NonPOD)
		{
			HD_HashSet<HD_String> set1;
			set1.Insert("0");
			set1.Insert("1");

			HD_HashSet<HD_String> set2;
			set2 = set1;

			Assert::AreEqual(set1.mySizeIncludingTombstones, set2.mySizeIncludingTombstones);
			Assert::AreEqual(set1.myCapacity, set2.myCapacity);

			const HD_String* value0 = set2.GetIfExists("0");
			const HD_String* value1 = set2.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");
		}

		TEST_METHOD(Operator_Assignment_Move_POD)
		{
			HD_HashSet<s32> set1;
			set1.Insert(0);
			set1.Insert(1);

			HD_HashSet<s32> set2;
			set2 = HD_Move(set1);

			Assert::IsNull(set1.myData);
			Assert::IsNotNull(set2.myData);

			Assert::AreEqual(set2.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set2.myCapacity, 16u);

			const s32* value0 = set2.GetIfExists(0);
			const s32* value1 = set2.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);
		}

		TEST_METHOD(Operator_Assignment_Move_NonPOD)
		{
			HD_HashSet<HD_String> set1;
			set1.Insert("0");
			set1.Insert("1");

			HD_HashSet<HD_String> set2;
			set2 = HD_Move(set1);

			Assert::IsNull(set1.myData);
			Assert::IsNotNull(set2.myData);

			Assert::AreEqual(set2.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set2.myCapacity, 16u);

			const HD_String* value0 = set2.GetIfExists("0");
			const HD_String* value1 = set2.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");
		}

		TEST_METHOD(GetIfExists_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			const s32* value0 = set.GetIfExists(0);
			const s32* value1 = set.GetIfExists(1);
			const s32* value2 = set.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);

			Assert::IsNull(value2);
		}

		TEST_METHOD(GetIfExists_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			const HD_String* value0 = set.GetIfExists("0");
			const HD_String* value1 = set.GetIfExists("1");
			const HD_String* value2 = set.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");

			Assert::IsNull(value2);
		}

		TEST_METHOD(Insert_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);

			const s32* value0 = set.GetIfExists(0);
			const s32* value1 = set.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);

			set.Insert(0);

			value0 = set.GetIfExists(0);
			value1 = set.GetIfExists(1);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Insert_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);

			const HD_String* value0 = set.GetIfExists("0");
			const HD_String* value1 = set.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");

			set.Insert("0");

			value0 = set.GetIfExists("0");
			value1 = set.GetIfExists("1");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Remove_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			set.Remove(0);

			const s32* value0 = set.GetIfExists(0);
			const s32* value1 = set.GetIfExists(1);

			Assert::IsNull(value0);
			Assert::IsNotNull(value1);
			Assert::AreEqual(*value1, 1);

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Remove_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			set.Remove("0");

			const HD_String* value0 = set.GetIfExists("0");
			const HD_String* value1 = set.GetIfExists("1");

			Assert::IsNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsTrue(*value1 == "1");

			Assert::AreEqual(set.mySizeIncludingTombstones, 2u);
			Assert::AreEqual(set.myCapacity, 16u);
		}

		TEST_METHOD(Clear_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			set.Clear();

			const s32* value0 = set.GetIfExists(0);
			const s32* value1 = set.GetIfExists(1);

			Assert::IsNull(value0);
			Assert::IsNull(value1);

			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
		}

		TEST_METHOD(Clear_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			set.Clear();

			const HD_String* value0 = set.GetIfExists("0");
			const HD_String* value1 = set.GetIfExists("1");

			Assert::IsNull(value0);
			Assert::IsNull(value1);

			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
		}

		TEST_METHOD(Iterator_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);

			for (s32 value : set)
			{
				bool is0Value = value == 0;
				bool is1Value = value == 1;
				Assert::IsTrue(is0Value != is1Value);
			}

			for (auto it = set.begin(); it != set.end(); it++)
			{
				s32 value = *it;

				bool is0Value = value == 0;
				bool is1Value = value == 1;
				Assert::IsTrue(is0Value != is1Value);
			}

			const HD_HashSet<s32> constSet(set);

			for (s32 value : constSet)
			{
				bool is0Value = value == 0;
				bool is1Value = value == 1;
				Assert::IsTrue(is0Value != is1Value);
			}

			for (auto it = constSet.begin(); it != constSet.end(); it++)
			{
				s32 value = *it;

				bool is0Value = value == 0;
				bool is1Value = value == 1;
				Assert::IsTrue(is0Value != is1Value);
			}
		}

		TEST_METHOD(Iterator_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");

			for (HD_String& value : set)
			{
				bool is0Value = value == "0";
				bool is1Value = value == "1";
				Assert::IsTrue(is0Value != is1Value);
			}

			for (auto it = set.begin(); it != set.end(); it++)
			{
				HD_String& value = *it;

				bool is0Value = value == "0";
				bool is1Value = value == "1";
				Assert::IsTrue(is0Value != is1Value);
			}

			const HD_HashSet<HD_String> constSet(set);

			for (const HD_String& value : constSet)
			{
				bool is0Value = value == "0";
				bool is1Value = value == "1";
				Assert::IsTrue(is0Value != is1Value);
			}

			for (auto it = constSet.begin(); it != constSet.end(); it++)
			{
				const HD_String& value = *it;

				bool is0Value = value == "0";
				bool is1Value = value == "1";
				Assert::IsTrue(is0Value != is1Value);
			}
		}

		TEST_METHOD(InitWithCapacity_POD)
		{
			HD_HashSet<s32> set;
			set.InitWithCapacity(32);

			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 32u);
		}

		TEST_METHOD(InitWithCapacity_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.InitWithCapacity(32);

			Assert::AreEqual(set.mySizeIncludingTombstones, 0u);
			Assert::AreEqual(set.myCapacity, 32u);
		}

		TEST_METHOD(InsertValueAtIndex_POD)
		{
			HD_HashSet<s32> set(16);
			set.InsertValueAtIndex(0, 0);

			u64 hashCode = HD_Hash(0);

			bool isSlotFullAtIndex = set.GetIsSlotFullAtIndex(0);
			bool isHashLevel2Set = set.GetLevel2Hash(set.myControlBytes[0]) == set.GetLevel2Hash(hashCode);
			Assert::IsTrue(isSlotFullAtIndex);
			Assert::IsTrue(isHashLevel2Set);

			Assert::AreEqual(set.myValues[0], 0);
		}

		TEST_METHOD(InsertKeyValueAtIndex_NonPOD)
		{
			HD_HashSet<HD_String> set(16);
			set.InsertValueAtIndex("0", 0);

			u64 hashCode = HD_Hash(HD_String("0"));

			bool isSlotFullAtIndex = set.GetIsSlotFullAtIndex(0);
			bool isHashLevel2Set = set.GetLevel2Hash(set.myControlBytes[0]) == set.GetLevel2Hash(hashCode);
			Assert::IsTrue(isSlotFullAtIndex);
			Assert::IsTrue(isHashLevel2Set);

			Assert::IsTrue(set.myValues[0] == "0");
		}

		TEST_METHOD(Rehash_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);
			set.Insert(1);
			set.Insert(2);
			set.Insert(3);
			set.Insert(4);
			set.Insert(5);
			set.Insert(6);
			set.Insert(7);
			set.Insert(8); // Should trigger a rehash

			Assert::AreEqual(set.mySizeIncludingTombstones, 9u);
			Assert::AreEqual(set.myCapacity, 32u);

			const s32* value0 = set.GetIfExists(0);
			const s32* value1 = set.GetIfExists(1);
			const s32* value2 = set.GetIfExists(2);
			const s32* value3 = set.GetIfExists(3);
			const s32* value4 = set.GetIfExists(4);
			const s32* value5 = set.GetIfExists(5);
			const s32* value6 = set.GetIfExists(6);
			const s32* value7 = set.GetIfExists(7);
			const s32* value8 = set.GetIfExists(8);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::IsNotNull(value3);
			Assert::IsNotNull(value4);
			Assert::IsNotNull(value5);
			Assert::IsNotNull(value6);
			Assert::IsNotNull(value7);
			Assert::IsNotNull(value8);
			Assert::AreEqual(*value0, 0);
			Assert::AreEqual(*value1, 1);
			Assert::AreEqual(*value2, 2);
			Assert::AreEqual(*value3, 3);
			Assert::AreEqual(*value4, 4);
			Assert::AreEqual(*value5, 5);
			Assert::AreEqual(*value6, 6);
			Assert::AreEqual(*value7, 7);
			Assert::AreEqual(*value8, 8);
		}

		TEST_METHOD(Rehash_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");
			set.Insert("1");
			set.Insert("2");
			set.Insert("3");
			set.Insert("4");
			set.Insert("5");
			set.Insert("6");
			set.Insert("7");
			set.Insert("8"); // Should trigger a rehash

			Assert::AreEqual(set.mySizeIncludingTombstones, 9u);
			Assert::AreEqual(set.myCapacity, 32u);

			const HD_String* value0 = set.GetIfExists("0");
			const HD_String* value1 = set.GetIfExists("1");
			const HD_String* value2 = set.GetIfExists("2");
			const HD_String* value3 = set.GetIfExists("3");
			const HD_String* value4 = set.GetIfExists("4");
			const HD_String* value5 = set.GetIfExists("5");
			const HD_String* value6 = set.GetIfExists("6");
			const HD_String* value7 = set.GetIfExists("7");
			const HD_String* value8 = set.GetIfExists("8");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value1);
			Assert::IsNotNull(value2);
			Assert::IsNotNull(value3);
			Assert::IsNotNull(value4);
			Assert::IsNotNull(value5);
			Assert::IsNotNull(value6);
			Assert::IsNotNull(value7);
			Assert::IsNotNull(value8);
			Assert::IsTrue(*value0 == "0");
			Assert::IsTrue(*value1 == "1");
			Assert::IsTrue(*value2 == "2");
			Assert::IsTrue(*value3 == "3");
			Assert::IsTrue(*value4 == "4");
			Assert::IsTrue(*value5 == "5");
			Assert::IsTrue(*value6 == "6");
			Assert::IsTrue(*value7 == "7");
			Assert::IsTrue(*value8 == "8");
		}

		TEST_METHOD(GetSlotIndexForValue_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);

			Assert::AreEqual(set.GetSlotIndexForValue(0), 7u);
		}

		TEST_METHOD(GetSlotIndexForValue_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");

			Assert::AreEqual(set.GetSlotIndexForValue("0"), 9u);
		}

		TEST_METHOD(GetFirstSlotIndex_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);

			Assert::AreEqual(set.GetFirstSlotIndex(), 7u);
		}

		TEST_METHOD(GetFirstSlotIndex_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");

			Assert::AreEqual(set.GetFirstSlotIndex(), 9u);
		}

		TEST_METHOD(GetIsSlotFullAtIndex_POD)
		{
			HD_HashSet<s32> set;
			set.Insert(0);

			Assert::IsTrue(set.GetIsSlotFullAtIndex(7));
			Assert::IsFalse(set.GetIsSlotFullAtIndex(0));
		}

		TEST_METHOD(GetIsSlotFullAtIndex_NonPOD)
		{
			HD_HashSet<HD_String> set;
			set.Insert("0");

			Assert::IsTrue(set.GetIsSlotFullAtIndex(9));
			Assert::IsFalse(set.GetIsSlotFullAtIndex(0));
		}

		TEST_METHOD(GetLevel1Hash)
		{
			HD_HashSet<s32> set;

			u64 madeUpHashCode = 0x7F;
			Assert::AreEqual(set.GetLevel1Hash(madeUpHashCode), 0ull);
		}

		TEST_METHOD(GetLevel2Hash)
		{
			HD_HashSet<s32> set;

			u64 madeUpHashCode = 0x7F;
			Assert::AreEqual(set.GetLevel2Hash(madeUpHashCode), static_cast<ControlByte_Type>(0x7F));
		}
	};
}
