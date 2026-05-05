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
		TEST_METHOD(Constructor)
		{
			{
				HD_String string;
				Assert::AreEqual(*string.myData, static_cast<char>(0));
				Assert::AreEqual(string.myLength, 0);
				Assert::AreEqual(string.myCapacity, 1);
			}

			{
				HD_WString string;
				Assert::AreEqual(*string.myData, static_cast<wchar_t>(0));
				Assert::AreEqual(string.myLength, 0);
				Assert::AreEqual(string.myCapacity, 1);
			}
		}

		TEST_METHOD(Constructor_CString)
		{
			{
				HD_String string("haha");
				Assert::AreEqual(string.myLength, 4);
				Assert::AreEqual(string.myCapacity, 5);

				char buffer[8]{ 0 };
				memcpy(buffer, "haha", 4);
				Assert::AreEqual(memcmp(string.myData, buffer, 5), 0);
			}

			{
				HD_WString string(L"haha");
				Assert::AreEqual(string.myLength, 4);
				Assert::AreEqual(string.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Consturctor_Copy)
		{
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

			{
				HD_WString string1(L"haha");
				HD_WString string2(string1);

				Assert::IsNotNull(string2.myData);
				Assert::AreEqual(string2.myLength, 4);
				Assert::AreEqual(string2.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string2.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Constructor_Move)
		{
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

			{
				HD_WString string1(L"haha");
				HD_WString string2(HD_Move(string1));

				Assert::IsNull(string1.myData);
				Assert::AreEqual(string2.myLength, 4);
				Assert::AreEqual(string2.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string2.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Destructor)
		{
			{
				HD_String string("haha");
				string.~HD_String();

				Assert::IsNull(string.myData);
			}

			{
				HD_WString string(L"haha");
				string.~HD_WString();

				Assert::IsNull(string.myData);
			}
		}

		TEST_METHOD(GetBuffer)
		{
			{
				HD_String string1("haha");
				const char* string2 = string1.GetBuffer();
				Assert::AreEqual(memcmp(string2, "haha", 4), 0);
			}

			{
				HD_WString string1(L"haha");
				const wchar_t* string2 = string1.GetBuffer();
				Assert::AreEqual(memcmp(string2, L"haha", sizeof(wchar_t) * 4), 0);
			}
		}

		TEST_METHOD(GetLength)
		{
			{
				HD_String string("haha");
				Assert::AreEqual(string.GetLength(), 4);
			}

			{
				HD_WString string(L"haha");
				Assert::AreEqual(string.GetLength(), 4);
			}
		}

		TEST_METHOD(GetChatAt)
		{
			{
				HD_String string("abcdef");
				Assert::AreEqual(string.GetCharAt(0), 'a');
				Assert::AreEqual(string.GetCharAt(1), 'b');
				Assert::AreEqual(string.GetCharAt(2), 'c');
				Assert::AreEqual(string.GetCharAt(3), 'd');
				Assert::AreEqual(string.GetCharAt(4), 'e');
				Assert::AreEqual(string.GetCharAt(5), 'f');
			}

			{
				HD_WString string(L"abcdef");
				Assert::AreEqual(string.GetCharAt(0), L'a');
				Assert::AreEqual(string.GetCharAt(1), L'b');
				Assert::AreEqual(string.GetCharAt(2), L'c');
				Assert::AreEqual(string.GetCharAt(3), L'd');
				Assert::AreEqual(string.GetCharAt(4), L'e');
				Assert::AreEqual(string.GetCharAt(5), L'f');
			}
		}

		TEST_METHOD(Append_CString)
		{
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

			{
				HD_WString string(L"haha");
				Assert::AreEqual(string.myLength, 4);
				Assert::AreEqual(string.myCapacity, 5);

				wchar_t buffer1[8]{ 0 };
				memcpy(buffer1, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string.myData, buffer1, sizeof(wchar_t) * 5), 0);

				string.Append(L"ha");

				Assert::AreEqual(string.myLength, 6);
				Assert::AreEqual(string.myCapacity, 10);

				wchar_t buffer2[8]{ 0 };
				memcpy(buffer2, L"hahaha", sizeof(wchar_t) * 6);
				Assert::AreEqual(memcmp(string.myData, buffer2, sizeof(wchar_t) * 7), 0);
			}
		}

		TEST_METHOD(Append_HD_String)
		{
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

			{
				HD_WString string(L"haha");
				Assert::AreEqual(string.myLength, 4);
				Assert::AreEqual(string.myCapacity, 5);

				wchar_t buffer1[8]{ 0 };
				memcpy(buffer1, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string.myData, buffer1, sizeof(wchar_t) * 5), 0);

				HD_WString string2(L"ha");
				string.Append(string2);

				Assert::AreEqual(string.myLength, 6);
				Assert::AreEqual(string.myCapacity, 10);

				wchar_t buffer2[8]{ 0 };
				memcpy(buffer2, L"hahaha", sizeof(wchar_t) * 6);
				Assert::AreEqual(memcmp(string.myData, buffer2, sizeof(wchar_t) * 7), 0);
			}
		}

		TEST_METHOD(Operator_Addition)
		{
			{
				HD_String string1("haha");
				HD_String string2("hehe");

				{
					HD_String string3 = string1 + string2;

					char buffer[16]{ 0 };
					memcpy(buffer, "hahahehe", 8);
					Assert::AreEqual(memcmp(string3.myData, buffer, 9), 0);
				}

				{
					HD_String string3 = string1 + " ";

					char buffer[16]{ 0 };
					memcpy(buffer, "haha ", 5);
					Assert::AreEqual(memcmp(string3.myData, buffer, 6), 0);
				}

				{
					// Global operator+ for <string literal> + aString.
					HD_String string3 = " " + string1;

					char buffer[16]{ 0 };
					memcpy(buffer, " haha", 5);
					Assert::AreEqual(memcmp(string3.myData, buffer, 6), 0);
				}
			}

			{
				HD_WString string1(L"haha");
				HD_WString string2(L"hehe");

				{
					HD_WString string3 = string1 + string2;

					wchar_t buffer[16]{ 0 };
					memcpy(buffer, L"hahahehe", sizeof(wchar_t) * 8);
					Assert::AreEqual(memcmp(string3.myData, buffer, sizeof(wchar_t) * 9), 0);
				}

				{
					HD_WString string3 = string1 + L" ";

					wchar_t buffer[16]{ 0 };
					memcpy(buffer, L"haha ", sizeof(wchar_t) * 5);
					Assert::AreEqual(memcmp(string3.myData, buffer, sizeof(wchar_t) * 6), 0);
				}

				{
					// Global operator+ for <string literal> + aString.
					HD_WString string3 = L" " + string1;

					wchar_t buffer[16]{ 0 };
					memcpy(buffer, L" haha", sizeof(wchar_t) * 5);
					Assert::AreEqual(memcmp(string3.myData, buffer, sizeof(wchar_t) * 6), 0);
				}
			}
		}

		TEST_METHOD(Operator_Assignment_CString)
		{
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

			{
				HD_WString string;
				string = L"haha";

				Assert::IsNotNull(string.myData);
				Assert::AreEqual(string.myLength, 4);
				Assert::AreEqual(string.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
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

			{
				HD_WString string1(L"haha");

				HD_WString string2;
				string2 = string1;

				Assert::IsNotNull(string2.myData);
				Assert::AreEqual(string2.myLength, 4);
				Assert::AreEqual(string2.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string2.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
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

			{
				HD_WString string1(L"haha");

				HD_WString string2;
				string2 = HD_Move(string1);

				Assert::IsNull(string1.myData);
				Assert::AreEqual(string2.myLength, 4);
				Assert::AreEqual(string2.myCapacity, 5);

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(string2.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
		}

		TEST_METHOD(Operator_Equals_CString)
		{
			{
				HD_String string("haha");
				bool isEqual1 = string == "haha";
				bool isEqual2 = string == "hehe";
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}

			{
				HD_WString string(L"haha");
				bool isEqual1 = string == L"haha";
				bool isEqual2 = string == L"hehe";
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}
		}

		TEST_METHOD(Operator_Equals_HD_String)
		{
			{
				HD_String string1("haha");
				HD_String string2("haha");
				HD_String string3("hehe");
				bool isEqual1 = string1 == string2;
				bool isEqual2 = string1 == string3;
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}

			{
				HD_WString string1(L"haha");
				HD_WString string2(L"haha");
				HD_WString string3(L"hehe");
				bool isEqual1 = string1 == string2;
				bool isEqual2 = string1 == string3;
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}
		}

		TEST_METHOD(Operator_Not_Equals_CString)
		{
			{
				HD_String string("haha");
				bool isEqual1 = string != "hehe";
				bool isEqual2 = string != "haha";
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}

			{
				HD_WString string(L"haha");
				bool isEqual1 = string != L"hehe";
				bool isEqual2 = string != L"haha";
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}
		}

		TEST_METHOD(Operator_Not_Equals_HD_String)
		{
			{
				HD_String string1("haha");
				HD_String string2("hehe");
				HD_String string3("haha");
				bool isEqual1 = string1 != string2;
				bool isEqual2 = string1 != string3;
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}

			{
				HD_WString string1(L"haha");
				HD_WString string2(L"hehe");
				HD_WString string3(L"haha");
				bool isEqual1 = string1 != string2;
				bool isEqual2 = string1 != string3;
				Assert::IsTrue(isEqual1);
				Assert::IsFalse(isEqual2);
			}
		}
	};
}
