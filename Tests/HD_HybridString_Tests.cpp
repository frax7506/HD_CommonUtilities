#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_HybridString.h"

#include <cstring>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_HybridString_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_HybridString string;
			Assert::IsNull(string.myData);
			Assert::AreEqual(static_cast<char>(string.myMode), static_cast<char>(HD_HybridString::StringMode_Invalid));
		}

		TEST_METHOD(Constructor_NonWide)
		{
			HD_HybridString string("haha");

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(string.myData, buffer, 5), 0);

			Assert::AreEqual(static_cast<char>(string.myMode), static_cast<char>(HD_HybridString::StringMode_NonWide));
		}

		TEST_METHOD(Constructor_Wide)
		{
			HD_HybridString string(L"haha");

			wchar_t buffer[8]{ 0 };
			memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
			Assert::AreEqual(memcmp(string.myData, buffer, sizeof(wchar_t) * 5), 0);

			Assert::AreEqual(static_cast<char>(string.myMode), static_cast<char>(HD_HybridString::StringMode_Wide));
		}

		TEST_METHOD(Destructor)
		{
			{
				HD_HybridString string("haha");
				string.~HD_HybridString();

				Assert::IsNull(string.myData);
			}

			{
				HD_HybridString string(L"haha");
				string.~HD_HybridString();

				Assert::IsNull(string.myData);
			}
		}

		TEST_METHOD(GetBuffer)
		{
			HD_HybridString string1("haha");
			const char* string2 = string1.GetBuffer();
			Assert::AreEqual(memcmp(string2, "haha", 4), 0);

			// Should trigger assert
			//const wchar_t* assertTest = string1.GetWBuffer();
			//HD_Unused(assertTest);
		}

		TEST_METHOD(GetWBuffer)
		{
			HD_HybridString string1(L"haha");
			const wchar_t* string2 = string1.GetWBuffer();
			Assert::AreEqual(memcmp(string2, L"haha", sizeof(wchar_t) * 4), 0);

			// Should trigger assert
			//const char* assertTest = string1.GetBuffer();
			//HD_Unused(assertTest);
		}

		TEST_METHOD(GetIsWide)
		{
			HD_HybridString nonWide("haha");
			HD_HybridString wide(L"haha");

			Assert::IsFalse(nonWide.GetIsWide());
			Assert::IsTrue(wide.GetIsWide());
		}
	};
}
