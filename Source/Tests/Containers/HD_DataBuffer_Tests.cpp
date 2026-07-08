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

			Assert::AreEqual(dataBuffer.myReadWriteIndex, 0u);

			u32 dataToCompareTo = 0;
			bool areEqual = memcmp(dataBuffer.myData, &dataToCompareTo, 4 * sizeof(u8)) == 0;
			Assert::IsTrue(areEqual);
		}

		TEST_METHOD(GetBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			u8* buffer = dataBuffer.GetBuffer();

			u32 dataToCompareTo = 0;
			bool areEqual = memcmp(buffer, &dataToCompareTo, 4 * sizeof(u8)) == 0;
			Assert::IsTrue(areEqual);
		}

		TEST_METHOD(GetSize)
		{
			HD_DataBuffer<4> dataBuffer;

			Assert::AreEqual(dataBuffer.GetSize(), 0u);

			u8 dataToReadFrom = 0;
			dataBuffer.WriteToBuffer(dataToReadFrom, sizeof(dataToReadFrom));

			Assert::AreEqual(dataBuffer.GetSize(), 1u);
		}

		TEST_METHOD(ReadFromBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			u8 dataToFillBufferWith1 = 1;
			u8 dataToFillBufferWith2 = 2;

			u8* buffer = dataBuffer.GetBuffer();
			memcpy(buffer + 0, &dataToFillBufferWith1, sizeof(dataToFillBufferWith1));
			memcpy(buffer + 1, &dataToFillBufferWith2, sizeof(dataToFillBufferWith2));

			u8 dataToWriteTo1 = 0;
			u8 dataToWriteTo2 = 0;

			dataBuffer.ReadFromBuffer(dataToWriteTo1, sizeof(dataToWriteTo1));
			dataBuffer.ReadFromBuffer(dataToWriteTo2, sizeof(dataToWriteTo2));

			Assert::AreEqual(static_cast<u32>(dataToWriteTo1), 1u);
			Assert::AreEqual(static_cast<u32>(dataToWriteTo2), 2u);
		}

		TEST_METHOD(WriteToBuffer)
		{
			HD_DataBuffer<4> dataBuffer;

			u8 dataToReadFrom1 = 1;
			u8 dataToReadFrom2 = 2;

			dataBuffer.WriteToBuffer(dataToReadFrom1, sizeof(dataToReadFrom1));
			dataBuffer.WriteToBuffer(dataToReadFrom2, sizeof(dataToReadFrom2));

			u8* buffer = dataBuffer.GetBuffer();
			u8 dataToCompareTo1 = 1;
			u8 dataToCompareTo2 = 2;
			bool areEqual1 = memcmp(buffer + 0, &dataToCompareTo1, sizeof(dataToCompareTo1)) == 0;
			bool areEqual2 = memcmp(buffer + 1, &dataToCompareTo2, sizeof(dataToCompareTo2)) == 0;

			Assert::IsTrue(areEqual1);
			Assert::IsTrue(areEqual2);
		}
	};
}
