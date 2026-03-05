#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_DataBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_DataBuffer_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_DataBuffer<4> dataBuffer;

			Assert::AreEqual(dataBuffer.myReadWriteIndex, 0);

			const int dataToCompareTo = 0;
			const bool areEqual = memcmp(dataBuffer.myData, &dataToCompareTo, sizeof(char) * 4) == 0;
			Assert::IsTrue(areEqual);
		}

		TEST_METHOD(GetBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			char* buffer = dataBuffer.GetBuffer();

			const int dataToCompareTo = 0;
			const bool areEqual = memcmp(buffer, &dataToCompareTo, sizeof(char) * 4) == 0;
			Assert::IsTrue(areEqual);
		}

		TEST_METHOD(GetSize)
		{
			HD_DataBuffer<4> dataBuffer;

			Assert::AreEqual(dataBuffer.GetSize(), 0);

			const char dataToReadFrom = 0;
			dataBuffer.WriteToBuffer(dataToReadFrom, sizeof(dataToReadFrom));

			Assert::AreEqual(dataBuffer.GetSize(), 1);
		}

		TEST_METHOD(ReadFromBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			const char dataToFillBufferWith1 = 1;
			const char dataToFillBufferWith2 = 2;

			char* buffer = dataBuffer.GetBuffer();
			memcpy(buffer + 0, &dataToFillBufferWith1, sizeof(dataToFillBufferWith1));
			memcpy(buffer + 1, &dataToFillBufferWith2, sizeof(dataToFillBufferWith2));

			char dataToWriteTo1 = 0;
			char dataToWriteTo2 = 0;

			dataBuffer.ReadFromBuffer(dataToWriteTo1, sizeof(dataToWriteTo1));
			dataBuffer.ReadFromBuffer(dataToWriteTo2, sizeof(dataToWriteTo2));

			Assert::AreEqual(static_cast<int>(dataToWriteTo1), 1);
			Assert::AreEqual(static_cast<int>(dataToWriteTo2), 2);
		}

		TEST_METHOD(WriteToBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			char dataToReadFrom1 = 1;
			char dataToReadFrom2 = 2;

			dataBuffer.WriteToBuffer(dataToReadFrom1, sizeof(dataToReadFrom1));
			dataBuffer.WriteToBuffer(dataToReadFrom2, sizeof(dataToReadFrom2));

			char* buffer = dataBuffer.GetBuffer();
			const char dataToCompareTo1 = 1;
			const char dataToCompareTo2 = 2;
			const bool areEqual1 = memcmp(buffer + 0, &dataToCompareTo1, sizeof(dataToCompareTo1)) == 0;
			const bool areEqual2 = memcmp(buffer + 1, &dataToCompareTo2, sizeof(dataToCompareTo2)) == 0;

			Assert::IsTrue(areEqual1);
			Assert::IsTrue(areEqual2);
		}
	};
}
