#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_Map.h"
#include "HD_String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Map_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_Map<s32, s32> map;
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_Map<HD_String, HD_String> map;
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Constructor_Copy_POD)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2(map1);
			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			HD_Map<HD_String, HD_String> map1;
			map1["0"] = "0";
			map1["1"] = "1";
			map1["2"] = "2";

			HD_Map<HD_String, HD_String> map2(map1);
			Assert::IsTrue(map2.myRoot->myValue == "1");
			Assert::IsTrue(map2.myRoot->myLeft->myValue == "0");
			Assert::IsTrue(map2.myRoot->myRight->myValue == "2");

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Constructor_Move_POD)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2(HD_Move(map1));

			Assert::IsNull(map1.myRoot);

			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Constructor_Move_NonPOD)
		{
			HD_Map<HD_String, HD_String> map1;
			map1["0"] = "0";
			map1["1"] = "1";
			map1["2"] = "2";

			HD_Map<HD_String, HD_String> map2(HD_Move(map1));

			Assert::IsNull(map1.myRoot);

			Assert::IsTrue(map2.myRoot->myValue == "1");
			Assert::IsTrue(map2.myRoot->myLeft->myValue == "0");
			Assert::IsTrue(map2.myRoot->myRight->myValue == "2");

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Destructor_POD)
		{
			HD_Map<s32, s32> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;

			map.~HD_Map();
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Destructor_NonPOD)
		{
			HD_Map<HD_String, HD_String> map;
			map["0"] = "0";
			map["1"] = "1";
			map["2"] = "2";

			map.~HD_Map();
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(GetIfExists_POD)
		{
			HD_Map<s32, s32> map;
			map[0] = 0;

			const s32* value1 = map.GetIfExists(0);
			const s32* value2 = map.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::AreEqual(*value1, 0);
			Assert::IsNull(value2);
		}

		TEST_METHOD(GetIfExists_NonPOD)
		{
			HD_Map<HD_String, HD_String> map;
			map["0"] = "0";

			const HD_String* value1 = map.GetIfExists("0");
			const HD_String* value2 = map.GetIfExists("1");

			Assert::IsNotNull(value1);
			Assert::IsTrue(*value1 == "0");
			Assert::IsNull(value2);
		}

		TEST_METHOD(Operator_Subscript_POD)
		{
			HD_Map<s32, s32> map;
			Assert::IsNull(map.myRoot);

			map[6] = 6;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 6);
			Assert::AreEqual(map.myRoot->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			map[7] = 7;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 6);
			Assert::AreEqual(map.myRoot->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Left rotation
			map[8] = 8;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map[5] = 5;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 6);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 5);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Right rotation
			map[4] = 4;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map[10] = 10;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right left rotation
			map[9] = 9;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			map[2] = 2;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 2);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Left right rotation
			map[3] = 3;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 2);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right rotation with children
			map[1] = 1;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);
		}

		TEST_METHOD(Operator_Subscript_NonPOD)
		{
			HD_Map<HD_String, HD_String> map;
			Assert::IsNull(map.myRoot);

			map["f"] = "f";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "f");
			Assert::IsTrue(map.myRoot->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			map["g"] = "g";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "f");
			Assert::IsTrue(map.myRoot->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "g");
			Assert::IsTrue(map.myRoot->myRight->myValue == "g");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Left rotation
			map["h"] = "h";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map["e"] = "e";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "f");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "e");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Right rotation
			map["d"] = "d";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map["j"] = "j";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right left rotation
			map["i"] = "i";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			map["b"] = "b";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "d");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "b");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Left right rotation
			map["c"] = "c";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "b");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myRight->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myRight->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right rotation with children
			map["a"] = "a";
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);
		}

		TEST_METHOD(Remove_POD)
		{
			HD_Map<s32, s32> map;
			map[6] = 6;
			map[7] = 7;
			map[8] = 8;
			map[5] = 5;
			map[4] = 4;
			map[10] = 10;
			map[9] = 9;
			map[2] = 2;
			map[3] = 3;
			map[1] = 1;

			// Remove a key that isn't in the map, make sure the map is unchanged.
			map.Remove(0);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove right leaf
			map.Remove(6);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one left child
			map.Remove(5);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with two children
			map.Remove(9);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myValue, 10);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove that results in one right rotation
			map.Remove(10);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove left leaf
			map.Remove(4);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one right child
			map.Remove(7);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove(3);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 2);
			Assert::AreEqual(map.myRoot->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove(2);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 8);
			Assert::AreEqual(map.myRoot->myValue, 8);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which has one child
			map.Remove(8);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 1);
			Assert::AreEqual(map.myRoot->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which is the last node
			map.Remove(1);
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Remove_NonPOD)
		{
			HD_Map<HD_String, HD_String> map;
			map["f"] = "f";
			map["g"] = "g";
			map["h"] = "h";
			map["e"] = "e";
			map["d"] = "d";
			map["j"] = "j";
			map["i"] = "i";
			map["b"] = "b";
			map["c"] = "c";
			map["a"] = "a";

			// Remove a key that isn't in the map, make sure the map is unchanged.
			map.Remove("0");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myRight->myKey == "f");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myRight->myValue == "f");
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove right leaf
			map.Remove("f");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "e");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "e");
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one left child
			map.Remove("e");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "i");
			Assert::IsTrue(map.myRoot->myRight->myValue == "i");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "j");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with two children
			map.Remove("i");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "g");
			Assert::IsTrue(map.myRoot->myValue == "g");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "c");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::IsTrue(map.myRoot->myLeft->myRight->myKey == "d");
			Assert::IsTrue(map.myRoot->myLeft->myRight->myValue == "d");
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "j");
			Assert::IsTrue(map.myRoot->myRight->myValue == "j");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove that results in one right rotation
			map.Remove("j");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "c");
			Assert::IsTrue(map.myRoot->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "g");
			Assert::IsTrue(map.myRoot->myRight->myValue == "g");
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::IsTrue(map.myRoot->myRight->myLeft->myKey == "d");
			Assert::IsTrue(map.myRoot->myRight->myLeft->myValue == "d");
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove left leaf
			map.Remove("d");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "c");
			Assert::IsTrue(map.myRoot->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "g");
			Assert::IsTrue(map.myRoot->myRight->myValue == "g");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::IsTrue(map.myRoot->myRight->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one right child
			map.Remove("g");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "c");
			Assert::IsTrue(map.myRoot->myValue == "c");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "b");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove("c");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "b");
			Assert::IsTrue(map.myRoot->myValue == "b");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::IsTrue(map.myRoot->myRight->myKey == "h");
			Assert::IsTrue(map.myRoot->myRight->myValue == "h");
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove("b");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "h");
			Assert::IsTrue(map.myRoot->myValue == "h");
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::IsTrue(map.myRoot->myLeft->myKey == "a");
			Assert::IsTrue(map.myRoot->myLeft->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which has one child
			map.Remove("h");
			Assert::IsNotNull(map.myRoot);
			Assert::IsTrue(map.myRoot->myKey == "a");
			Assert::IsTrue(map.myRoot->myValue == "a");
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which is the last node
			map.Remove("a");
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Operator_Assignment_Copy_POD)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2;
			map2 = map1;
			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Operator_Assignment_Copy_NonPOD)
		{
			HD_Map<HD_String, HD_String> map1;
			map1["0"] = "0";
			map1["1"] = "1";
			map1["2"] = "2";

			HD_Map<HD_String, HD_String> map2;
			map2 = map1;
			Assert::IsTrue(map2.myRoot->myValue == "1");
			Assert::IsTrue(map2.myRoot->myLeft->myValue == "0");
			Assert::IsTrue(map2.myRoot->myRight->myValue == "2");

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Operator_Assignment_Move_POD)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myRoot);

			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Operator_Assignment_Move_NonPOD)
		{
			HD_Map<HD_String, HD_String> map1;
			map1["0"] = "0";
			map1["1"] = "1";
			map1["2"] = "2";

			HD_Map<HD_String, HD_String> map2;
			map2 = HD_Move(map1);

			Assert::IsNull(map1.myRoot);

			Assert::IsTrue(map2.myRoot->myValue == "1");
			Assert::IsTrue(map2.myRoot->myLeft->myValue == "0");
			Assert::IsTrue(map2.myRoot->myRight->myValue == "2");

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Iterator_POD)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			int index = 0;
			for (const auto& node : map1)
			{
				Assert::AreEqual(node.myKey, index);
				Assert::AreEqual(node.myValue, index);
				++index;
			}

			const HD_Map<s32, s32> map2(map1);

			index = 0;
			for (const auto& node : map2)
			{
				Assert::AreEqual(node.myKey, index);
				Assert::AreEqual(node.myValue, index);
				++index;
			}
		}

		TEST_METHOD(Iterator_NonPOD)
		{
			HD_Map<HD_String, HD_String> map1;
			map1["a"] = "a";
			map1["b"] = "b";
			map1["c"] = "c";

			int index = 0;
			for (auto& node : map1)
			{
				if (index == 0)
				{
					Assert::IsTrue(node.myKey == "a");
					Assert::IsTrue(node.myValue == "a");
				}
				else if (index == 1)
				{
					Assert::IsTrue(node.myKey == "b");
					Assert::IsTrue(node.myValue == "b");
				}
				else // index == 2
				{
					Assert::IsTrue(node.myKey == "c");
					Assert::IsTrue(node.myValue == "c");
				}

				index++;
			}

			index = 0;
			for (auto it = map1.begin(); it != map1.end(); it++)
			{
				if (index == 0)
				{
					Assert::IsTrue(it->myKey == "a");
					Assert::IsTrue(it->myValue == "a");
				}
				else if (index == 1)
				{
					Assert::IsTrue(it->myKey == "b");
					Assert::IsTrue(it->myValue == "b");
				}
				else // index == 2
				{
					Assert::IsTrue(it->myKey == "c");
					Assert::IsTrue(it->myValue == "c");
				}

				index++;
			}

			const HD_Map<HD_String, HD_String> map2(map1);

			index = 0;
			for (const auto& node : map2)
			{
				if (index == 0)
				{
					Assert::IsTrue(node.myKey == "a");
					Assert::IsTrue(node.myValue == "a");
				}
				else if (index == 1)
				{
					Assert::IsTrue(node.myKey == "b");
					Assert::IsTrue(node.myValue == "b");
				}
				else // index == 2
				{
					Assert::IsTrue(node.myKey == "c");
					Assert::IsTrue(node.myValue == "c");
				}

				index++;
			}

			index = 0;
			for (auto it = map2.begin(); it != map2.end(); it++)
			{
				if (index == 0)
				{
					Assert::IsTrue(it->myKey == "a");
					Assert::IsTrue(it->myValue == "a");
				}
				else if (index == 1)
				{
					Assert::IsTrue(it->myKey == "b");
					Assert::IsTrue(it->myValue == "b");
				}
				else // index == 2
				{
					Assert::IsTrue(it->myKey == "c");
					Assert::IsTrue(it->myValue == "c");
				}

				index++;
			}
		}
	};
}
