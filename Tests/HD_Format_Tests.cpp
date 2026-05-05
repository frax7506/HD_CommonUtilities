#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_Format.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Format_Test)
	{
	public:

		TEST_METHOD(Constructor_NonWide)
		{
			const char* formattedString = HD_Format("%i %.2f %s", 9, 2.25f, "haha").GetBuffer();
			Assert::IsTrue(memcmp(formattedString, "9 2.25 haha", 11) == 0);
		}

		TEST_METHOD(Constructor_Wide)
		{
			const wchar_t* formattedString = HD_Format(L"%i %.2f %s", 9, 2.25f, L"haha").GetBuffer();
			Assert::IsTrue(memcmp(formattedString, L"9 2.25 haha", 22) == 0);
		}
	};
}