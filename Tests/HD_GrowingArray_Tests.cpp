#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_GrowingArray.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_GrowingArray_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::IsNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 0);
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			Assert::IsNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 0);
		}

		TEST_METHOD(Constructor_Capacity_POD)
		{
			HD_GrowingArray<s32> growingArray(8);
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 8);
			
		}

		TEST_METHOD(Constructor_Capacity_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray(8);
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 8);
		}

		TEST_METHOD(Constructor_Copy_POD)
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

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray1;
			growingArray1.EmplaceBack("haha0");
			growingArray1.EmplaceBack("haha1");
			growingArray1.EmplaceBack("haha2");

			HD_GrowingArray<HD_String> growingArray2(growingArray1);
			Assert::IsNotNull(growingArray2.myData);
			Assert::IsTrue(growingArray2[0] == "haha0");
			Assert::IsTrue(growingArray2[1] == "haha1");
			Assert::IsTrue(growingArray2[2] == "haha2");
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Constructor_Move)
		{
			HD_GrowingArray<HD_String> growingArray1;
			growingArray1.EmplaceBack("haha0");
			growingArray1.EmplaceBack("haha1");
			growingArray1.EmplaceBack("haha2");

			HD_GrowingArray<HD_String> growingArray2(HD_Move(growingArray1));

			Assert::IsNull(growingArray1.myData);
			Assert::AreEqual(growingArray1.mySize, 0);
			Assert::AreEqual(growingArray1.myCapacity, 0);

			Assert::IsNotNull(growingArray2.myData);
			Assert::IsTrue(growingArray2[0] == "haha0");
			Assert::IsTrue(growingArray2[1] == "haha1");
			Assert::IsTrue(growingArray2[2] == "haha2");
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Constructor_InitializerList_POD)
		{
			HD_GrowingArray<s32> growingArray = { 0, 1, 2 };
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(Constructor_InitializerList_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray = { "haha0", "haha1", "haha2" };
			Assert::IsNotNull(growingArray.myData);
			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha1");
			Assert::IsTrue(growingArray[2] == "haha2");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(Destructor_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			growingArray.~HD_GrowingArray();
			Assert::IsNull(growingArray.myData);
		}

		TEST_METHOD(Destructor_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			growingArray.~HD_GrowingArray();
			Assert::IsNull(growingArray.myData);
		}

		TEST_METHOD(GetData_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			s32* data = growingArray.GetData();
			Assert::IsNotNull(data);
			Assert::AreEqual(data[0], 0);
			Assert::AreEqual(data[1], 1);
			Assert::AreEqual(data[2], 2);

			const HD_GrowingArray<s32> growingArrayConst = growingArray;
			const s32* dataConst = growingArrayConst.GetData();
			Assert::IsNotNull(dataConst);
			Assert::AreEqual(dataConst[0], 0);
			Assert::AreEqual(dataConst[1], 1);
			Assert::AreEqual(dataConst[2], 2);
		}

		TEST_METHOD(GetData_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			HD_String* data = growingArray.GetData();
			Assert::IsNotNull(data);
			Assert::IsTrue(data[0] == "haha0");
			Assert::IsTrue(data[1] == "haha1");
			Assert::IsTrue(data[2] == "haha2");

			const HD_GrowingArray<HD_String> growingArrayConst = growingArray;
			const HD_String* dataConst = growingArrayConst.GetData();
			Assert::IsNotNull(dataConst);
			Assert::IsTrue(dataConst[0] == "haha0");
			Assert::IsTrue(dataConst[1] == "haha1");
			Assert::IsTrue(dataConst[2] == "haha2");
		}

		TEST_METHOD(PushBack_POD)
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

		TEST_METHOD(PushBack_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha1");
			Assert::IsTrue(growingArray[2] == "haha2");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(PushBack_Move)
		{
			HD_String stringToMove("haha");
			HD_GrowingArray<HD_String> growingArray;

			growingArray.PushBack(HD_Move(stringToMove));

			Assert::IsNull(stringToMove.myData);
			Assert::AreEqual(stringToMove.myLength, 0);
			Assert::AreEqual(stringToMove.myCapacity, 0);

			Assert::IsTrue(growingArray[0] == "haha");
		}

		TEST_METHOD(EmplaceBack)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha");

			Assert::IsTrue(growingArray[0] == "haha");
			Assert::AreEqual(growingArray.mySize, 1);
			Assert::AreEqual(growingArray.myCapacity, 2);
		}

		TEST_METHOD(InsertSorted_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.InsertSorted(2);
			growingArray.InsertSorted(1);
			growingArray.InsertSorted(0);

			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(InsertSorted_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.InsertSorted("c");
			growingArray.InsertSorted("b");
			growingArray.InsertSorted("a");

			Assert::IsTrue(growingArray[0] == "a");
			Assert::IsTrue(growingArray[1] == "b");
			Assert::IsTrue(growingArray[2] == "c");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(InsertSortedReverse_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.InsertSortedReverse(0);
			growingArray.InsertSortedReverse(1);
			growingArray.InsertSortedReverse(2);

			Assert::AreEqual(growingArray[0], 2);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 0);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(InsertSortedReverse_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.InsertSortedReverse("a");
			growingArray.InsertSortedReverse("b");
			growingArray.InsertSortedReverse("c");

			Assert::IsTrue(growingArray[0] == "c");
			Assert::IsTrue(growingArray[1] == "b");
			Assert::IsTrue(growingArray[2] == "a");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(Remove_POD)
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

		TEST_METHOD(Remove_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			growingArray.Remove(1);
			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha2");
			Assert::AreEqual(growingArray.mySize, 2);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(RemoveCyclic_POD)
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

		TEST_METHOD(RemoveCyclic_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");
			growingArray.EmplaceBack("haha3");

			growingArray.RemoveCyclic(1);
			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha3");
			Assert::IsTrue(growingArray[2] == "haha2");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 4);
		}

		TEST_METHOD(RemoveAll_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);
			growingArray.PushBack(3);
			growingArray.PushBack(4);
			growingArray.PushBack(5);
			growingArray.PushBack(6);
			growingArray.PushBack(7);

			growingArray.RemoveAll();
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 9);
		}

		TEST_METHOD(RemoveAll_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");
			growingArray.EmplaceBack("haha3");
			growingArray.EmplaceBack("haha4");
			growingArray.EmplaceBack("haha5");
			growingArray.EmplaceBack("haha6");
			growingArray.EmplaceBack("haha7");

			growingArray.RemoveAll();
			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 9);
		}

		TEST_METHOD(Size)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::AreEqual(growingArray.GetSize(), 0);

			growingArray.PushBack(0);
			Assert::AreEqual(growingArray.GetSize(), 1);

			growingArray.PushBack(1);
			Assert::AreEqual(growingArray.GetSize(), 2);

			growingArray.PushBack(2);
			Assert::AreEqual(growingArray.GetSize(), 3);
		}

		TEST_METHOD(IsEmpty)
		{
			HD_GrowingArray<s32> growingArray;
			Assert::IsTrue(growingArray.GetIsEmpty());

			growingArray.PushBack(0);
			Assert::IsFalse(growingArray.GetIsEmpty());
		}

		TEST_METHOD(Reserve)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.Reserve(8);

			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray.mySize, 0);
			Assert::AreEqual(growingArray.myCapacity, 8);
		}

		TEST_METHOD(Resize_POD)
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

		TEST_METHOD(Resize_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.Resize(4);

			TestUtils::StringDataCheckIsUninitialized(growingArray[0]);
			TestUtils::StringDataCheckIsUninitialized(growingArray[1]);
			TestUtils::StringDataCheckIsUninitialized(growingArray[2]);
			TestUtils::StringDataCheckIsUninitialized(growingArray[3]);
			Assert::AreEqual(growingArray.mySize, 4);
			Assert::AreEqual(growingArray.myCapacity, 4);
		}

		TEST_METHOD(Swap_POD)
		{
			// Member swap function
			{
				HD_GrowingArray<s32> growingArray1;
				growingArray1.PushBack(0);
				growingArray1.PushBack(1);
				growingArray1.PushBack(2);

				HD_GrowingArray<s32> growingArray2;
				growingArray2.PushBack(3);
				growingArray2.PushBack(4);
				growingArray2.PushBack(5);

				growingArray1.Swap(growingArray2);

				Assert::AreEqual(growingArray1[0], 3);
				Assert::AreEqual(growingArray1[1], 4);
				Assert::AreEqual(growingArray1[2], 5);

				Assert::AreEqual(growingArray2[0], 0);
				Assert::AreEqual(growingArray2[1], 1);
				Assert::AreEqual(growingArray2[2], 2);
			}

			// Global swap function
			{
				HD_GrowingArray<s32> growingArray1;
				growingArray1.PushBack(0);
				growingArray1.PushBack(1);
				growingArray1.PushBack(2);

				HD_GrowingArray<s32> growingArray2;
				growingArray2.PushBack(3);
				growingArray2.PushBack(4);
				growingArray2.PushBack(5);

				HD_Swap(growingArray1, growingArray2);

				Assert::AreEqual(growingArray1[0], 3);
				Assert::AreEqual(growingArray1[1], 4);
				Assert::AreEqual(growingArray1[2], 5);

				Assert::AreEqual(growingArray2[0], 0);
				Assert::AreEqual(growingArray2[1], 1);
				Assert::AreEqual(growingArray2[2], 2);
			}
		}

		TEST_METHOD(Swap_NonPOD)
		{
			// Member swap function
			{
				HD_GrowingArray<HD_String> growingArray1;
				growingArray1.EmplaceBack("haha0");
				growingArray1.EmplaceBack("haha1");
				growingArray1.EmplaceBack("haha2");

				HD_GrowingArray<HD_String> growingArray2;
				growingArray2.EmplaceBack("haha3");
				growingArray2.EmplaceBack("haha4");
				growingArray2.EmplaceBack("haha5");

				growingArray1.Swap(growingArray2);

				Assert::IsTrue(growingArray1[0] == "haha3");
				Assert::IsTrue(growingArray1[1] == "haha4");
				Assert::IsTrue(growingArray1[2] == "haha5");

				Assert::IsTrue(growingArray2[0] == "haha0");
				Assert::IsTrue(growingArray2[1] == "haha1");
				Assert::IsTrue(growingArray2[2] == "haha2");
			}

			// Global swap function
			{
				HD_GrowingArray<HD_String> growingArray1;
				growingArray1.EmplaceBack("haha0");
				growingArray1.EmplaceBack("haha1");
				growingArray1.EmplaceBack("haha2");

				HD_GrowingArray<HD_String> growingArray2;
				growingArray2.EmplaceBack("haha3");
				growingArray2.EmplaceBack("haha4");
				growingArray2.EmplaceBack("haha5");

				HD_Swap(growingArray1, growingArray2);

				Assert::IsTrue(growingArray1[0] == "haha3");
				Assert::IsTrue(growingArray1[1] == "haha4");
				Assert::IsTrue(growingArray1[2] == "haha5");

				Assert::IsTrue(growingArray2[0] == "haha0");
				Assert::IsTrue(growingArray2[1] == "haha1");
				Assert::IsTrue(growingArray2[2] == "haha2");
			}
		}

		TEST_METHOD(Operator_Subscript_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);

			const HD_GrowingArray<s32> growingArrayConst = growingArray;
			Assert::AreEqual(growingArrayConst[0], 0);
			Assert::AreEqual(growingArrayConst[1], 1);
			Assert::AreEqual(growingArrayConst[2], 2);
		}

		TEST_METHOD(Operator_Subscript_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha1");
			Assert::IsTrue(growingArray[2] == "haha2");

			const HD_GrowingArray<HD_String> growingArrayConst = growingArray;
			Assert::IsTrue(growingArrayConst[0] == "haha0");
			Assert::IsTrue(growingArrayConst[1] == "haha1");
			Assert::IsTrue(growingArrayConst[2] == "haha2");
		}

		TEST_METHOD(Operator_Assignment_POD)
		{
			HD_GrowingArray<s32> growingArray1;
			growingArray1.PushBack(0);
			growingArray1.PushBack(1);
			growingArray1.PushBack(2);

			HD_GrowingArray<s32> growingArray2;
			growingArray2 = growingArray1;

			Assert::IsNotNull(growingArray2.myData);
			Assert::AreEqual(growingArray2[0], 0);
			Assert::AreEqual(growingArray2[1], 1);
			Assert::AreEqual(growingArray2[2], 2);
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Operator_Assignment_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray1;

			{
				HD_GrowingArray<HD_String> growingArray2;
				growingArray2.EmplaceBack("haha0");
				growingArray2.EmplaceBack("haha1");
				growingArray2.EmplaceBack("haha2");

				growingArray1 = growingArray2;
			}

			Assert::IsNotNull(growingArray1.myData);
			Assert::IsTrue(growingArray1[0] == "haha0");
			Assert::IsTrue(growingArray1[1] == "haha1");
			Assert::IsTrue(growingArray1[2] == "haha2");
			Assert::AreEqual(growingArray1.mySize, 3);
			Assert::AreEqual(growingArray1.myCapacity, 3);
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			HD_GrowingArray<HD_String> growingArray1;
			growingArray1.EmplaceBack("haha0");
			growingArray1.EmplaceBack("haha1");
			growingArray1.EmplaceBack("haha2");

			HD_GrowingArray<HD_String> growingArray2;
			growingArray2 = HD_Move(growingArray1);

			Assert::IsNull(growingArray1.myData);
			Assert::AreEqual(growingArray1.mySize, 0);
			Assert::AreEqual(growingArray1.myCapacity, 0);

			Assert::IsNotNull(growingArray2.myData);
			Assert::IsTrue(growingArray2[0] == "haha0");
			Assert::IsTrue(growingArray2[1] == "haha1");
			Assert::IsTrue(growingArray2[2] == "haha2");
			Assert::AreEqual(growingArray2.mySize, 3);
			Assert::AreEqual(growingArray2.myCapacity, 3);
		}

		TEST_METHOD(Operator_Assignment_InitializerList_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray = { 0, 1, 2 };

			Assert::IsNotNull(growingArray.myData);
			Assert::AreEqual(growingArray[0], 0);
			Assert::AreEqual(growingArray[1], 1);
			Assert::AreEqual(growingArray[2], 2);
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(Operator_Assignment_InitializerList_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray = { "haha0", "haha1", "haha2" };

			Assert::IsNotNull(growingArray.myData);
			Assert::IsTrue(growingArray[0] == "haha0");
			Assert::IsTrue(growingArray[1] == "haha1");
			Assert::IsTrue(growingArray[2] == "haha2");
			Assert::AreEqual(growingArray.mySize, 3);
			Assert::AreEqual(growingArray.myCapacity, 3);
		}

		TEST_METHOD(GetFirst_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray.GetFirst(), 0);
		}

		TEST_METHOD(GetFirst_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			Assert::IsTrue(growingArray.GetFirst() == "haha0");
		}

		TEST_METHOD(GetLast_POD)
		{
			HD_GrowingArray<s32> growingArray;
			growingArray.PushBack(0);
			growingArray.PushBack(1);
			growingArray.PushBack(2);

			Assert::AreEqual(growingArray.GetLast(), 2);
		}

		TEST_METHOD(GetLast_NonPOD)
		{
			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack("haha0");
			growingArray.EmplaceBack("haha1");
			growingArray.EmplaceBack("haha2");

			Assert::IsTrue(growingArray.GetLast() == "haha2");
		}

		TEST_METHOD(Iterator_POD)
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

		TEST_METHOD(Iterator_NonPOD)
		{
			const char* strings[3] = { "haha0", "haha1", "haha2" };

			HD_GrowingArray<HD_String> growingArray;
			growingArray.EmplaceBack(strings[0]);
			growingArray.EmplaceBack(strings[1]);
			growingArray.EmplaceBack(strings[2]);

			s32 index = 0;
			for (const HD_String& entry : growingArray)
			{
				Assert::IsTrue(entry == strings[index]);
				index++;
			}

			const HD_GrowingArray<HD_String> growingArrayConst = growingArray;

			index = 0;
			for (const HD_String& entry : growingArrayConst)
			{
				Assert::IsTrue(entry == strings[index]);
				index++;
			}
		}
	};
}
