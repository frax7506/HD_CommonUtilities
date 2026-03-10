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
			Assert::AreEqual(string.GetLength(), 0);
			Assert::IsNull(string.myData);
		}

		TEST_METHOD(Constructor_CString)
		{
			HD_String string("haha");
			u32 length = string.GetLength();
			Assert::AreEqual(length, 4u);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer, 5), 0);
		}

		TEST_METHOD(Consturctor_Copy)
		{
			HD_String string1("haha");
			HD_String string2(string1);

			Assert::IsNotNull(string2.myData);
			Assert::AreEqual(string2.GetLength(), 4);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_String string1("haha");
			HD_String string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string2.GetLength(), 4);

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
			u32 length = string.GetLength();
			Assert::AreEqual(length, 4u);
		}

		TEST_METHOD(Operator_Assignment_CString)
		{
			HD_String string;
			string = "haha";

			Assert::IsNotNull(string.myData);
			Assert::AreEqual(string.GetLength(), 4);

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
			Assert::AreEqual(string2.GetLength(), 4);

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
			Assert::AreEqual(string2.GetLength(), 4);

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string2.myData, buffer, 5), 0);
		}
	};
}
