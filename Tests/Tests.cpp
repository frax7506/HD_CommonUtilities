#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_Box.h"
#include "HD_CircularArray.h"
#include "HD_GrowingArray.h"
#include "HD_Map.h"
#include "HD_Math.h"
#include "HD_Pair.h"
#include "HD_StaticArray.h"
#include "HD_StaticStack.h"
#include "HD_Vector2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	bool AreFloatValuesClose(f32 aFirst, f32 aSecond)
	{
		f32 diff = HD_Abs(aFirst - aSecond);
		return diff < F_SMALL;
	}

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

	TEST_CLASS(HD_StaticArray_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (int i = 0, e = staticArray.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticArray[i], 0);
			}
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (int i = 0, e = staticArray1.Size(); i < e; ++i)
			{
				staticArray1[i] = i;
			}

			HD_StaticArray<s32, 8> staticArray2(staticArray1);

			for (int i = 0, e = staticArray2.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticArray2[i], i);
			}
		}

		TEST_METHOD(Size)
		{
			HD_StaticArray<s32, 8> staticArray1;
			Assert::AreEqual(staticArray1.Size(), 8);

			HD_StaticArray<s32, 16> staticArray2;
			Assert::AreEqual(staticArray2.Size(), 16);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (int i = 0, e = staticArray.Size(); i < e; ++i)
			{
				staticArray[i] = i;
			}

			for (int i = 0, e = staticArray.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticArray[i], i);
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			for (int i = 0, e = staticArrayConst.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticArrayConst[i], i);
			}
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (int i = 0, e = staticArray1.Size(); i < e; ++i)
			{
				staticArray1[i] = i;
			}

			HD_StaticArray<s32, 8> staticArray2;
			staticArray2 = staticArray1;

			for (int i = 0, e = staticArray2.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticArray2[i], i);
			}
		}

		TEST_METHOD(Iterator)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (int i = 0, e = staticArray.Size(); i < e; ++i)
			{
				staticArray[i] = i;
			}

			int index = 0;
			for (s32 i : staticArray)
			{
				Assert::AreEqual(i, index);
				++index;
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			index = 0;
			for (s32 i : staticArrayConst)
			{
				Assert::AreEqual(i, index);
				++index;
			}
		}
	};

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

	TEST_CLASS(HD_StaticStack_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_StaticStack<s32, 8> staticStack;

			for (int i = 0; i < 8; ++i)
			{
				Assert::AreEqual(staticStack.myData[i], 0);
			}
		}

		TEST_METHOD(Push)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);

			for (int i = 0, e = staticStack.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}
		}

		TEST_METHOD(Pop)
		{

			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.Pop();

			for (int i = 0, e = staticStack.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.Size(), 3);
		}

		TEST_METHOD(Top)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			Assert::AreEqual(staticStack.Top(), 0);
			staticStack.Push(1);
			Assert::AreEqual(staticStack.Top(), 1);
			staticStack.Push(2);
			Assert::AreEqual(staticStack.Top(), 2);
			staticStack.Push(3);
			Assert::AreEqual(staticStack.Top(), 3);
		}

		TEST_METHOD(PopN)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.PopN(2);

			for (int i = 0, e = staticStack.Size(); i < e; ++i)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.Size(), 2);
		}

		TEST_METHOD(MoveN)
		{
			HD_StaticStack<s32, 8> staticStack1;
			staticStack1.Push(0);
			staticStack1.Push(1);
			staticStack1.Push(2);
			staticStack1.Push(3);

			HD_StaticStack<s32, 8> staticStack2;
			staticStack2.MoveN(staticStack1, 2);

			Assert::AreEqual(staticStack1.myData[0], 0);
			Assert::AreEqual(staticStack1.myData[1], 1);
			Assert::AreEqual(staticStack1.Size(), 2);

			Assert::AreEqual(staticStack2.myData[0], 2);
			Assert::AreEqual(staticStack2.myData[1], 3);
			Assert::AreEqual(staticStack2.Size(), 2);
		}

		TEST_METHOD(Size)
		{
			HD_StaticStack<s32, 8> staticStack;
			Assert::AreEqual(staticStack.Size(), 0);
			staticStack.Push(0);
			Assert::AreEqual(staticStack.Size(), 1);
			staticStack.Push(1);
			Assert::AreEqual(staticStack.Size(), 2);
			staticStack.Push(2);
			Assert::AreEqual(staticStack.Size(), 3);
			staticStack.Push(3);
			Assert::AreEqual(staticStack.Size(), 4);
			staticStack.Pop();
			Assert::AreEqual(staticStack.Size(), 3);
			staticStack.Pop();
			Assert::AreEqual(staticStack.Size(), 2);
		}
	};

	TEST_CLASS(HD_Map_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Map<s32, s32> map;
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2(map1);
			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2(HD_Move(map1));
			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);

			Assert::IsNull(map1.myRoot);
		}

		TEST_METHOD(Destructor)
		{
			HD_Map<s32, s32> map;
			map[0] = 0;
			map[1] = 1;
			map[2] = 2;

			map.~HD_Map();
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(GetIfExists)
		{
			HD_Map<s32, s32> map;
			map[0] = 0;

			const int* value1 = map.GetIfExists(0);
			const int* value2 = map.GetIfExists(1);

			Assert::IsNotNull(value1);
			Assert::AreEqual(*value1, 0);
			Assert::IsNull(value2);
		}

		TEST_METHOD(Operator_Subscript)
		{
			HD_Map<s32, s32> map;
			Assert::IsNull(map.myRoot);

			map[6] = 6;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 6);
			Assert::AreEqual(map.myRoot->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			map[7] = 7;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 6);
			Assert::AreEqual(map.myRoot->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Left rotation
			map[8] = 8;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map[5] = 5;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 6);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 5);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Right rotation
			map[4] = 4;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			map[10] = 10;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right left rotation
			map[9] = 9;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			map[2] = 2;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 4);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 2);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Left right rotation
			map[3] = 3;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 2);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Right rotation with children
			map[1] = 1;
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);
		}

		TEST_METHOD(Remove)
		{
			HD_Map<s32, s32> map;
			map[6] = 6;
			map[7] = 7;
			map[8] = 8;
			map[5] = 5;
			map[4] = 4;
			map[10] = 10;
			map[9] = 9;
			map[2] = 2;
			map[3] = 3;
			map[1] = 1;

			// Remove a key that isn't in the map, make sure the map is unchanged.
			map.Remove(0);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myKey, 6);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myRight->myValue, 6);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove right leaf
			map.Remove(6);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 5);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 5);
			Assert::IsNotNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one left child
			map.Remove(5);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 9);
			Assert::AreEqual(map.myRoot->myRight->myValue, 9);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 10);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with two children
			map.Remove(9);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 7);
			Assert::AreEqual(map.myRoot->myValue, 7);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 3);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myLeft->myRight);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myKey, 4);
			Assert::AreEqual(map.myRoot->myLeft->myRight->myValue, 4);
			Assert::IsNull(map.myRoot->myLeft->myRight->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 10);
			Assert::AreEqual(map.myRoot->myRight->myValue, 10);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove that results in one right rotation
			map.Remove(10);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNotNull(map.myRoot->myRight->myLeft);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myKey, 4);
			Assert::AreEqual(map.myRoot->myRight->myLeft->myValue, 4);
			Assert::IsNull(map.myRoot->myRight->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myRight->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove left leaf
			map.Remove(4);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 7);
			Assert::AreEqual(map.myRoot->myRight->myValue, 7);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNotNull(map.myRoot->myRight->myRight);
			Assert::AreEqual(map.myRoot->myRight->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight->myRight);

			// Remove root with one right child
			map.Remove(7);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 3);
			Assert::AreEqual(map.myRoot->myValue, 3);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 2);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove(3);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 2);
			Assert::AreEqual(map.myRoot->myValue, 2);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNotNull(map.myRoot->myRight);
			Assert::AreEqual(map.myRoot->myRight->myKey, 8);
			Assert::AreEqual(map.myRoot->myRight->myValue, 8);
			Assert::IsNull(map.myRoot->myRight->myLeft);
			Assert::IsNull(map.myRoot->myRight->myRight);

			// Remove the root which has two children
			map.Remove(2);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 8);
			Assert::AreEqual(map.myRoot->myValue, 8);
			Assert::IsNotNull(map.myRoot->myLeft);
			Assert::AreEqual(map.myRoot->myLeft->myKey, 1);
			Assert::AreEqual(map.myRoot->myLeft->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft->myLeft);
			Assert::IsNull(map.myRoot->myLeft->myRight);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which has one child
			map.Remove(8);
			Assert::IsNotNull(map.myRoot);
			Assert::AreEqual(map.myRoot->myKey, 1);
			Assert::AreEqual(map.myRoot->myValue, 1);
			Assert::IsNull(map.myRoot->myLeft);
			Assert::IsNull(map.myRoot->myRight);

			// Remove the root which is the last node
			map.Remove(1);
			Assert::IsNull(map.myRoot);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			HD_Map<s32, s32> map2;
			map2 = map1;
			Assert::AreEqual(map2.myRoot->myValue, 1);
			Assert::AreEqual(map2.myRoot->myLeft->myValue, 0);
			Assert::AreEqual(map2.myRoot->myRight->myValue, 2);

			Assert::IsNull(map2.myRoot->myLeft->myLeft);
			Assert::IsNull(map2.myRoot->myLeft->myRight);
			Assert::IsNull(map2.myRoot->myRight->myLeft);
			Assert::IsNull(map2.myRoot->myRight->myRight);
		}

		TEST_METHOD(Iterator)
		{
			HD_Map<s32, s32> map1;
			map1[0] = 0;
			map1[1] = 1;
			map1[2] = 2;

			int index = 0;
			for (const auto& node : map1)
			{
				Assert::AreEqual(node.myKey, index);
				Assert::AreEqual(node.myValue, index);
				++index;
			}

			const HD_Map<s32, s32> map2(map1);

			index = 0;
			for (const auto& node : map2)
			{
				Assert::AreEqual(node.myKey, index);
				Assert::AreEqual(node.myValue, index);
				++index;
			}
		}
	};

	TEST_CLASS(HD_Pair_Test)
	{
	public:
		TEST_METHOD(Construtor_Default)
		{
			HD_Pair<s32, s32> pair;
			Assert::AreEqual(pair.myFirst, 0);
			Assert::AreEqual(pair.mySecond, 0);
		}

		TEST_METHOD(Construtor_First_And_Second_As_Args)
		{
			HD_Pair<s32, s32> pair(1, 2);
			Assert::AreEqual(pair.myFirst, 1);
			Assert::AreEqual(pair.mySecond, 2);
		}
	};

	TEST_CLASS(HD_String_Test)
	{
	public:

	};

	TEST_CLASS(HD_Box_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Box box;
			Assert::AreEqual(box.myCenter.myX, 0.f);
			Assert::AreEqual(box.myCenter.myY, 0.f);
			Assert::AreEqual(box.myHalfSize, 0.f);
		}

		TEST_METHOD(Constructor_Center_And_Size)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 1.f);
			Assert::AreEqual(box.myCenter.myX, 1.f);
			Assert::AreEqual(box.myCenter.myY, 1.f);
			Assert::AreEqual(box.myHalfSize, 0.5f);
		}

		TEST_METHOD(Contains)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 2.f);

			Assert::IsTrue(box.Contains({ 1.f, 1.f }));

			Assert::IsTrue(box.Contains({ 1.5f, 1.f }));
			Assert::IsTrue(box.Contains({ 1.f, 1.5f }));
			Assert::IsTrue(box.Contains({ 0.5f, 1.f }));
			Assert::IsTrue(box.Contains({ 1.f, 0.5f }));

			Assert::IsTrue(box.Contains({ 2.f, 1.f }));
			Assert::IsTrue(box.Contains({ 2.f, 2.f }));
			Assert::IsTrue(box.Contains({ 1.f, 2.f }));
			Assert::IsTrue(box.Contains({ 0.f, 2.f }));
			Assert::IsTrue(box.Contains({ 0.f, 1.f }));
			Assert::IsTrue(box.Contains({ 0.f, 0.f }));
			Assert::IsTrue(box.Contains({ 1.f, 0.f }));
			Assert::IsTrue(box.Contains({ 2.f, 0.f }));

			Assert::IsFalse(box.Contains({ 3.f, 1.f }));
			Assert::IsFalse(box.Contains({ 3.f, 2.f }));
			Assert::IsFalse(box.Contains({ 3.f, 3.f }));
			Assert::IsFalse(box.Contains({ 2.f, 3.f }));
			Assert::IsFalse(box.Contains({ 1.f, 3.f }));
			Assert::IsFalse(box.Contains({ 0.f, 3.f }));
			Assert::IsFalse(box.Contains({ -1.f, 3.f }));
			Assert::IsFalse(box.Contains({ -1.f, 2.f }));
			Assert::IsFalse(box.Contains({ -1.f, 1.f }));
			Assert::IsFalse(box.Contains({ -1.f, 0.f }));
			Assert::IsFalse(box.Contains({ -1.f, -1.f }));
			Assert::IsFalse(box.Contains({ 0.f, -1.f }));
			Assert::IsFalse(box.Contains({ 1.f, -1.f }));
			Assert::IsFalse(box.Contains({ 2.f, -1.f }));
			Assert::IsFalse(box.Contains({ 3.f, -1.f }));
			Assert::IsFalse(box.Contains({ 3.f, 0.f }));
		}

		TEST_METHOD(Intersects)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 2.f);

			Assert::IsTrue(box.Intersects(box));

			Assert::IsTrue(box.Intersects({ { 2.f, 2.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 0.f, 2.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 0.f, 0.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 2.f, 0.f }, 2.f }));

			Assert::IsTrue(box.Intersects({ { 3.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 1.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, 1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 1.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 3.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 3.f, 1.f }, 2.f }));

			Assert::IsFalse(box.Intersects({ { 4.f, 1.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 4.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 1.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, 1.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, -2.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 1.f, -2.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 4.f, -1.f }, 2.f }));
		}
	};

	TEST_CLASS(HD_Vector2_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector2f floatVector;
			Assert::AreEqual(floatVector.myX, 0.f);
			Assert::AreEqual(floatVector.myY, 0.f);

			HD_Vector2i intVector;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 0);
		}

		TEST_METHOD(Constructor_X_And_Y)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);

			HD_Vector2i intVector(3, 4);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(floatVector1);
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);

			HD_Vector2i intVector1(3, 4);
			HD_Vector2i intVector2(intVector1);
			Assert::AreEqual(intVector2.myX, 3);
			Assert::AreEqual(intVector2.myY, 4);
		}

		TEST_METHOD(Set)
		{
			HD_Vector2f floatVector;
			floatVector.Set(1.f, 2.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);

			HD_Vector2i intVector;
			intVector.Set(3, 4);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Length)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			float length = floatVector.Length();
			Assert::IsTrue(AreFloatValuesClose(length, HD_Sqrtf(2.f)));
		}

		TEST_METHOD(Length2)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			float floatLength2 = floatVector.Length2();
			Assert::IsTrue(AreFloatValuesClose(floatLength2, 2.f));

			HD_Vector2i intVector(2, 2);
			int intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 8);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			floatVector.Normalize();
			float length = floatVector.Length();
			Assert::IsTrue(AreFloatValuesClose(length, 1.f));
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			HD_Vector2f normalizedFloatVector = floatVector.GetNormalized();
			float floatVectorLength = floatVector.Length();
			float normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::IsTrue(AreFloatValuesClose(floatVectorLength, HD_Sqrtf(8.f)));
			Assert::IsTrue(AreFloatValuesClose(normalizedFloatVectorLength, 1.f));
		}

		TEST_METHOD(Dot)
		{
			HD_Vector2f up(0.f, 1.f);
			HD_Vector2f upRight(1.f, 1.f);
			HD_Vector2f right(1.f, 0.f);
			HD_Vector2f downRight(1.f, -1.f);
			HD_Vector2f down(0.f, -1.f);
			HD_Vector2f downLeft(-1.f, -1.f);
			HD_Vector2f left(-1.f, 0.f);
			HD_Vector2f upLeft(-1.f, 1.f);

			upRight.Normalize();
			downRight.Normalize();
			downLeft.Normalize();
			upLeft.Normalize();

			float upDotUp = up.Dot(up);
			float upDotUpRight = up.Dot(upRight);
			float upDotRight = up.Dot(right);
			float upDotDownRight = up.Dot(downRight);
			float upDotDown = up.Dot(down);
			float upDotDownLeft = up.Dot(downLeft);
			float upDotLeft = up.Dot(left);
			float upDotUpLeft = up.Dot(upLeft);

			Assert::IsTrue(AreFloatValuesClose(upDotUp, 1.f));
			Assert::IsTrue(AreFloatValuesClose(upDotUpRight, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(AreFloatValuesClose(upDotRight, 0.f));
			Assert::IsTrue(AreFloatValuesClose(upDotDownRight, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(AreFloatValuesClose(upDotDown, -1.f));
			Assert::IsTrue(AreFloatValuesClose(upDotDownLeft, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(AreFloatValuesClose(upDotLeft, 0.f));
			Assert::IsTrue(AreFloatValuesClose(upDotUpLeft, F_ONE_OVER_SQRT_TWO));
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2;
			floatVector2 = floatVector1;
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2;
			intVector2 = intVector1;
			Assert::AreEqual(intVector2.myX, 1);
			Assert::AreEqual(intVector2.myY, 2);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatResult = floatVector1 + floatVector2;
			Assert::AreEqual(floatResult.myX, 4.f);
			Assert::AreEqual(floatResult.myY, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intResult = intVector1 + intVector2;
			Assert::AreEqual(intResult.myX, 4);
			Assert::AreEqual(intResult.myY, 6);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatResult = floatVector1 - floatVector2;
			Assert::AreEqual(floatResult.myX, -2.f);
			Assert::AreEqual(floatResult.myY, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intResult = intVector1 - intVector2;
			Assert::AreEqual(intResult.myX, -2);
			Assert::AreEqual(intResult.myY, -2);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = floatVector * 2.f;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = intVector * 2;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = 2.f * floatVector;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = 2 * intVector;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = floatVector / 2.f;
			Assert::AreEqual(floatResult.myX, 0.5f);
			Assert::AreEqual(floatResult.myY, 1.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = intVector / 2;
			Assert::AreEqual(intResult.myX, 0);
			Assert::AreEqual(intResult.myY, 1);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 += floatVector2;
			Assert::AreEqual(floatVector1.myX, 4.f);
			Assert::AreEqual(floatVector1.myY, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 += intVector2;
			Assert::AreEqual(intVector1.myX, 4);
			Assert::AreEqual(intVector1.myY, 6);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 -= floatVector2;
			Assert::AreEqual(floatVector1.myX, -2.f);
			Assert::AreEqual(floatVector1.myY, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 -= intVector2;
			Assert::AreEqual(intVector1.myX, -2);
			Assert::AreEqual(intVector1.myY, -2);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector *= 2.f;
			Assert::AreEqual(floatVector.myX, 2.f);
			Assert::AreEqual(floatVector.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			intVector *= 2;
			Assert::AreEqual(intVector.myX, 2);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector /= 2.f;
			Assert::AreEqual(floatVector.myX, 0.5f);
			Assert::AreEqual(floatVector.myY, 1.f);

			HD_Vector2i intVector(1, 2);
			intVector /= 2;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 1);
		}
	};

	TEST_CLASS(Math)
	{
	public:
		TEST_METHOD(SquareRoot)
		{
			Assert::AreEqual(HD_Sqrtf(4.f), 2.f);
		}

		TEST_METHOD(AbsoluteValue)
		{
			Assert::AreEqual(HD_Abs(2), 2);
			Assert::AreEqual(HD_Abs(-2), 2);
			Assert::AreEqual(HD_Abs(2.f), 2.f);
			Assert::AreEqual(HD_Abs(-2.f), 2.f);
		}

		TEST_METHOD(Power)
		{
			Assert::AreEqual(HD_Pow(2, 2), 4);
			Assert::AreEqual(HD_Powf(3.f, 3.f), 27.f);
		}

		TEST_METHOD(Max)
		{
			Assert::AreEqual(HD_Max(0, 0), 0);
			Assert::AreEqual(HD_Max(1, 2), 2);
			Assert::AreEqual(HD_Max(2, 1), 2);
			Assert::AreEqual(HD_Max(-1.f, 1.f), 1.f);
			Assert::AreEqual(HD_Max(1.f, -1.f), 1.f);
		}

		TEST_METHOD(Min)
		{
			Assert::AreEqual(HD_Min(0, 0), 0);
			Assert::AreEqual(HD_Min(1, 2), 1);
			Assert::AreEqual(HD_Min(2, 1), 1);
			Assert::AreEqual(HD_Min(-1.f, 1.f), -1.f);
			Assert::AreEqual(HD_Min(1.f, -1.f), -1.f);
		}
	};
}
