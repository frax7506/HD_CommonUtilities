#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_ExeArgs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_ExeArgs_Test)
	{
	public:
		TEST_METHOD(Init)
		{
			Assert::IsTrue(false); // wip
		}
	};
}
