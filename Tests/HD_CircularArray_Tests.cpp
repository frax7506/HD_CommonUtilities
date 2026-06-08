#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_CircularArray.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_CircularArray_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_CircularArray<s32, 8> circularArray;

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<s32, 8>::eOverflowBehaviour_Enable));

			for (s32 i = 0; i < 8; i++)
			{
				Assert::AreEqual(circularArray.myData[i], 0);
			}
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<HD_String, 8>::eOverflowBehaviour_Enable));

			for (s32 i = 0; i < 8; i++)
			{
				Assert::IsNull(circularArray.myData[i].myData);
				Assert::AreEqual(circularArray.myData[i].myLength, 0);
				Assert::AreEqual(circularArray.myData[i].myCapacity, 0);
			}
		}

		TEST_METHOD(PushBack_Overflow_Enabled_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 4);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 0);
			Assert::AreEqual(circularArray.myData[5], 0);
			Assert::AreEqual(circularArray.myData[6], 0);
			Assert::AreEqual(circularArray.myData[7], 0);

			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.PushBack(8);

			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 1);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 8);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.PushBack(9);

			Assert::AreEqual(circularArray.myFirstIndex, 2);
			Assert::AreEqual(circularArray.myWriteIndex, 2);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 8);
			Assert::AreEqual(circularArray.myData[1], 9);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);
		}

		TEST_METHOD(PushBack_Overflow_Enabled_NonPod)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.PushBack("0");
			circularArray.PushBack("1");
			circularArray.PushBack("2");
			circularArray.PushBack("3");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 4);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			TestUtils::Test_IsStringUninitialized(circularArray.myData[4]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[5]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[6]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[7]);

			circularArray.PushBack("4");
			circularArray.PushBack("5");
			circularArray.PushBack("6");
			circularArray.PushBack("7");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.PushBack("8");

			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 1);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.PushBack("9");

			Assert::AreEqual(circularArray.myFirstIndex, 2);
			Assert::AreEqual(circularArray.myWriteIndex, 2);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "9");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");
		}

		TEST_METHOD(PushBack_Overflow_Disabled_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.DisableOverflow();

			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);
			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			// htodo: automate this
			// Comment out to validate assertion
			//circularArray.PushBack(8);
		}

		TEST_METHOD(PushBack_Overflow_Disabled_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.DisableOverflow();

			circularArray.PushBack("0");
			circularArray.PushBack("1");
			circularArray.PushBack("2");
			circularArray.PushBack("3");
			circularArray.PushBack("4");
			circularArray.PushBack("5");
			circularArray.PushBack("6");
			circularArray.PushBack("7");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			// htodo: automate this
			// Comment out to validate assertion
			//circularArray.PushBack("8");
		}

		TEST_METHOD(PushBack_Move_Overflow_Enabled)
		{
			HD_String string0("0");
			HD_String string1("1");
			HD_String string2("2");
			HD_String string3("3");
			HD_String string4("4");
			HD_String string5("5");
			HD_String string6("6");
			HD_String string7("7");
			HD_String string8("8");
			HD_String string9("9");

			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.PushBack(HD_Move(string0));
			circularArray.PushBack(HD_Move(string1));
			circularArray.PushBack(HD_Move(string2));
			circularArray.PushBack(HD_Move(string3));

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 4);

			TestUtils::Test_IsStringUninitialized(string0);
			TestUtils::Test_IsStringUninitialized(string1);
			TestUtils::Test_IsStringUninitialized(string2);
			TestUtils::Test_IsStringUninitialized(string3);
			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			TestUtils::Test_IsStringUninitialized(circularArray.myData[4]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[5]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[6]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[7]);

			circularArray.PushBack(HD_Move(string4));
			circularArray.PushBack(HD_Move(string5));
			circularArray.PushBack(HD_Move(string6));
			circularArray.PushBack(HD_Move(string7));

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			TestUtils::Test_IsStringUninitialized(string4);
			TestUtils::Test_IsStringUninitialized(string5);
			TestUtils::Test_IsStringUninitialized(string6);
			TestUtils::Test_IsStringUninitialized(string7);
			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.PushBack(HD_Move(string8));

			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 1);
			Assert::AreEqual(circularArray.mySize, 8);

			TestUtils::Test_IsStringUninitialized(string8);
			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.PushBack(HD_Move(string9));

			Assert::AreEqual(circularArray.myFirstIndex, 2);
			Assert::AreEqual(circularArray.myWriteIndex, 2);
			Assert::AreEqual(circularArray.mySize, 8);

			TestUtils::Test_IsStringUninitialized(string9);
			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "9");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");
		}

		TEST_METHOD(PushBack_Move_Overflow_Disabled)
		{
			HD_String string0("0");
			HD_String string1("1");
			HD_String string2("2");
			HD_String string3("3");
			HD_String string4("4");
			HD_String string5("5");
			HD_String string6("6");
			HD_String string7("7");
			HD_String string8("8");
			HD_Unused(string8);

			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.DisableOverflow();

			circularArray.PushBack(HD_Move(string0));
			circularArray.PushBack(HD_Move(string1));
			circularArray.PushBack(HD_Move(string2));
			circularArray.PushBack(HD_Move(string3));
			circularArray.PushBack(HD_Move(string4));
			circularArray.PushBack(HD_Move(string5));
			circularArray.PushBack(HD_Move(string6));
			circularArray.PushBack(HD_Move(string7));

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			TestUtils::Test_IsStringUninitialized(string0);
			TestUtils::Test_IsStringUninitialized(string1);
			TestUtils::Test_IsStringUninitialized(string2);
			TestUtils::Test_IsStringUninitialized(string3);
			TestUtils::Test_IsStringUninitialized(string4);
			TestUtils::Test_IsStringUninitialized(string5);
			TestUtils::Test_IsStringUninitialized(string6);
			TestUtils::Test_IsStringUninitialized(string7);
			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			// htodo: automate this
			// Comment out to validate assertion
			//circularArray.PushBack(HD_Move(string8));
		}

		TEST_METHOD(EmplaceBack_Overflow_Enabled)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.EmplaceBack("0");
			circularArray.EmplaceBack("1");
			circularArray.EmplaceBack("2");
			circularArray.EmplaceBack("3");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 4);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			TestUtils::Test_IsStringUninitialized(circularArray.myData[4]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[5]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[6]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[7]);

			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("5");
			circularArray.EmplaceBack("6");
			circularArray.EmplaceBack("7");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.EmplaceBack("8");

			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 1);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.EmplaceBack("9");

			Assert::AreEqual(circularArray.myFirstIndex, 2);
			Assert::AreEqual(circularArray.myWriteIndex, 2);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "8");
			Assert::IsTrue(circularArray.myData[1] == "9");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");
		}

		TEST_METHOD(EmplaceBack_Overflow_Disabled)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.DisableOverflow();

			circularArray.EmplaceBack("0");
			circularArray.EmplaceBack("1");
			circularArray.EmplaceBack("2");
			circularArray.EmplaceBack("3");
			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("5");
			circularArray.EmplaceBack("6");
			circularArray.EmplaceBack("7");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			// htodo: automate this
			// Comment out to validate assertion
			//circularArray.EmplaceBack("8");
		}

		TEST_METHOD(GetFirstAndRemove_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(4);
			circularArray.PushBack(4);
			circularArray.PushBack(4);
			circularArray.PushBack(4);

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);

			Assert::AreEqual(i, 4);
			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 3);

			Assert::AreEqual(circularArray.myData[0], 4);
			Assert::AreEqual(circularArray.myData[1], 4);
			Assert::AreEqual(circularArray.myData[2], 4);
			Assert::AreEqual(circularArray.myData[3], 4);
			Assert::AreEqual(circularArray.myData[4], 0);
			Assert::AreEqual(circularArray.myData[5], 0);
			Assert::AreEqual(circularArray.myData[6], 0);
			Assert::AreEqual(circularArray.myData[7], 0);
		}

		TEST_METHOD(GetFirstAndRemove_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("4");

			HD_String string;
			circularArray.GetFirstAndRemove(string);

			Assert::IsTrue(string == "4");
			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 3);

			Assert::IsTrue(circularArray.myData[0] == "4");
			Assert::IsTrue(circularArray.myData[1] == "4");
			Assert::IsTrue(circularArray.myData[2] == "4");
			Assert::IsTrue(circularArray.myData[3] == "4");
			TestUtils::Test_IsStringUninitialized(circularArray.myData[4]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[5]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[6]);
			TestUtils::Test_IsStringUninitialized(circularArray.myData[7]);
		}

		TEST_METHOD(Clear_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);
			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.Clear();

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);
		}

		TEST_METHOD(Clear_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.EmplaceBack("0");
			circularArray.EmplaceBack("1");
			circularArray.EmplaceBack("2");
			circularArray.EmplaceBack("3");
			circularArray.EmplaceBack("4");
			circularArray.EmplaceBack("5");
			circularArray.EmplaceBack("6");
			circularArray.EmplaceBack("7");

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");

			circularArray.Clear();

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);

			Assert::IsTrue(circularArray.myData[0] == "0");
			Assert::IsTrue(circularArray.myData[1] == "1");
			Assert::IsTrue(circularArray.myData[2] == "2");
			Assert::IsTrue(circularArray.myData[3] == "3");
			Assert::IsTrue(circularArray.myData[4] == "4");
			Assert::IsTrue(circularArray.myData[5] == "5");
			Assert::IsTrue(circularArray.myData[6] == "6");
			Assert::IsTrue(circularArray.myData[7] == "7");
		}

		TEST_METHOD(GetSize_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			Assert::AreEqual(circularArray.GetSize(), 0);

			circularArray.PushBack(0);
			Assert::AreEqual(circularArray.GetSize(), 1);

			circularArray.PushBack(1);
			Assert::AreEqual(circularArray.GetSize(), 2);

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);
			Assert::AreEqual(circularArray.GetSize(), 1);
		}

		TEST_METHOD(GetSize_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			Assert::AreEqual(circularArray.GetSize(), 0);

			circularArray.EmplaceBack("0");
			Assert::AreEqual(circularArray.GetSize(), 1);

			circularArray.EmplaceBack("1");
			Assert::AreEqual(circularArray.GetSize(), 2);

			HD_String string;
			circularArray.GetFirstAndRemove(string);
			Assert::AreEqual(circularArray.GetSize(), 1);
		}

		TEST_METHOD(GetCapacity_POD)
		{
			{
				HD_CircularArray<s32, 8> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 8);
			}

			{
				HD_CircularArray<s32, 16> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 16);
			}
		}

		TEST_METHOD(GetCapacity_NonPOD)
		{
			{
				HD_CircularArray<HD_String, 8> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 8);
			}

			{
				HD_CircularArray<HD_String, 16> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 16);
			}
		}

		TEST_METHOD(GetIsEmpty_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			Assert::IsTrue(circularArray.GetIsEmpty());

			circularArray.PushBack(0);
			Assert::IsFalse(circularArray.GetIsEmpty());

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);
			Assert::IsTrue(circularArray.GetIsEmpty());
		}

		TEST_METHOD(GetIsEmpty_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			Assert::IsTrue(circularArray.GetIsEmpty());

			circularArray.EmplaceBack("0");
			Assert::IsFalse(circularArray.GetIsEmpty());

			HD_String string;
			circularArray.GetFirstAndRemove(string);
			Assert::IsTrue(circularArray.GetIsEmpty());
		}

		TEST_METHOD(EnableOverflow_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.EnableOverflow();
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<s32, 8>::eOverflowBehaviour_Enable));
		}

		TEST_METHOD(EnableOverflow_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.EnableOverflow();
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<HD_String, 8>::eOverflowBehaviour_Enable));
		}

		TEST_METHOD(DisableOverflow_POD)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.DisableOverflow();
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<s32, 8>::eOverflowBehaviour_Disable));
		}

		TEST_METHOD(DisableOverflow_NonPOD)
		{
			HD_CircularArray<HD_String, 8> circularArray;
			circularArray.DisableOverflow();
			Assert::AreEqual(static_cast<char>(circularArray.myOverflowBehaviour), static_cast<char>(HD_CircularArray<HD_String, 8>::eOverflowBehaviour_Disable));
		}
	};
}
