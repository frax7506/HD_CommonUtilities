#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_String_Test)
	{
	public:
		TEST_METHOD(Constructor_NonWide)
		{
			HD_String string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);
		}

		TEST_METHOD(Constructor_Wide)
		{
			HD_WString string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);
		}

		TEST_METHOD(Constructor_CString_NonWide)
		{
			HD_String string("haha");
			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);
		}

		TEST_METHOD(Constructor_CString_Wide)
		{
			HD_WString string(L"haha");
			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);
		}

		TEST_METHOD(Consturctor_Copy_NonWide)
		{
			HD_String string1("haha");
			HD_String string2(string1);

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Consturctor_Copy_Wide)
		{
			HD_WString string1(L"haha");
			HD_WString string2(string1);

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Consturctor_Copy_NonWide_Empty)
		{
			HD_String string1;
			HD_String string2(string1);

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Consturctor_Copy_Wide_Empty)
		{
			HD_WString string1;
			HD_WString string2(string1);

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Constructor_Move_NonWide)
		{
			HD_String string1("haha");
			HD_String string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Constructor_Move_Wide)
		{
			HD_WString string1(L"haha");
			HD_WString string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Constructor_Move_NonWide_Empty)
		{
			HD_String string1;
			HD_String string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Constructor_Move_Wide_Empty)
		{
			HD_WString string1;
			HD_WString string2(HD_Move(string1));

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Destructor_NonWide)
		{
			HD_String string("haha");
			string.~HD_String();

			Assert::IsNull(string.myData);
		}

		TEST_METHOD(Destructor_Wide)
		{
			HD_WString string(L"haha");
			string.~HD_WString();

			Assert::IsNull(string.myData);
		}

		TEST_METHOD(GetBuffer_NonWide)
		{
			HD_String string1("haha");
			const char* buffer = string1.GetBuffer();
			Assert::AreEqual(memcmp(buffer, "haha", 4), 0);
		}

		TEST_METHOD(GetBuffer_Wide)
		{
			HD_WString string1(L"haha");
			const wchar_t* buffer = string1.GetBuffer();
			Assert::AreEqual(memcmp(buffer, L"haha", 4 * sizeof(wchar_t)), 0);
		}

		TEST_METHOD(GetBufferWritable_NonWide)
		{
			HD_String string1("haha");
			char* buffer = string1.GetBufferWritable();
			Assert::AreEqual(memcmp(buffer, "haha", 4), 0);
		}

		TEST_METHOD(GetBufferWritable_Wide)
		{
			HD_WString string1(L"haha");
			wchar_t* buffer = string1.GetBufferWritable();
			Assert::AreEqual(memcmp(buffer, L"haha", 4 * sizeof(wchar_t)), 0);
		}

		TEST_METHOD(GetLength_NonWide)
		{
			HD_String string("haha");
			Assert::AreEqual(string.GetLength(), 4);
		}

		TEST_METHOD(GetLength_Wide)
		{
			HD_WString string(L"haha");
			Assert::AreEqual(string.GetLength(), 4);
		}

		TEST_METHOD(GetChatAt_NonWide)
		{
			HD_String string("abcdef");
			Assert::AreEqual(string.GetCharAt(0), 'a');
			Assert::AreEqual(string.GetCharAt(1), 'b');
			Assert::AreEqual(string.GetCharAt(2), 'c');
			Assert::AreEqual(string.GetCharAt(3), 'd');
			Assert::AreEqual(string.GetCharAt(4), 'e');
			Assert::AreEqual(string.GetCharAt(5), 'f');
		}

		TEST_METHOD(GetChatAt_Wide)
		{
			HD_WString string(L"abcdef");
			Assert::AreEqual(string.GetCharAt(0), L'a');
			Assert::AreEqual(string.GetCharAt(1), L'b');
			Assert::AreEqual(string.GetCharAt(2), L'c');
			Assert::AreEqual(string.GetCharAt(3), L'd');
			Assert::AreEqual(string.GetCharAt(4), L'e');
			Assert::AreEqual(string.GetCharAt(5), L'f');
		}

		TEST_METHOD(Append_CString_NonWide)
		{
			HD_String string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);

			string.Append("haha");

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 7);

			string.Append("ha");

			Assert::IsTrue(string == "hahaha");
			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 7);
		}

		TEST_METHOD(Append_CString_Wide)
		{
			HD_WString string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);

			string.Append(L"haha");

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 7);

			string.Append(L"ha");

			Assert::IsTrue(string == L"hahaha");
			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 7);
		}

		TEST_METHOD(Append_HD_String_NonWide)
		{
			HD_String string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);

			HD_String string1("haha");
			string.Append(string1);

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 7);

			HD_String string2("ha");
			string.Append(string2);

			Assert::IsTrue(string == "hahaha");
			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 7);
		}

		TEST_METHOD(Append_HD_String_Wide)
		{
			HD_WString string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);

			HD_WString string1(L"haha");
			string.Append(string1);

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 7);

			HD_WString string2(L"ha");
			string.Append(string2);

			Assert::IsTrue(string == L"hahaha");
			Assert::AreEqual(string.myLength, 6);
			Assert::AreEqual(string.myCapacity, 7);
		}

		TEST_METHOD(Operator_Addition_NonWide)
		{
			HD_String string1("haha");
			HD_String string2("hehe");

			{
				HD_String string3 = string1 + string2;

				Assert::IsTrue(string3 == "hahahehe");
				Assert::AreEqual(string3.myLength, 8);
				Assert::AreEqual(string3.myCapacity, 13);
			}

			{
				HD_String string3 = string1 + " ";

				Assert::IsTrue(string3 == "haha ");
				Assert::AreEqual(string3.myLength, 5);
				Assert::AreEqual(string3.myCapacity, 8);
			}

			{
				HD_String string3 = " " + string1;

				Assert::IsTrue(string3 == " haha");
				Assert::AreEqual(string3.myLength, 5);
				Assert::AreEqual(string3.myCapacity, 8);
			}
		}

		TEST_METHOD(Operator_Addition_Wide)
		{
			HD_WString string1(L"haha");
			HD_WString string2(L"hehe");

			{
				HD_WString string3 = string1 + string2;

				Assert::IsTrue(string3 == L"hahahehe");
				Assert::AreEqual(string3.myLength, 8);
				Assert::AreEqual(string3.myCapacity, 13);
			}

			{
				HD_WString string3 = string1 + L" ";

				Assert::IsTrue(string3 == L"haha ");
				Assert::AreEqual(string3.myLength, 5);
				Assert::AreEqual(string3.myCapacity, 8);
			}

			{
				HD_WString string3 = L" " + string1;

				Assert::IsTrue(string3 == L" haha");
				Assert::AreEqual(string3.myLength, 5);
				Assert::AreEqual(string3.myCapacity, 8);
			}
		}

		TEST_METHOD(Operator_Assignment_CString_NonWide)
		{
			HD_String string;
			string = "haha";

			Assert::IsTrue(string == "haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_CString_Wide)
		{
			HD_WString string;
			string = L"haha";

			Assert::IsTrue(string == L"haha");
			Assert::AreEqual(string.myLength, 4);
			Assert::AreEqual(string.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_CString_NonWide_Empty)
		{
			HD_String string;
			string = "";

			Assert::IsTrue(string == "");
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);
		}

		TEST_METHOD(Operator_Assignment_CString_Wide_Empty)
		{
			HD_WString string;
			string = L"";

			Assert::IsTrue(string == L"");
			Assert::AreEqual(string.myLength, 0);
			Assert::AreEqual(string.myCapacity, 0);
		}

		TEST_METHOD(Operator_Assignment_HD_String_NonWide)
		{
			HD_String string1("haha");
			
			HD_String string2;
			string2 = string1;

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_HD_String_Wide)
		{
			HD_WString string1(L"haha");

			HD_WString string2;
			string2 = string1;

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_HD_String_NonWide_Empty)
		{
			HD_String string1;

			HD_String string2;
			string2 = string1;

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Operator_Assignment_HD_String_Wide_Empty)
		{
			HD_WString string1;

			HD_WString string2;
			string2 = string1;

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Operator_Assignment_Move_NonWide)
		{
			HD_String string1("haha");

			HD_String string2;
			string2 = HD_Move(string1);

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == "haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_Move_Wide)
		{
			HD_WString string1(L"haha");

			HD_WString string2;
			string2 = HD_Move(string1);

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == L"haha");
			Assert::AreEqual(string2.myLength, 4);
			Assert::AreEqual(string2.myCapacity, 5);
		}

		TEST_METHOD(Operator_Assignment_Move_NonWide_Emtpy)
		{
			HD_String string1;

			HD_String string2;
			string2 = HD_Move(string1);

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == "");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Operator_Assignment_Move_Wide_Emtpy)
		{
			HD_WString string1;

			HD_WString string2;
			string2 = HD_Move(string1);

			Assert::IsNull(string1.myData);
			Assert::AreEqual(string1.myLength, 0);
			Assert::AreEqual(string1.myCapacity, 0);

			Assert::IsTrue(string2 == L"");
			Assert::AreEqual(string2.myLength, 0);
			Assert::AreEqual(string2.myCapacity, 0);
		}

		TEST_METHOD(Operator_Equals_CString_NonWide)
		{
			HD_String string("haha");
			Assert::IsTrue(string == "haha");
			Assert::IsFalse(string == "hehe");
		}

		TEST_METHOD(Operator_Equals_CString_Wide)
		{
			HD_WString string(L"haha");
			Assert::IsTrue(string == L"haha");
			Assert::IsFalse(string == L"hehe");
		}

		TEST_METHOD(Operator_Equals_CString_NonWide_Empty)
		{
			HD_String string;
			Assert::IsTrue(string == "");
			Assert::IsFalse(string == "haha");
		}

		TEST_METHOD(Operator_Equals_CString_Wide_Empty)
		{
			HD_WString string;
			Assert::IsTrue(string == L"");
			Assert::IsFalse(string == L"haha");
		}

		TEST_METHOD(Operator_Equals_HD_String_NonWide)
		{
			HD_String string1("haha");
			HD_String string2("haha");
			HD_String string3("hehe");
			Assert::IsTrue(string1 == string2);
			Assert::IsFalse(string1 == string3);
		}

		TEST_METHOD(Operator_Equals_HD_String_Wide)
		{
			HD_WString string1(L"haha");
			HD_WString string2(L"haha");
			HD_WString string3(L"hehe");
			Assert::IsTrue(string1 == string2);
			Assert::IsFalse(string1 == string3);
		}

		TEST_METHOD(Operator_Equals_HD_String_NonWide_Empty)
		{
			// Empty as lhs
			{
				HD_String string1;
				HD_String string2("haha");
				Assert::IsTrue(string1 == "");
				Assert::IsFalse(string1 == string2);
			}

			// Empty as rhs
			{
				HD_String string1("haha");
				HD_String string2;
				Assert::IsTrue(string1 == "haha");
				Assert::IsFalse(string1 == string2);
			}
		}

		TEST_METHOD(Operator_Equals_HD_String_Wide_Empty)
		{
			// Empty as lhs
			{
				HD_WString string1;
				HD_WString string2(L"haha");
				Assert::IsTrue(string1 == L"");
				Assert::IsFalse(string1 == string2);
			}

			// Empty as rhs
			{
				HD_WString string1(L"haha");
				HD_WString string2;
				Assert::IsTrue(string1 == L"haha");
				Assert::IsFalse(string1 == string2);
			}
		}

		TEST_METHOD(Operator_Not_Equals_CString_NonWide)
		{
			HD_String string("haha");
			Assert::IsTrue(string != "hehe");
			Assert::IsFalse(string != "haha");
		}

		TEST_METHOD(Operator_Not_Equals_CString_Wide)
		{
			HD_WString string(L"haha");
			Assert::IsTrue(string != L"hehe");
			Assert::IsFalse(string != L"haha");
		}

		TEST_METHOD(Operator_Not_Equals_CString_NonWide_Empty)
		{
			HD_String string1("haha");
			Assert::IsTrue(string1 != "");
			Assert::IsFalse(string1 != "haha");

			HD_String string2;
			Assert::IsTrue(string2 != "haha");
			Assert::IsFalse(string2 != "");
		}

		TEST_METHOD(Operator_Not_Equals_CString_Wide_Empty)
		{
			HD_WString string1(L"haha");
			Assert::IsTrue(string1 != L"");
			Assert::IsFalse(string1 != L"haha");

			HD_WString string2;
			Assert::IsTrue(string2 != L"haha");
			Assert::IsFalse(string2 != L"");
		}

		TEST_METHOD(Operator_Not_Equals_HD_String_NonWide)
		{
			HD_String string1("haha");
			HD_String string2("hehe");
			HD_String string3("haha");
			Assert::IsTrue(string1 != string2);
			Assert::IsFalse(string1 != string3);
		}

		TEST_METHOD(Operator_Not_Equals_HD_String_Wide)
		{
			HD_WString string1(L"haha");
			HD_WString string2(L"hehe");
			HD_WString string3(L"haha");
			Assert::IsTrue(string1 != string2);
			Assert::IsFalse(string1 != string3);
		}

		TEST_METHOD(Operator_Not_Equals_HD_String_NonWide_Empty)
		{
			// Empty as lhs
			{
				HD_String string1;
				HD_String string2("haha");
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != "");
			}

			// Empty as rhs
			{
				HD_String string1("haha");
				HD_String string2;
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != "haha");
			}
		}

		TEST_METHOD(Operator_Not_Equals_HD_String_Wide_Empty)
		{
			// Empty as lhs
			{
				HD_WString string1;
				HD_WString string2(L"haha");
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != L"");
			}

			// Empty as rhs
			{
				HD_WString string1(L"haha");
				HD_WString string2;
				Assert::IsTrue(string1 != string2);
				Assert::IsFalse(string1 != L"haha");
			}
		}
	};
}
