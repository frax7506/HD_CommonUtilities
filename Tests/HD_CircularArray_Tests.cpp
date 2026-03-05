#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_CircularArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_CircularArray_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_CircularArray<s32, 8> circularArray;

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);
			Assert::AreEqual(static_cast<int>(circularArray.myOverflowBehaviour), static_cast<int>(OverflowBehaviour::Enable));

			for (s32 i = 0; i < 8; i++)
			{
				Assert::AreEqual(circularArray.myData[i], 0);
			}
		}

		TEST_METHOD(PushBack_Overflow_Enabled)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 4);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 0);
			Assert::AreEqual(circularArray.myData[5], 0);
			Assert::AreEqual(circularArray.myData[6], 0);
			Assert::AreEqual(circularArray.myData[7], 0);

			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.PushBack(8);

			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 1);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 8);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.PushBack(9);

			Assert::AreEqual(circularArray.myFirstIndex, 2);
			Assert::AreEqual(circularArray.myWriteIndex, 2);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 8);
			Assert::AreEqual(circularArray.myData[1], 9);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);
		}

		TEST_METHOD(PushBack_Overflow_Disabled)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.SetOverflowBehaviour(OverflowBehaviour::Disable);

			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);
			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			// htodo: automate this
			// Comment out to validate assertion
			//circularArray.PushBack(8);
		}

		TEST_METHOD(GetFirstAndRemove)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(4);
			circularArray.PushBack(4);
			circularArray.PushBack(4);
			circularArray.PushBack(4);

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);

			Assert::AreEqual(i, 4);
			Assert::AreEqual(circularArray.myFirstIndex, 1);
			Assert::AreEqual(circularArray.myWriteIndex, 4);
			Assert::AreEqual(circularArray.mySize, 3);

			Assert::AreEqual(circularArray.myData[0], 4);
			Assert::AreEqual(circularArray.myData[1], 4);
			Assert::AreEqual(circularArray.myData[2], 4);
			Assert::AreEqual(circularArray.myData[3], 4);
			Assert::AreEqual(circularArray.myData[4], 0);
			Assert::AreEqual(circularArray.myData[5], 0);
			Assert::AreEqual(circularArray.myData[6], 0);
			Assert::AreEqual(circularArray.myData[7], 0);
		}

		TEST_METHOD(Clear)
		{
			HD_CircularArray<s32, 8> circularArray;
			circularArray.PushBack(0);
			circularArray.PushBack(1);
			circularArray.PushBack(2);
			circularArray.PushBack(3);
			circularArray.PushBack(4);
			circularArray.PushBack(5);
			circularArray.PushBack(6);
			circularArray.PushBack(7);

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 8);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);

			circularArray.Clear();

			Assert::AreEqual(circularArray.myFirstIndex, 0);
			Assert::AreEqual(circularArray.myWriteIndex, 0);
			Assert::AreEqual(circularArray.mySize, 0);

			Assert::AreEqual(circularArray.myData[0], 0);
			Assert::AreEqual(circularArray.myData[1], 1);
			Assert::AreEqual(circularArray.myData[2], 2);
			Assert::AreEqual(circularArray.myData[3], 3);
			Assert::AreEqual(circularArray.myData[4], 4);
			Assert::AreEqual(circularArray.myData[5], 5);
			Assert::AreEqual(circularArray.myData[6], 6);
			Assert::AreEqual(circularArray.myData[7], 7);
		}

		TEST_METHOD(GetSize)
		{
			HD_CircularArray<s32, 8> circularArray;
			Assert::AreEqual(circularArray.GetSize(), 0);

			circularArray.PushBack(0);
			Assert::AreEqual(circularArray.GetSize(), 1);

			circularArray.PushBack(1);
			Assert::AreEqual(circularArray.GetSize(), 2);

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);
			Assert::AreEqual(circularArray.GetSize(), 1);
		}

		TEST_METHOD(GetCapacity)
		{
			{
				HD_CircularArray<s32, 8> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 8);
			}

			{
				HD_CircularArray<s32, 16> circularArray;
				Assert::AreEqual(circularArray.GetCapacity(), 16);
			}
		}

		TEST_METHOD(IsEmpty)
		{
			HD_CircularArray<s32, 8> circularArray;
			Assert::IsTrue(circularArray.IsEmpty());

			circularArray.PushBack(0);
			Assert::IsFalse(circularArray.IsEmpty());

			s32 i = 0;
			circularArray.GetFirstAndRemove(i);
			Assert::IsTrue(circularArray.IsEmpty());
		}

		TEST_METHOD(SetOverflowBehaviour)
		{
			HD_CircularArray<s32, 8> circularArray;
			Assert::AreEqual(static_cast<int>(circularArray.myOverflowBehaviour), static_cast<int>(OverflowBehaviour::Enable));

			circularArray.SetOverflowBehaviour(OverflowBehaviour::Disable);
			Assert::AreEqual(static_cast<int>(circularArray.myOverflowBehaviour), static_cast<int>(OverflowBehaviour::Disable));
		}
	};
}
