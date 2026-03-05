#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_StaticArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
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
}
