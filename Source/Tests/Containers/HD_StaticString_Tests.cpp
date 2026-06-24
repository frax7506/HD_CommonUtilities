#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_StaticString.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_StaticString_Test)
	{
	public:
		TEST_METHOD(Constructor_NonWide)
		{
			HD_StaticString<8> string;
			TestUtils::StaticString_IsUninitialized(string);
		}

		TEST_METHOD(Constructor_Wide)
		{
			HD_StaticWString<8> string;
			TestUtils::StaticString_IsUninitialized(string);
		}

		TEST_METHOD(Constructor_CString_NonWide)
		{
			HD_StaticString<8> string("haha");
			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Constructor_CString_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Consturctor_Copy_NonWide)
		{
			HD_StaticString<8> string1("haha");
			HD_StaticString<8> string2(string1);

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.GetLength(), 4);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Consturctor_Copy_Wide)
		{
			HD_StaticWString<8> string1(L"haha");
			HD_StaticWString<8> string2(string1);

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.GetLength(), 4);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Consturctor_Copy_NonWide_Empty)
		{
			HD_StaticString<8> string1;
			HD_StaticString<8> string2(string1);

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.GetLength(), 0);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Consturctor_Copy_Wide_Empty)
		{
			HD_StaticWString<8> string1;
			HD_StaticWString<8> string2(string1);

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.GetLength(), 0);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(GetBuffer_NonWide)
		{
			HD_StaticString<8> string("haha");
			const char* buffer = string.GetBuffer();
			Assert::AreEqual(memcmp(buffer, "haha", 4), 0);
		}

		TEST_METHOD(GetBuffer_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			const wchar_t* buffer = string.GetBuffer();
			Assert::AreEqual(memcmp(buffer, L"haha", 4 * sizeof(wchar_t)), 0);
		}

		TEST_METHOD(GetBufferWritable_NonWide)
		{
			HD_StaticString<8> string("haha");
			char* buffer = string.GetBufferWritable();
			Assert::AreEqual(memcmp(buffer, "haha", 4), 0);
		}

		TEST_METHOD(GetBufferWritable_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			wchar_t* buffer = string.GetBufferWritable();
			Assert::AreEqual(memcmp(buffer, L"haha", 4 * sizeof(wchar_t)), 0);
		}

		TEST_METHOD(GetLength_NonWide)
		{
			HD_StaticString<8> string("haha");
			Assert::AreEqual(string.GetLength(), 4);
		}

		TEST_METHOD(GetLength_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			Assert::AreEqual(string.GetLength(), 4);
		}

		TEST_METHOD(GetChatAt_NonWide)
		{
			HD_StaticString<8> string("abcdef");
			Assert::AreEqual(string.GetCharAt(0), 'a');
			Assert::AreEqual(string.GetCharAt(1), 'b');
			Assert::AreEqual(string.GetCharAt(2), 'c');
			Assert::AreEqual(string.GetCharAt(3), 'd');
			Assert::AreEqual(string.GetCharAt(4), 'e');
			Assert::AreEqual(string.GetCharAt(5), 'f');
		}

		TEST_METHOD(GetChatAt_Wide)
		{
			HD_StaticWString<8> string(L"abcdef");
			Assert::AreEqual(string.GetCharAt(0), L'a');
			Assert::AreEqual(string.GetCharAt(1), L'b');
			Assert::AreEqual(string.GetCharAt(2), L'c');
			Assert::AreEqual(string.GetCharAt(3), L'd');
			Assert::AreEqual(string.GetCharAt(4), L'e');
			Assert::AreEqual(string.GetCharAt(5), L'f');
		}

		TEST_METHOD(Append_CString_NonWide)
		{
			HD_StaticString<8> string;
			TestUtils::StaticString_IsUninitialized(string);

			string.Append("haha");

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);

			string.Append("ha");

			Assert::IsTrue(string == "hahaha");
			Assert::AreEqual(string.GetLength(), 6);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Append_CString_Wide)
		{
			HD_StaticWString<8> string;
			TestUtils::StaticString_IsUninitialized(string);

			string.Append(L"haha");

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);

			string.Append(L"ha");

			Assert::IsTrue(string == L"hahaha");
			Assert::AreEqual(string.GetLength(), 6);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Append_HD_StaticString_NonWide)
		{
			HD_StaticString<8> string;
			TestUtils::StaticString_IsUninitialized(string);

			HD_StaticString<8> string1("haha");
			string.Append(string1);

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);

			HD_StaticString<8> string2("ha");
			string.Append(string2);

			Assert::IsTrue(string == "hahaha");
			Assert::AreEqual(string.GetLength(), 6);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Append_HD_StaticString_Wide)
		{
			HD_StaticWString<8> string;
			TestUtils::StaticString_IsUninitialized(string);

			HD_StaticWString<8> string1(L"haha");
			string.Append(string1);

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);

			HD_StaticWString<8> string2(L"ha");
			string.Append(string2);

			Assert::IsTrue(string == L"hahaha");
			Assert::AreEqual(string.GetLength(), 6);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Addition_NonWide)
		{
			HD_StaticString<16> string1("haha");
			HD_StaticString<16> string2("hehe");

			{
				HD_StaticString<16> string3 = string1 + string2;

				Assert::IsTrue(string3 == "hahahehe");
				Assert::AreEqual(string3.GetLength(), 8);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}

			{
				HD_StaticString<16> string3 = string1 + " ";

				Assert::IsTrue(string3 == "haha ");
				Assert::AreEqual(string3.GetLength(), 5);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}

			{
				HD_StaticString<16> string3 = " " + string1;

				Assert::IsTrue(string3 == " haha");
				Assert::AreEqual(string3.GetLength(), 5);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}
		}

		TEST_METHOD(Operator_Addition_Wide)
		{
			HD_StaticWString<16> string1(L"haha");
			HD_StaticWString<16> string2(L"hehe");

			{
				HD_StaticWString<16> string3 = string1 + string2;

				Assert::IsTrue(string3 == L"hahahehe");
				Assert::AreEqual(string3.GetLength(), 8);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}

			{
				HD_StaticWString<16> string3 = string1 + L" ";

				Assert::IsTrue(string3 == L"haha ");
				Assert::AreEqual(string3.GetLength(), 5);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}

			{
				HD_StaticWString<16> string3 = L" " + string1;

				Assert::IsTrue(string3 == L" haha");
				Assert::AreEqual(string3.GetLength(), 5);
				Assert::AreEqual(string3.GetCapacity(), 16);
			}
		}

		TEST_METHOD(Operator_Assignment_CString_NonWide)
		{
			HD_StaticString<8> string;
			string = "haha";

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_CString_Wide)
		{
			HD_StaticWString<8> string;
			string = L"haha";

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.GetLength(), 4);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_CString_NonWide_Empty)
		{
			HD_StaticString<8> string;
			string = "";

			Assert::IsTrue(string == "");
			Assert::AreEqual(string.GetLength(), 0);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_CString_Wide_Empty)
		{
			HD_StaticWString<8> string;
			string = L"";

			Assert::IsTrue(string == L"");
			Assert::AreEqual(string.GetLength(), 0);
			Assert::AreEqual(string.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_HD_StaticString_NonWide)
		{
			HD_StaticString<8> string1("haha");

			HD_StaticString<8> string2;
			string2 = string1;

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.GetLength(), 4);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_HD_StaticString_Wide)
		{
			HD_StaticWString<8> string1(L"haha");

			HD_StaticWString<8> string2;
			string2 = string1;

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.GetLength(), 4);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_HD_StaticString_NonWide_Empty)
		{
			HD_StaticString<8> string1;

			HD_StaticString<8> string2;
			string2 = string1;

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.GetLength(), 0);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Assignment_HD_StaticString_Wide_Empty)
		{
			HD_StaticWString<8> string1;

			HD_StaticWString<8> string2;
			string2 = string1;

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.GetLength(), 0);
			Assert::AreEqual(string2.GetCapacity(), 8);
		}

		TEST_METHOD(Operator_Equals_CString_NonWide)
		{
			HD_StaticString<8> string("haha");
			Assert::IsTrue(string == "haha");
			Assert::IsFalse(string == "hehe");
		}

		TEST_METHOD(Operator_Equals_CString_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			Assert::IsTrue(string == L"haha");
			Assert::IsFalse(string == L"hehe");
		}

		TEST_METHOD(Operator_Equals_CString_NonWide_Empty)
		{
			HD_StaticString<8> string;
			Assert::IsTrue(string == "");
			Assert::IsFalse(string == "haha");
		}

		TEST_METHOD(Operator_Equals_CString_Wide_Empty)
		{
			HD_StaticWString<8> string;
			Assert::IsTrue(string == L"");
			Assert::IsFalse(string == L"haha");
		}

		TEST_METHOD(Operator_Equals_HD_StaticString_NonWide)
		{
			HD_StaticString<8> string1("haha");
			HD_StaticString<8> string2("haha");
			HD_StaticString<8> string3("hehe");
			Assert::IsTrue(string1 == string2);
			Assert::IsFalse(string1 == string3);
		}

		TEST_METHOD(Operator_Equals_HD_StaticString_Wide)
		{
			HD_StaticWString<8> string1(L"haha");
			HD_StaticWString<8> string2(L"haha");
			HD_StaticWString<8> string3(L"hehe");
			Assert::IsTrue(string1 == string2);
			Assert::IsFalse(string1 == string3);
		}

		TEST_METHOD(Operator_Equals_HD_StaticString_NonWide_Empty)
		{
			// Empty as lhs
			{
				HD_StaticString<8> string1;
				HD_StaticString<8> string2("haha");
				Assert::IsTrue(string1 == "");
				Assert::IsFalse(string1 == string2);
			}

			// Empty as rhs
			{
				HD_StaticString<8> string1("haha");
				HD_StaticString<8> string2;
				Assert::IsTrue(string1 == "haha");
				Assert::IsFalse(string1 == string2);
			}
		}

		TEST_METHOD(Operator_Equals_HD_StaticString_Wide_Empty)
		{
			// Empty as lhs
			{
				HD_StaticWString<8> string1;
				HD_StaticWString<8> string2(L"haha");
				Assert::IsTrue(string1 == L"");
				Assert::IsFalse(string1 == string2);
			}

			// Empty as rhs
			{
				HD_StaticWString<8> string1(L"haha");
				HD_StaticWString<8> string2;
				Assert::IsTrue(string1 == L"haha");
				Assert::IsFalse(string1 == string2);
			}
		}

		TEST_METHOD(Operator_Not_Equals_CString_NonWide)
		{
			HD_StaticString<8> string("haha");
			Assert::IsTrue(string != "hehe");
			Assert::IsFalse(string != "haha");
		}

		TEST_METHOD(Operator_Not_Equals_CString_Wide)
		{
			HD_StaticWString<8> string(L"haha");
			Assert::IsTrue(string != L"hehe");
			Assert::IsFalse(string != L"haha");
		}

		TEST_METHOD(Operator_Not_Equals_CString_NonWide_Empty)
		{
			HD_StaticString<8> string1("haha");
			Assert::IsTrue(string1 != "");
			Assert::IsFalse(string1 != "haha");

			HD_StaticString<8> string2;
			Assert::IsTrue(string2 != "haha");
			Assert::IsFalse(string2 != "");
		}

		TEST_METHOD(Operator_Not_Equals_CString_Wide_Empty)
		{
			HD_StaticWString<8> string1(L"haha");
			Assert::IsTrue(string1 != L"");
			Assert::IsFalse(string1 != L"haha");

			HD_StaticWString<8> string2;
			Assert::IsTrue(string2 != L"haha");
			Assert::IsFalse(string2 != L"");
		}

		TEST_METHOD(Operator_Not_Equals_HD_StaticString_NonWide)
		{
			HD_StaticString<8> string1("haha");
			HD_StaticString<8> string2("hehe");
			HD_StaticString<8> string3("haha");
			Assert::IsTrue(string1 != string2);
			Assert::IsFalse(string1 != string3);
		}

		TEST_METHOD(Operator_Not_Equals_HD_StaticString_Wide)
		{
			HD_StaticWString<8> string1(L"haha");
			HD_StaticWString<8> string2(L"hehe");
			HD_StaticWString<8> string3(L"haha");
			Assert::IsTrue(string1 != string2);
			Assert::IsFalse(string1 != string3);
		}

		TEST_METHOD(Operator_Not_Equals_HD_StaticString_NonWide_Empty)
		{
			// Empty as lhs
			{
				HD_StaticString<8> string1;
				HD_StaticString<8> string2("haha");
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != "");
			}

			// Empty as rhs
			{
				HD_StaticString<8> string1("haha");
				HD_StaticString<8> string2;
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != "haha");
			}
		}

		TEST_METHOD(Operator_Not_Equals_HD_StaticString_Wide_Empty)
		{
			// Empty as lhs
			{
				HD_StaticWString<8> string1;
				HD_StaticWString<8> string2(L"haha");
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != L"");
			}

			// Empty as rhs
			{
				HD_StaticWString<8> string1(L"haha");
				HD_StaticWString<8> string2;
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != L"haha");
			}
		}
	};
}
