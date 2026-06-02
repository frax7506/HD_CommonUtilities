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

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				Assert::AreEqual(staticArray[i], 0);
			}
		}

		TEST_METHOD(Constructor_NonPOD)
		{
			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				TestUtils::StringDataCheckIsUninitialized(staticArray[i]);
			}
		}

		TEST_METHOD(Constructor_Copy_POD)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (s32 i = 0; i < staticArray1.Size(); i++)
			{
				staticArray1[i] = i;
			}

			HD_StaticArray<s32, 8> staticArray2(staticArray1);

			for (s32 i = 0, e = staticArray2.Size(); i < e; i++)
			{
				Assert::AreEqual(staticArray2[i], i);
			}
		}

		TEST_METHOD(Constructor_Copy_NonPOD)
		{
			const char* strings[8] = {"0", "1", "2", "3", "4", "5", "6", "7"};

			HD_StaticArray<HD_String, 8> staticArray1;

			for (s32 i = 0; i < staticArray1.Size(); i++)
			{
				staticArray1[i] = strings[i];
			}

			HD_StaticArray<HD_String, 8> staticArray2(staticArray1);

			for (s32 i = 0; i < staticArray2.Size(); i++)
			{
				Assert::IsTrue(staticArray2[i] == strings[i]);
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

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				staticArray[i] = i;
			}

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				Assert::AreEqual(staticArray[i], i);
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			for (s32 i = 0; i < staticArrayConst.Size(); i++)
			{
				Assert::AreEqual(staticArrayConst[i], i);
			}
		}

		TEST_METHOD(Operator_Subscript_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				staticArray[i] = strings[i];
			}

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				Assert::IsTrue(staticArray[i] == strings[i]);
			}

			const HD_StaticArray<HD_String, 8> staticArrayConst(staticArray);

			for (s32 i = 0; i < staticArrayConst.Size(); i++)
			{
				Assert::IsTrue(staticArrayConst[i] == strings[i]);
			}
		}

		TEST_METHOD(Operator_Assignment_POD)
		{
			HD_StaticArray<s32, 8> staticArray1;

			for (s32 i = 0; i < staticArray1.Size(); i++)
			{
				staticArray1[i] = i;
			}

			HD_StaticArray<s32, 8> staticArray2;
			staticArray2 = staticArray1;

			for (s32 i = 0; i < staticArray2.Size(); i++)
			{
				Assert::AreEqual(staticArray2[i], i);
			}
		}

		TEST_METHOD(Operator_Assignment_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray1;

			{
				HD_StaticArray<HD_String, 8> staticArray2;

				for (s32 i = 0; i < staticArray2.Size(); i++)
				{
					staticArray2[i] = strings[i];
				}

				staticArray1 = staticArray2;
			}

			for (s32 i = 0; i < staticArray1.Size(); i++)
			{
				Assert::IsTrue(staticArray1[i] == strings[i]);
			}
		}

		TEST_METHOD(Iterator_POD)
		{
			HD_StaticArray<s32, 8> staticArray;

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				staticArray[i] = i;
			}

			s32 i = 0;
			for (s32 value : staticArray)
			{
				Assert::AreEqual(value, i);
				i++;
			}

			i = 0;
			for (auto it = staticArray.begin(); it != staticArray.end(); it++)
			{
				Assert::AreEqual(*it, i);
				i++;
			}

			const HD_StaticArray<s32, 8> staticArrayConst(staticArray);

			i = 0;
			for (s32 value : staticArrayConst)
			{
				Assert::AreEqual(value, i);
				i++;
			}

			i = 0;
			for (auto it = staticArrayConst.begin(); it != staticArrayConst.end(); it++)
			{
				Assert::AreEqual(*it, i);
				i++;
			}
		}

		TEST_METHOD(Iterator_NonPOD)
		{
			const char* strings[8] = { "0", "1", "2", "3", "4", "5", "6", "7" };

			HD_StaticArray<HD_String, 8> staticArray;

			for (s32 i = 0; i < staticArray.Size(); i++)
			{
				staticArray[i] = strings[i];
			}

			s32 i = 0;
			for (HD_String& string : staticArray)
			{
				Assert::IsTrue(string == strings[i]);
				i++;
			}

			i = 0;
			for (auto it = staticArray.begin(); it != staticArray.end(); it++)
			{
				Assert::IsTrue((*it) == strings[i]);
				i++;
			}

			const HD_StaticArray<HD_String, 8> staticArrayConst(staticArray);

			i = 0;
			for (const HD_String& string : staticArrayConst)
			{
				Assert::IsTrue(string == strings[i]);
				i++;
			}

			i = 0;
			for (auto it = staticArrayConst.begin(); it != staticArrayConst.end(); it++)
			{
				Assert::IsTrue((*it) == strings[i]);
				i++;
			}
		}
	};
}
