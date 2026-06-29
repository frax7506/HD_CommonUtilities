#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_Bitset.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Bitset_Test)
	{
	public:
		enum eBits
		{
			eBits0,
			eBits1,
			eBits2,
			eBits3,
			eBits4,
			eBits5,
			eBits6,
			eBits7,
		};

		TEST_METHOD(Constructor)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Constructor_HD_Bitset)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Constructor_Unsigned_Long_Long)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Subscript)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitwise_AND_Assignment)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitwise_OR_Assignment)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitwise_XOR_Assignment)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitshift_Left_Assignment)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitshift_Right_Assignment)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_NOT)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitshift_Left)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Bitshift_Right)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Reference_Constructor_HD_Bitset_And_Index)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Reference_Operator_Assignment_Reference)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Reference_Operator_Assignment_Bool)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Reference_Operator_Bool)
		{
			Assert::IsTrue(false);
		}
	};
}
