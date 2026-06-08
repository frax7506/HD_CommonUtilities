#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_HashMap.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_HashMap_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_HashMap<s32, s32> map;
			Assert::IsNull(map.myData);
			Assert::IsNull(map.myControlBytes);
			Assert::IsNull(map.myKeyValuePairs);
			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 0);
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			Assert::IsNull(map.myData);
			Assert::IsNull(map.myControlBytes);
			Assert::IsNull(map.myKeyValuePairs);
			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 0);
		}

		TEST_METHOD(Constructor_Capacity_POD)
		{
			HD_HashMap<s32, s32> map(16);
			Assert::IsNotNull(map.myData);
			Assert::IsNotNull(map.myControlBytes);
			Assert::IsNotNull(map.myKeyValuePairs);
			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Constructor_Capacity_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map(16);
			Assert::IsNotNull(map.myData);
			Assert::IsNotNull(map.myControlBytes);
			Assert::IsNotNull(map.myKeyValuePairs);
			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Constructor_Copy_POD)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2(map1);

			Assert::AreEqual(map1.mySizeIncludingTombstones, map2.mySizeIncludingTombstones);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map1;
			map1["0"] = "1";
			map1["2"] = "3";

			HD_HashMap<HD_String, HD_String> map2(map1);

			Assert::AreEqual(map1.mySizeIncludingTombstones, map2.mySizeIncludingTombstones);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const HD_String* value0 = map2.GetIfExists("0");
			const HD_String* value2 = map2.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");
		}

		TEST_METHOD(Constructor_Move_POD)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2(HD_Move(map1));

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Constructor_Move_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map1;
			map1["0"] = "1";
			map1["2"] = "3";

			HD_HashMap<HD_String, HD_String> map2(HD_Move(map1));

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const HD_String* value0 = map2.GetIfExists("0");
			const HD_String* value2 = map2.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");
		}

		TEST_METHOD(Destructor_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			map.~HD_HashMap();
			Assert::IsNull(map.myData);
		}

		TEST_METHOD(Destructor_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			map.~HD_HashMap();
			Assert::IsNull(map.myData);
		}

		TEST_METHOD(GetIfExists_POD)
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

		TEST_METHOD(GetIfExists_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			const HD_String* value0 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("2");
			const HD_String* value4 = map.GetIfExists("4");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");

			Assert::IsNull(value4);
		}

		TEST_METHOD(Operator_Subscript_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			Assert::AreEqual(map.mySizeIncludingTombstones, 2);
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

			Assert::AreEqual(map.mySizeIncludingTombstones, 3);
			Assert::AreEqual(map.myCapacity, 16);

			const s32* value4 = map.GetIfExists(4);
			Assert::AreEqual(*value4, 0);
		}

		TEST_METHOD(Operator_Subscript_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			Assert::AreEqual(map.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map.myCapacity, 16);

			const HD_String* value0 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");

			map["0"] = "5";
			value0 = map.GetIfExists("0");
			value2 = map.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "5");
			Assert::IsTrue(*value2 == "3");

			map["4"];

			Assert::AreEqual(map.mySizeIncludingTombstones, 3);
			Assert::AreEqual(map.myCapacity, 16);

			const HD_String* value4 = map.GetIfExists("4");
			TestUtils::String_IsUninitialized(*value4);
		}

		TEST_METHOD(Operator_Assignment_Copy_POD)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2;
			map2 = map1;

			Assert::AreEqual(map1.mySizeIncludingTombstones, map2.mySizeIncludingTombstones);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Operator_Assignment_Copy_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map1;
			map1["0"] = "1";
			map1["2"] = "3";

			HD_HashMap<HD_String, HD_String> map2;
			map2 = map1;

			Assert::AreEqual(map1.mySizeIncludingTombstones, map2.mySizeIncludingTombstones);
			Assert::AreEqual(map1.myCapacity, map2.myCapacity);

			const HD_String* value0 = map2.GetIfExists("0");
			const HD_String* value2 = map2.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");
		}

		TEST_METHOD(Operator_Assignment_Move_POD)
		{
			HD_HashMap<s32, s32> map1;
			map1[0] = 1;
			map1[2] = 3;

			HD_HashMap<s32, s32> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const s32* value0 = map2.GetIfExists(0);
			const s32* value2 = map2.GetIfExists(2);

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::AreEqual(*value0, 1);
			Assert::AreEqual(*value2, 3);
		}

		TEST_METHOD(Operator_Assignment_Move_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map1;
			map1["0"] = "1";
			map1["2"] = "3";

			HD_HashMap<HD_String, HD_String> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myData);
			Assert::IsNotNull(map2.myData);

			Assert::AreEqual(map2.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map2.myCapacity, 16);

			const HD_String* value0 = map2.GetIfExists("0");
			const HD_String* value2 = map2.GetIfExists("2");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");
		}

		TEST_METHOD(Remove_POD)
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

			Assert::AreEqual(map.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Remove_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			map.Remove("0");

			const HD_String* value0 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("2");

			Assert::IsNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsTrue(*value2 == "3");

			Assert::AreEqual(map.mySizeIncludingTombstones, 2);
			Assert::AreEqual(map.myCapacity, 16);
		}

		TEST_METHOD(Clear_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			map.Clear();

			const s32* value0 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(2);

			Assert::IsNull(value0);
			Assert::IsNull(value2);

			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
		}

		TEST_METHOD(Clear_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			map.Clear();

			const HD_String* value0 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("2");

			Assert::IsNull(value0);
			Assert::IsNull(value2);

			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
		}

		TEST_METHOD(Iterator_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;
			map[2] = 3;

			for (auto& entry : map)
			{
				s32 key = entry.myFirst;
				s32 value = entry.mySecond;

				bool is01Entry = key == 0 && value == 1;
				bool is23Entry = key == 2 && value == 3;
				Assert::IsTrue(is01Entry != is23Entry);
			}

			for (auto it = map.begin(); it != map.end(); it++)
			{
				s32 key = it->myFirst;
				s32 value = it->mySecond;

				bool is01Entry = key == 0 && value == 1;
				bool is23Entry = key == 2 && value == 3;
				Assert::IsTrue(is01Entry != is23Entry);
			}

			const HD_HashMap<s32, s32> constMap(map);

			for (const auto& entry : constMap)
			{
				s32 key = entry.myFirst;
				s32 value = entry.mySecond;

				bool is01Entry = key == 0 && value == 1;
				bool is23Entry = key == 2 && value == 3;
				Assert::IsTrue(is01Entry != is23Entry);
			}

			for (auto it = constMap.begin(); it != constMap.end(); it++)
			{
				s32 key = it->myFirst;
				s32 value = it->mySecond;

				bool is01Entry = key == 0 && value == 1;
				bool is23Entry = key == 2 && value == 3;
				Assert::IsTrue(is01Entry != is23Entry);
			}
		}

		TEST_METHOD(Iterator_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";

			for (auto& entry : map)
			{
				HD_String& key = entry.myFirst;
				HD_String& value = entry.mySecond;

				bool is01Entry = key == "0" && value == "1";
				bool is23Entry = key == "2" && value == "3";
				Assert::IsTrue(is01Entry != is23Entry);
			}

			for (auto it = map.begin(); it != map.end(); it++)
			{
				HD_String& key = it->myFirst;
				HD_String& value = it->mySecond;

				bool is01Entry = key == "0" && value == "1";
				bool is23Entry = key == "2" && value == "3";
				Assert::IsTrue(is01Entry != is23Entry);
			}

			const HD_HashMap<HD_String, HD_String> constMap(map);

			for (const auto& entry : constMap)
			{
				const HD_String& key = entry.myFirst;
				const HD_String& value = entry.mySecond;

				bool is01Entry = key == "0" && value == "1";
				bool is23Entry = key == "2" && value == "3";
				Assert::IsTrue(is01Entry != is23Entry);
			}

			for (auto it = constMap.begin(); it != constMap.end(); it++)
			{
				const HD_String& key = it->myFirst;
				const HD_String& value = it->mySecond;

				bool is01Entry = key == "0" && value == "1";
				bool is23Entry = key == "2" && value == "3";
				Assert::IsTrue(is01Entry != is23Entry);
			}
		}

		TEST_METHOD(InitWithCapacity_POD)
		{
			HD_HashMap<s32, s32> map;
			map.InitWithCapacity(32);

			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 32);
		}

		TEST_METHOD(InitWithCapacity_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map.InitWithCapacity(32);

			Assert::AreEqual(map.mySizeIncludingTombstones, 0);
			Assert::AreEqual(map.myCapacity, 32);
		}

		TEST_METHOD(InsertKeyValueAtIndex_POD)
		{
			HD_HashMap<s32, s32> map(16);
			map.InsertKeyValueAtIndex(0, 1, 0);

			size_t hashCode = HD_Hash(0);

			bool isSlotFullAtIndex = map.GetIsSlotFullAtIndex(0);
			bool isHashLevel2Set = map.GetLevel2Hash(map.myControlBytes[0]) == map.GetLevel2Hash(hashCode);
			Assert::IsTrue(isSlotFullAtIndex);
			Assert::IsTrue(isHashLevel2Set);

			Assert::AreEqual(map.myKeyValuePairs[0].myFirst, 0);
			Assert::AreEqual(map.myKeyValuePairs[0].mySecond, 1);
		}

		TEST_METHOD(InsertKeyValueAtIndex_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map(16);
			map.InsertKeyValueAtIndex("0", "1", 0);

			size_t hashCode = HD_Hash(HD_String("0"));

			bool isSlotFullAtIndex = map.GetIsSlotFullAtIndex(0);
			bool isHashLevel2Set = map.GetLevel2Hash(map.myControlBytes[0]) == map.GetLevel2Hash(hashCode);
			Assert::IsTrue(isSlotFullAtIndex);
			Assert::IsTrue(isHashLevel2Set);

			Assert::IsTrue(map.myKeyValuePairs[0].myFirst == "0");
			Assert::IsTrue(map.myKeyValuePairs[0].mySecond == "1");
		}

		TEST_METHOD(Rehash_POD)
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

			Assert::AreEqual(map.mySizeIncludingTombstones, 9);
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

		TEST_METHOD(Rehash_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";
			map["2"] = "3";
			map["4"] = "5";
			map["6"] = "7";
			map["8"] = "9";
			map["10"] = "11";
			map["12"] = "13";
			map["14"] = "15";
			map["16"] = "17"; // Should trigger a rehash

			Assert::AreEqual(map.mySizeIncludingTombstones, 9);
			Assert::AreEqual(map.myCapacity, 32);

			const HD_String* value0 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("2");
			const HD_String* value4 = map.GetIfExists("4");
			const HD_String* value6 = map.GetIfExists("6");
			const HD_String* value8 = map.GetIfExists("8");
			const HD_String* value10 = map.GetIfExists("10");
			const HD_String* value12 = map.GetIfExists("12");
			const HD_String* value14 = map.GetIfExists("14");
			const HD_String* value16 = map.GetIfExists("16");

			Assert::IsNotNull(value0);
			Assert::IsNotNull(value2);
			Assert::IsNotNull(value4);
			Assert::IsNotNull(value6);
			Assert::IsNotNull(value8);
			Assert::IsNotNull(value10);
			Assert::IsNotNull(value12);
			Assert::IsNotNull(value14);
			Assert::IsNotNull(value16);
			Assert::IsTrue(*value0 == "1");
			Assert::IsTrue(*value2 == "3");
			Assert::IsTrue(*value4 == "5");
			Assert::IsTrue(*value6 == "7");
			Assert::IsTrue(*value8 == "9");
			Assert::IsTrue(*value10 == "11");
			Assert::IsTrue(*value12 == "13");
			Assert::IsTrue(*value14 == "15");
			Assert::IsTrue(*value16 == "17");
		}

		TEST_METHOD(GetSlotIndexForKey_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::AreEqual(map.GetSlotIndexForKey(0), 7);
		}

		TEST_METHOD(GetSlotIndexForKey_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";

			Assert::AreEqual(map.GetSlotIndexForKey("0"), 9);
		}

		TEST_METHOD(GetFirstSlotIndex_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::AreEqual(map.GetFirstSlotIndex(), 7);
		}

		TEST_METHOD(GetFirstSlotIndex_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";

			Assert::AreEqual(map.GetFirstSlotIndex(), 9);
		}

		TEST_METHOD(GetIsSlotFullAtIndex_POD)
		{
			HD_HashMap<s32, s32> map;
			map[0] = 1;

			Assert::IsTrue(map.GetIsSlotFullAtIndex(7));
			Assert::IsFalse(map.GetIsSlotFullAtIndex(0));
		}

		TEST_METHOD(GetIsSlotFullAtIndex_NonPOD)
		{
			HD_HashMap<HD_String, HD_String> map;
			map["0"] = "1";

			Assert::IsTrue(map.GetIsSlotFullAtIndex(9));
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
