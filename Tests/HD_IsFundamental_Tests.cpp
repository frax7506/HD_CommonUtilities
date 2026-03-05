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

			Assert::IsTrue(HD_IsFundamental<char>::Result);
			Assert::IsTrue(HD_IsFundamental<unsigned char>::Result);
			Assert::IsTrue(HD_IsFundamental<short>::Result);
			Assert::IsTrue(HD_IsFundamental<unsigned short>::Result);
			Assert::IsTrue(HD_IsFundamental<int>::Result);
			Assert::IsTrue(HD_IsFundamental<unsigned int>::Result);
			Assert::IsTrue(HD_IsFundamental<long long>::Result);
			Assert::IsTrue(HD_IsFundamental<unsigned long long>::Result);
			Assert::IsTrue(HD_IsFundamental<float>::Result);
			Assert::IsTrue(HD_IsFundamental<double>::Result);
		}
	};
}
