#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_IsFundamental.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_IsFundamental_Test)
	{
	public:
		TEST_METHOD(IsFundamental)
		{
			struct CustomType
			{
			};

			Assert::IsFalse(HD_IsFundamental<CustomType>::Result);

			Assert::IsTrue(HD_IsFundamental<s8>::Result);
			Assert::IsTrue(HD_IsFundamental<u8>::Result);
			Assert::IsTrue(HD_IsFundamental<s16>::Result);
			Assert::IsTrue(HD_IsFundamental<u16>::Result);
			Assert::IsTrue(HD_IsFundamental<s32>::Result);
			Assert::IsTrue(HD_IsFundamental<u32>::Result);
			Assert::IsTrue(HD_IsFundamental<s64>::Result);
			Assert::IsTrue(HD_IsFundamental<u64>::Result);
			Assert::IsTrue(HD_IsFundamental<f32>::Result);
			Assert::IsTrue(HD_IsFundamental<f64>::Result);
		}
	};
}
