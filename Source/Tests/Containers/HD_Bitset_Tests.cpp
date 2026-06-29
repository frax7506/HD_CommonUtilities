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
			HD_Bitset<32> bitset;
			char zeroMemory[4]{ 0 };
			Assert::IsTrue(memcmp(&bitset.myBits, zeroMemory, 4) == 0);
		}

		TEST_METHOD(Constructor_Copy)
		{
			s32 bits = 0x01010101;
			HD_Bitset<32> bitset1(bits);
			HD_Bitset<32> bitset2(bitset1);
			Assert::IsTrue(memcmp(&bitset2.myBits, &bits, 4) == 0);
		}

		TEST_METHOD(Constructor_Unsigned_Long_Long)
		{
			s32 bits = 0x01010101;
			HD_Bitset<32> bitset(bits);
			Assert::IsTrue(memcmp(&bitset.myBits, &bits, 4) == 0);
		}

		TEST_METHOD(EnableAllBits)
		{
			HD_Bitset<32> bitset;
			bitset.EnableAllBits();

			s32 testMemory = 0xFFFFFFFF;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(DisableAllBits)
		{
			HD_Bitset<32> bitset;
			bitset.EnableAllBits();
			bitset.DisableAllBits();

			char zeroMemory[4]{ 0 };
			Assert::IsTrue(memcmp(&bitset.myBits, zeroMemory, 4) == 0);
		}

		TEST_METHOD(FlipAllBits)
		{
			HD_Bitset<32> bitset(0x0000FFFF);
			bitset.FlipAllBits();
			
			s32 testMemory = 0xFFFF0000;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_Bitset<32> bitset;
			bitset[0] = true;
			bitset[8] = true;
			bitset[16] = true;
			bitset[24] = true;

			s32 testMemory = 0x01010101;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);

			bitset[8] = false;
			bitset[24] = false;

			testMemory = 0x00010001;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitwise_AND_Assignment)
		{
			HD_Bitset<32> bitset(0x01010101);
			bitset &= 0x0000FFFF;
			s32 testMemory = 0x00000101;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitwise_OR_Assignment)
		{
			HD_Bitset<32> bitset(0x01010101);
			bitset |= 0x0000FFFF;
			s32 testMemory = 0x0101FFFF;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitwise_XOR_Assignment)
		{
			HD_Bitset<32> bitset(0x01010101);
			bitset ^= 0x0000FFFF;
			s32 testMemory = 0x0101FEFE;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitshift_Left_Assignment)
		{
			HD_Bitset<32> bitset(0x01010101);
			bitset <<= 1;
			s32 testMemory = 0x02020202;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitshift_Right_Assignment)
		{
			HD_Bitset<32> bitset(0x01010101);
			bitset >>= 1;
			s32 testMemory = 0x00808080;
			Assert::IsTrue(memcmp(&bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_NOT)
		{
			HD_Bitset<32> bitset1(0x01010101);
			HD_Bitset<32> bitset2 = ~bitset1;
			s32 testMemory = 0xFEFEFEFE;
			Assert::IsTrue(memcmp(&bitset2.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitshift_Left)
		{
			HD_Bitset<32> bitset1(0x01010101);
			HD_Bitset<32> bitset2 = bitset1 << 1;
			s32 testMemory = 0x02020202;
			Assert::IsTrue(memcmp(&bitset2.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Operator_Bitshift_Right)
		{
			HD_Bitset<32> bitset1(0x01010101);
			HD_Bitset<32> bitset2 = bitset1 >> 1;
			s32 testMemory = 0x00808080;
			Assert::IsTrue(memcmp(&bitset2.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Reference_Constructor)
		{
			HD_Bitset<32>::Reference reference;
			Assert::IsNull(reference.myBitset);
			Assert::AreEqual(reference.myIndex, 0);
		}

		TEST_METHOD(Reference_Constructor_Copy)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Reference reference1(&bitset, 1);
			HD_Bitset<32>::Reference reference2(reference1);

			Assert::IsNotNull(reference2.myBitset);
			Assert::IsTrue(memcmp(reference1.myBitset, reference2.myBitset, 4) == 0);
			Assert::AreEqual(reference1.myIndex, reference2.myIndex);
		}

		TEST_METHOD(Reference_Constructor_HD_Bitset_And_Index)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Reference reference(&bitset, 1);

			s32 testMemory = 0x01010101;
			Assert::IsTrue(memcmp(reference.myBitset, &testMemory, 4) == 0);
			Assert::AreEqual(reference.myIndex, 1);
		}

		TEST_METHOD(Reference_Operator_Assignment_Copy)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Reference reference1(&bitset, 1);
			HD_Bitset<32>::Reference reference2;
			reference2 = reference1;

			Assert::IsNotNull(reference2.myBitset);
			Assert::IsTrue(memcmp(reference1.myBitset, reference2.myBitset, 4) == 0);
			Assert::AreEqual(reference1.myIndex, reference2.myIndex);
		}

		TEST_METHOD(Reference_Operator_Assignment_Bool)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Reference reference(&bitset, 1);

			reference = true;

			s32 testMemory = 0x01010103;
			Assert::IsTrue(memcmp(bitset.myBits, &testMemory, 4) == 0);

			reference = false;

			testMemory = 0x01010101;
			Assert::IsTrue(memcmp(bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Reference_GetValue)
		{
			HD_Bitset<32> bitset;
			HD_Bitset<32>::Reference reference(&bitset, 0);

			bool value = reference.GetValue();
			Assert::IsFalse(value);

			reference = true;

			value = reference.GetValue();
			Assert::IsTrue(value);
		}

		TEST_METHOD(Reference_Operator_Bool)
		{
			HD_Bitset<32> bitset;
			HD_Bitset<32>::Reference reference(&bitset, 0);

			bool value = reference;
			Assert::IsFalse(value);

			reference = true;

			value = reference;
			Assert::IsTrue(value);
		}
	};
}
