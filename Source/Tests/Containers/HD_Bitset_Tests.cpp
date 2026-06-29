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

		TEST_METHOD(Bit_Constructor)
		{
			HD_Bitset<32>::Bit bit;
			Assert::IsNull(bit.myBitset);
			Assert::AreEqual(bit.myIndex, 0);
		}

		TEST_METHOD(Bit_Constructor_Copy)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Bit bit1(&bitset, 1);
			HD_Bitset<32>::Bit bit2(bit1);

			Assert::IsNotNull(bit2.myBitset);
			Assert::IsTrue(memcmp(bit1.myBitset, bit2.myBitset, 4) == 0);
			Assert::AreEqual(bit1.myIndex, bit2.myIndex);
		}

		TEST_METHOD(Bit_Constructor_HD_Bitset_And_Index)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Bit bit(&bitset, 1);

			s32 testMemory = 0x01010101;
			Assert::IsTrue(memcmp(bit.myBitset, &testMemory, 4) == 0);
			Assert::AreEqual(bit.myIndex, 1);
		}

		TEST_METHOD(Bit_Operator_Assignment_Copy)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Bit bit1(&bitset, 1);
			HD_Bitset<32>::Bit bit2;
			bit2 = bit1;

			Assert::IsNotNull(bit2.myBitset);
			Assert::IsTrue(memcmp(bit1.myBitset, bit2.myBitset, 4) == 0);
			Assert::AreEqual(bit1.myIndex, bit2.myIndex);
		}

		TEST_METHOD(Bit_Operator_Assignment_Bool)
		{
			HD_Bitset<32> bitset(0x01010101);
			HD_Bitset<32>::Bit bit(&bitset, 1);

			bit = true;

			s32 testMemory = 0x01010103;
			Assert::IsTrue(memcmp(bitset.myBits, &testMemory, 4) == 0);

			bit = false;

			testMemory = 0x01010101;
			Assert::IsTrue(memcmp(bitset.myBits, &testMemory, 4) == 0);
		}

		TEST_METHOD(Bit_GetValue)
		{
			HD_Bitset<32> bitset;
			HD_Bitset<32>::Bit bit(&bitset, 0);

			bool value = bit.GetValue();
			Assert::IsFalse(value);

			bit = true;

			value = bit.GetValue();
			Assert::IsTrue(value);
		}

		TEST_METHOD(Bit_Operator_Bool)
		{
			HD_Bitset<32> bitset;
			HD_Bitset<32>::Bit bit(&bitset, 0);

			bool value = bit;
			Assert::IsFalse(value);

			bit = true;

			value = bit;
			Assert::IsTrue(value);
		}
	};
}
