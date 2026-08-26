#pragma once

#include "HD_Types.h"

#include <cstring>

template<SizeType aNrOfBytes>
class HD_DataBuffer
{
public:
	HD_DataBuffer();

	u8* GetBuffer();
	SizeType GetSize() const;

	template<typename T>
	void ReadFromBuffer(T& aDataToWriteTo, SizeType aSizeOfDataToWriteTo);

	template<typename T>
	void WriteToBuffer(const T& aDataToReadFrom, SizeType aSizeOfDataToReadFrom);

protected:
	u8 myData[aNrOfBytes];
	u32 myReadWriteIndex;
};

template<SizeType aNrOfBytes>
HD_DataBuffer<aNrOfBytes>::HD_DataBuffer()
	: myReadWriteIndex(0)
{
	memset(myData, 0, aNrOfBytes);
}

template<SizeType aNrOfBytes>
u8* HD_DataBuffer<aNrOfBytes>::GetBuffer()
{
	return myData;
}

template<SizeType aNrOfBytes>
SizeType HD_DataBuffer<aNrOfBytes>::GetSize() const
{
	return myReadWriteIndex;
}

template<SizeType aNrOfBytes>
template<typename T>
void HD_DataBuffer<aNrOfBytes>::ReadFromBuffer(T& aDataToWriteTo, u32 aSizeOfDataToWriteTo)
{
	memcpy(&aDataToWriteTo, myData + myReadWriteIndex, aSizeOfDataToWriteTo);
	myReadWriteIndex += aSizeOfDataToWriteTo;
}

template<SizeType aNrOfBytes>
template<typename T>
void HD_DataBuffer<aNrOfBytes>::WriteToBuffer(const T& aDataToReadFrom, u32 aSizeOfDataToReadFrom)
{
	memcpy(myData + myReadWriteIndex, &aDataToReadFrom, aSizeOfDataToReadFrom);
	myReadWriteIndex += aSizeOfDataToReadFrom;
}
