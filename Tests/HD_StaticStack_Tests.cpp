#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_StaticStack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
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
}
