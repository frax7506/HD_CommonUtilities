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
			HD_StaticStack<u32, 8> staticStack;

			for (u32 i = 0; i < 8; i++)
			{
				Assert::AreEqual(staticStack.myData[i], 0u);
			}
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_StaticStack<HD_String, 8> staticStack;

			for (u32 i = 0; i < 8; i++)
			{
				TestUtils::String_IsUninitialized(staticStack.myData[i]);
			}
		}

		TEST_METHOD(Push_POD)
		{
			HD_StaticStack<u32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
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

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}
		}

		TEST_METHOD(Pop_POD)
		{
			HD_StaticStack<u32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.Pop();

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3u);
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

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3u);
		}

		TEST_METHOD(Top_POD)
		{
			HD_StaticStack<u32, 8> staticStack;
			staticStack.Push(0);
			Assert::AreEqual(staticStack.Top(), 0u);
			staticStack.Push(1);
			Assert::AreEqual(staticStack.Top(), 1u);
			staticStack.Push(2);
			Assert::AreEqual(staticStack.Top(), 2u);
			staticStack.Push(3);
			Assert::AreEqual(staticStack.Top(), 3u);
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
			HD_StaticStack<u32, 8> staticStack;
			staticStack.Push(0);
			staticStack.Push(1);
			staticStack.Push(2);
			staticStack.Push(3);
			staticStack.PopN(2);

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::AreEqual(staticStack.myData[i], i);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2u);
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

			for (u32 i = 0; i < staticStack.GetNrOfPushedElements(); i++)
			{
				Assert::IsTrue(staticStack.myData[i] == strings[i]);
			}

			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2u);
		}

		TEST_METHOD(MoveN_POD)
		{
			HD_StaticStack<u32, 8> staticStack1;
			staticStack1.Push(0);
			staticStack1.Push(1);
			staticStack1.Push(2);
			staticStack1.Push(3);

			HD_StaticStack<u32, 8> staticStack2;
			staticStack2.MoveN(staticStack1, 2);

			Assert::AreEqual(staticStack1.myData[0], 0u);
			Assert::AreEqual(staticStack1.myData[1], 1u);
			Assert::AreEqual(staticStack1.GetNrOfPushedElements(), 2u);

			Assert::AreEqual(staticStack2.myData[0], 2u);
			Assert::AreEqual(staticStack2.myData[1], 3u);
			Assert::AreEqual(staticStack2.GetNrOfPushedElements(), 2u);
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
			Assert::AreEqual(staticStack1.GetNrOfPushedElements(), 2u);

			Assert::IsTrue(staticStack2.myData[0] == "2");
			Assert::IsTrue(staticStack2.myData[1] == "3");
			Assert::AreEqual(staticStack2.GetNrOfPushedElements(), 2u);
		}

		TEST_METHOD(GetNrOfPushedElements)
		{
			HD_StaticStack<u32, 8> staticStack;
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 0u);
			staticStack.Push(0);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 1u);
			staticStack.Push(1);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2u);
			staticStack.Push(2);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3u);
			staticStack.Push(3);
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 4u);
			staticStack.Pop();
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 3u);
			staticStack.Pop();
			Assert::AreEqual(staticStack.GetNrOfPushedElements(), 2u);
		}
	};
}
