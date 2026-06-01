#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_StaticArray.h"
#include "HD_String.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_StaticArray_Test)
	{
	public:
		TEST_METHOD(Constructor_POD)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				Assert::AreEqual(staticArray[index], 0);
			}
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				TestUtils::StringDataCheckIsUninitialized(staticArray[index]);
			}
		}

		TEST_METHOD(Constructor_Copy_POD)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (s32 index = 0; index < staticArray1.Size(); index++)
			{
				staticArray1[index] = index;
			}

			HD_StaticArray<s32, 8> staticArray2(staticArray1);

			for (s32 index = 0, e = staticArray2.Size(); index < e; index++)
			{
				Assert::AreEqual(staticArray2[index], index);
			}
		}

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			const char* strings[8] = {"0", "1", "2", "3", "4", "5", "6", "7"};

			HD_StaticArray<HD_String, 8> staticArray1;

			for (s32 index = 0; index < staticArray1.Size(); index++)
			{
				staticArray1[index] = strings[index];
			}

			HD_StaticArray<HD_String, 8> staticArray2(staticArray1);

			for (s32 index = 0; index < staticArray2.Size(); index++)
			{
				Assert::IsTrue(staticArray2[index] == strings[index]);
			}
		}

		TEST_METHOD(Size)
		{
			HD_StaticArray<s32, 8> staticArray1;
			Assert::AreEqual(staticArray1.Size(), 8);

			HD_StaticArray<s32, 16> staticArray2;
			Assert::AreEqual(staticArray2.Size(), 16);
		}

		TEST_METHOD(Operator_Subscript_POD)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				staticArray[index] = index;
			}

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				Assert::AreEqual(staticArray[index], index);
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			for (s32 index = 0; index < staticArrayConst.Size(); index++)
			{
				Assert::AreEqual(staticArrayConst[index], index);
			}
		}

		TEST_METHOD(Operator_Subscript_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				staticArray[index] = strings[index];
			}

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				Assert::IsTrue(staticArray[index] == strings[index]);
			}

			const HD_StaticArray<HD_String, 8> staticArrayConst(staticArray);

			for (s32 index = 0; index < staticArrayConst.Size(); index++)
			{
				Assert::IsTrue(staticArrayConst[index] == strings[index]);
			}
		}

		TEST_METHOD(Operator_Assignment_POD)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (s32 index = 0; index < staticArray1.Size(); index++)
			{
				staticArray1[index] = index;
			}

			HD_StaticArray<s32, 8> staticArray2;
			staticArray2 = staticArray1;

			for (s32 index = 0; index < staticArray2.Size(); index++)
			{
				Assert::AreEqual(staticArray2[index], index);
			}
		}

		TEST_METHOD(Operator_Assignment_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray1;

			{
				HD_StaticArray<HD_String, 8> staticArray2;

				for (s32 index = 0; index < staticArray2.Size(); index++)
				{
					staticArray2[index] = strings[index];
				}

				staticArray1 = staticArray2;
			}

			for (s32 index = 0; index < staticArray1.Size(); index++)
			{
				Assert::IsTrue(staticArray1[index] == strings[index]);
			}
		}

		TEST_METHOD(Iterator_POD)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				staticArray[index] = index;
			}

			s32 index = 0;
			for (s32 value : staticArray)
			{
				Assert::AreEqual(value, index);
				index++;
			}

			index = 0;
			for (auto it = staticArray.begin(); it != staticArray.end(); it++)
			{
				Assert::AreEqual(*it, index);
				index++;
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			index = 0;
			for (s32 value : staticArrayConst)
			{
				Assert::AreEqual(value, index);
				index++;
			}

			index = 0;
			for (auto it = staticArrayConst.begin(); it != staticArrayConst.end(); it++)
			{
				Assert::AreEqual(*it, index);
				index++;
			}
		}

		TEST_METHOD(Iterator_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 index = 0; index < staticArray.Size(); index++)
			{
				staticArray[index] = strings[index];
			}

			s32 index = 0;
			for (HD_String& string : staticArray)
			{
				Assert::IsTrue(string == strings[index]);
				index++;
			}

			index = 0;
			for (auto it = staticArray.begin(); it != staticArray.end(); it++)
			{
				Assert::IsTrue((*it) == strings[index]);
				index++;
			}

			const HD_StaticArray<HD_String, 8> staticArrayConst(staticArray);

			index = 0;
			for (const HD_String& string : staticArrayConst)
			{
				Assert::IsTrue(string == strings[index]);
				index++;
			}

			index = 0;
			for (auto it = staticArrayConst.begin(); it != staticArrayConst.end(); it++)
			{
				Assert::IsTrue((*it) == strings[index]);
				index++;
			}
		}
	};
}
