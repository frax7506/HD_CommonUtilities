#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_String.h"

#include <cstring>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_String_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_String string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);
		}

		TEST_METHOD(Constructor_CString)
		{
			HD_String string("haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer, 5), 0);
		}

		TEST_METHOD(Consturctor_Copy)
		{
			HD_String string1("haha");
			HD_String string2(string1);

			Assert::IsNotNull(string2.myData);
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_String string1("haha");
			HD_String string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}

		TEST_METHOD(Destructor)
		{
			HD_String string("haha");
			string.~HD_String();

			Assert::IsNull(string.myData);
		}

		TEST_METHOD(GetBuffer)
		{
			HD_String string1("haha");
			const char* string2 = string1.GetBuffer();
			Assert::AreEqual(memcmp(string2, "haha", 4), 0);
		}

		TEST_METHOD(GetLength)
		{
			HD_String string("haha");
			Assert::AreEqual(string.GetLength(), 4);
		}

		TEST_METHOD(GetChatAt)
		{
			HD_String string("abcdef");
			Assert::AreEqual(string.GetCharAt(0), 'a');
			Assert::AreEqual(string.GetCharAt(1), 'b');
			Assert::AreEqual(string.GetCharAt(2), 'c');
			Assert::AreEqual(string.GetCharAt(3), 'd');
			Assert::AreEqual(string.GetCharAt(4), 'e');
			Assert::AreEqual(string.GetCharAt(5), 'f');
		}

		TEST_METHOD(Append_CString)
		{
			HD_String string("haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);

			char buffer1[8]{ 0 };
			memcpy(buffer1, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer1, 5), 0);

			string.Append("ha");

			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 10);

			char buffer2[8]{ 0 };
			memcpy(buffer2, "hahaha", 6);
			Assert::AreEqual(memcmp(string.myData, buffer2, 7), 0);
		}

		TEST_METHOD(Append_HD_String)
		{
			HD_String string("haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);

			char buffer1[8]{ 0 };
			memcpy(buffer1, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer1, 5), 0);

			HD_String string2("ha");
			string.Append(string2);

			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 10);

			char buffer2[8]{ 0 };
			memcpy(buffer2, "hahaha", 6);
			Assert::AreEqual(memcmp(string.myData, buffer2, 7), 0);
		}

		TEST_METHOD(Operator_Addition)
		{
			HD_String string1("haha");
			HD_String string2("hehe");

			HD_String string3 = string1 + string2;

			char buffer1[16]{ 0 };
			memcpy(buffer1, "hahahehe", 8);
			Assert::AreEqual(memcmp(string3.myData, buffer1, 9), 0);

			// Global operator+ for <string literal> + aString.
			HD_String string4 = " " + string1;

			char buffer2[16]{ 0 };
			memcpy(buffer2, " haha", 5);
			Assert::AreEqual(memcmp(string4.myData, buffer2, 6), 0);
		}

		TEST_METHOD(Operator_Assignment_CString)
		{
			HD_String string;
			string = "haha";

			Assert::IsNotNull(string.myData);
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer, 5), 0);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_String string1("haha");
			
			HD_String string2;
			string2 = string1;

			Assert::IsNotNull(string2.myData);
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			HD_String string1("haha");

			HD_String string2;
			string2 = HD_Move(string1);

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}

		TEST_METHOD(Operator_Equals_CString)
		{
			HD_String string("haha");
			bool isEqual1 = string == "haha";
			bool isEqual2 = string == "hehe";
			Assert::IsTrue(isEqual1);
			Assert::IsFalse(isEqual2);
		}

		TEST_METHOD(Operator_Equals_HD_String)
		{
			HD_String string1("haha");
			HD_String string2("haha");
			HD_String string3("hehe");
			bool isEqual1 = string1 == string2;
			bool isEqual2 = string1 == string3;
			Assert::IsTrue(isEqual1);
			Assert::IsFalse(isEqual2);
		}

		TEST_METHOD(Operator_Not_Equals_CString)
		{
			HD_String string("haha");
			bool isEqual1 = string != "hehe";
			bool isEqual2 = string != "haha";
			Assert::IsTrue(isEqual1);
			Assert::IsFalse(isEqual2);
		}

		TEST_METHOD(Operator_Not_Equals_HD_String)
		{
			HD_String string1("haha");
			HD_String string2("hehe");
			HD_String string3("haha");
			bool isEqual1 = string1 != string2;
			bool isEqual2 = string1 != string3;
			Assert::IsTrue(isEqual1);
			Assert::IsFalse(isEqual2);
		}
	};
}
