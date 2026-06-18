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
			eBits0 = 1 << 0,
			eBits1 = 1 << 1,
			eBits2 = 1 << 2,
			eBits3 = 1 << 3,
			eBits4 = 1 << 4,
			eBits5 = 1 << 5,
			eBits6 = 1 << 6,
			eBits7 = 1 << 7,
		};

		TEST_METHOD(Constructor)
		{
			HD_Bitset8 bitset;
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0));
		}

		TEST_METHOD(EnableBits)
		{
			HD_Bitset8 bitset;
			bitset.EnableBits(eBits0);
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0b00000001));

			bitset.EnableBits(eBits2 | eBits4);
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0b00010101));

			bitset.EnableBits(eBits7);
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0b10010101));
		}

		TEST_METHOD(DisableBits)
		{
			HD_Bitset8 bitset;
			bitset.EnableBits(eBits0 | eBits1 | eBits2 | eBits3 | eBits4 | eBits5 | eBits6 | eBits7);

			bitset.DisableBits(eBits0);
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0b11111110));

			bitset.DisableBits(eBits2 | eBits4);
			Assert::AreEqual(bitset.myBits, static_cast<unsigned char>(0b11101010));
		}

		TEST_METHOD(GetIsBitSet)
		{
			HD_Bitset8 bitset;
			bitset.EnableBits(eBits4);

			Assert::IsFalse(bitset.GetIsBitSet(eBits0));
			Assert::IsFalse(bitset.GetIsBitSet(eBits1));
			Assert::IsFalse(bitset.GetIsBitSet(eBits2));
			Assert::IsFalse(bitset.GetIsBitSet(eBits3));
			Assert::IsTrue(bitset.GetIsBitSet(eBits4));
			Assert::IsFalse(bitset.GetIsBitSet(eBits5));
			Assert::IsFalse(bitset.GetIsBitSet(eBits6));
			Assert::IsFalse(bitset.GetIsBitSet(eBits7));
		}

		TEST_METHOD(GetBits)
		{
			HD_Bitset8 bitset;
			bitset.EnableBits(eBits0 | eBits2 | eBits4 | eBits6);

			unsigned char bits = bitset.GetBits();
			Assert::AreEqual(bits, static_cast<unsigned char>(0b01010101));
		}
	};
}
