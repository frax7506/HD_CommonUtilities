#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_StaticStack.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_StaticStack_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_StaticStack<s32, 8> staticStack;

			for (s32 i = 0; i < 8; i++)
			{
				Assert::AreEqual(staticStack.myData[i], 0);
			}
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_StaticStack<HD_String, 8> staticStack;

			for (s32 i = 0; i < 8; i++)
			{
				TestUtils::StringDataCheckIsUninitialized(staticStack.myData[i]);
			}
		}

		TEST_METHOD(Push_POD)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}
		}

		TEST_METHOD(Push_NonPOD)
		{
			const char* strings[4] = { "0", "1", "2", "3" };

			HD_StaticStack<HD_String, 8> staticStack;
			staticStack.Push("0");
			staticStack.Push("1");
			staticStack.Push("2");
			staticStack.Push("3");

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}
		}

		TEST_METHOD(Pop_POD)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.Pop();

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3);
		}

		TEST_METHOD(Pop_NonPOD)
		{
			const char* strings[4] = { "0", "1", "2", "3" };

			HD_StaticStack<HD_String, 8> staticStack;
			staticStack.Push("0");
			staticStack.Push("1");
			staticStack.Push("2");
			staticStack.Push("3");
			staticStack.Pop();

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3);
		}

		TEST_METHOD(Top_POD)
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

		TEST_METHOD(Top_NonPOD)
		{
			HD_StaticStack<HD_String, 8> staticStack;
			staticStack.Push("0");
			Assert::IsTrue(staticStack.Top() == "0");
			staticStack.Push("1");
			Assert::IsTrue(staticStack.Top() == "1");
			staticStack.Push("2");
			Assert::IsTrue(staticStack.Top() == "2");
			staticStack.Push("3");
			Assert::IsTrue(staticStack.Top() == "3");
		}

		TEST_METHOD(PopN_POD)
		{
			HD_StaticStack<s32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.PopN(2);

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2);
		}

		TEST_METHOD(PopN_NonPOD)
		{
			const char* strings[4] = { "0", "1", "2", "3" };

			HD_StaticStack<HD_String, 8> staticStack;
			staticStack.Push("0");
			staticStack.Push("1");
			staticStack.Push("2");
			staticStack.Push("3");
			staticStack.PopN(2);

			for (s32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2);
		}

		TEST_METHOD(MoveN_POD)
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
			Assert::AreEqual(staticStack1.GetNrOfPushedElements(), 2);

			Assert::AreEqual(staticStack2.myData[0], 2);
			Assert::AreEqual(staticStack2.myData[1], 3);
			Assert::AreEqual(staticStack2.GetNrOfPushedElements(), 2);
		}

		TEST_METHOD(MoveN_NonPOD)
		{
			HD_StaticStack<HD_String, 8> staticStack1;
			staticStack1.Push("0");
			staticStack1.Push("1");
			staticStack1.Push("2");
			staticStack1.Push("3");

			HD_StaticStack<HD_String, 8> staticStack2;
			staticStack2.MoveN(staticStack1, 2);

			Assert::IsTrue(staticStack1.myData[0] == "0");
			Assert::IsTrue(staticStack1.myData[1] == "1");
			Assert::AreEqual(staticStack1.GetNrOfPushedElements(), 2);

			Assert::IsTrue(staticStack2.myData[0] == "2");
			Assert::IsTrue(staticStack2.myData[1] == "3");
			Assert::AreEqual(staticStack2.GetNrOfPushedElements(), 2);
		}

		TEST_METHOD(GetNrOfPushedElements)
		{
			HD_StaticStack<s32, 8> staticStack;
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 0);
			staticStack.Push(0);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 1);
			staticStack.Push(1);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2);
			staticStack.Push(2);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3);
			staticStack.Push(3);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 4);
			staticStack.Pop();
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3);
			staticStack.Pop();
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2);
		}
	};
}
