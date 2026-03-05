#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_GrowingArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_GrowingArray_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 2);
		}

		TEST_METHOD(Constructor_Capacity)
		{
			HD_GrowingArray<s32> growingArray(8);
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 8);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_GrowingArray<s32> growingArray1;
			growingArray1.PushBack(0);
			growingArray1.PushBack(1);
			growingArray1.PushBack(2);

			HD_GrowingArray<s32> growingArray2(growingArray1);
			Assert::IsNotNull(growingArray2.myData);
			Assert::AreEqual(growingArray2[0], 0);
			Assert::AreEqual(growingArray2[1], 1);
			Assert::AreEqual(growingArray2[2], 2);
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_GrowingArray<s32> growingArray1;
			growingArray1.PushBack(0);
			growingArray1.PushBack(1);
			growingArray1.PushBack(2);

			HD_GrowingArray<s32> growingArray2(HD_Move(growingArray1));

			Assert::IsNull(growingArray1.myData);
			Assert::IsNotNull(growingArray2.myData);
			Assert::AreEqual(growingArray2[0], 0);
			Assert::AreEqual(growingArray2[1], 1);
			Assert::AreEqual(growingArray2[2], 2);
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Destructor)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			growingArray.~HD_GrowingArray();
			Assert::IsNull(growingArray.myData);
		}

		TEST_METHOD(PushBack)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(PushBackSorted)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBackSorted(2);
			growingArray.PushBackSorted(1);
			growingArray.PushBackSorted(0);

			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(PushBackSortedReverse)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBackSortedReverse(0);
			growingArray.PushBackSortedReverse(1);
			growingArray.PushBackSortedReverse(2);

			Assert::AreEqual(growingArray[0], 2);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 0);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(Remove)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			growingArray.Remove(1);
			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 2);
			Assert::AreEqual(growingArray.mySize, 2);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(RemoveCyclic)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);
			growingArray.PushBack(3);

			growingArray.RemoveCyclic(1);
			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 3);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 4);
		}

		TEST_METHOD(RemoveAll)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);

			growingArray.RemoveAll();
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 2);
		}

		TEST_METHOD(Delete)
		{
			// htodo: write memory leak detector

			HD_GrowingArray<s32*> growingArray;
			growingArray.PushBack(new s32(0));
			growingArray.PushBack(new s32(1));
			growingArray.PushBack(new s32(2));

			growingArray.Delete(1);
			Assert::AreEqual(*growingArray[0], 0);
			Assert::AreEqual(*growingArray[1], 2);
			Assert::AreEqual(growingArray.mySize, 2);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(DeleteCyclic)
		{
			// htodo: write memory leak detector

			HD_GrowingArray<s32*> growingArray;
			growingArray.PushBack(new s32(0));
			growingArray.PushBack(new s32(1));
			growingArray.PushBack(new s32(2));
			growingArray.PushBack(new s32(3));

			growingArray.DeleteCyclic(1);
			Assert::AreEqual(*growingArray[0], 0);
			Assert::AreEqual(*growingArray[1], 3);
			Assert::AreEqual(*growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 4);
		}

		TEST_METHOD(DeleteAll)
		{
			HD_GrowingArray<s32*> growingArray;
			growingArray.PushBack(new s32(0));
			growingArray.PushBack(new s32(1));

			growingArray.DeleteAll();
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 2);
		}

		TEST_METHOD(Size)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::AreEqual(growingArray.Size(), 0);

			growingArray.PushBack(0);
			Assert::AreEqual(growingArray.Size(), 1);

			growingArray.PushBack(1);
			Assert::AreEqual(growingArray.Size(), 2);

			growingArray.PushBack(2);
			Assert::AreEqual(growingArray.Size(), 3);
		}

		TEST_METHOD(IsEmpty)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::IsTrue(growingArray.IsEmpty());

			growingArray.PushBack(0);
			Assert::IsFalse(growingArray.IsEmpty());
		}

		TEST_METHOD(Reserve)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.Reserve(8);

			Assert::AreEqual(growingArray.myCapacity, 8);
		}

		TEST_METHOD(Resize)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.Resize(4);

			Assert::AreEqual(growingArray.mySize, 4);
			Assert::AreEqual(growingArray.myCapacity, 4);
			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 0);
			Assert::AreEqual(growingArray[2], 0);
			Assert::AreEqual(growingArray[3], 0);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			s32 i0 = growingArray[0];
			s32 i1 = growingArray[1];
			s32 i2 = growingArray[2];

			Assert::AreEqual(i0, 0);
			Assert::AreEqual(i1, 1);
			Assert::AreEqual(i2, 2);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_GrowingArray<s32> growingArray1;
			HD_GrowingArray<s32> growingArray2;

			growingArray1.PushBack(0);
			growingArray1.PushBack(1);
			growingArray1.PushBack(2);

			growingArray2 = growingArray1;

			Assert::IsNotNull(growingArray2.myData);
			Assert::AreEqual(growingArray2[0], 0);
			Assert::AreEqual(growingArray2[1], 1);
			Assert::AreEqual(growingArray2[2], 2);
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(GetFirst)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray.GetFirst(), 0);
		}

		TEST_METHOD(GetLast)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray.GetLast(), 2);
		}

		TEST_METHOD(Iterator)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			s32 index = 0;
			for (s32 entry : growingArray)
			{
				Assert::AreEqual(entry, index);
				++index;
			}

			const HD_GrowingArray<s32> growingArrayConst = growingArray;

			index = 0;
			for (s32 entry : growingArrayConst)
			{
				Assert::AreEqual(entry, index);
				++index;
			}
		}
	};
}
