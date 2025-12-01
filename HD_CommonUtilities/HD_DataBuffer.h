#pragma once

template<int aSize>
class HD_DataBuffer
{
public:
	HD_DataBuffer();

	char* GetBuffer();
	int GetSize() const;

	template<typename T>
	void ReadFromBuffer(T& aDataToWriteTo, int aSizeOfDataToWriteTo);

	template<typename T>
	void WriteToBuffer(const T& aDataToReadFrom, int aSizeOfDataToReadFrom);

protected:
	char myData[aSize];
	int myReadWriteIndex;
};

template<int aSize>
HD_DataBuffer<aSize>::HD_DataBuffer()
	: myReadWriteIndex(0)
{
	memset(myData, 0, aSize);
}

template<int aSize>
char* HD_DataBuffer<aSize>::GetBuffer()
{
	return myData;
}

template<int aSize>
int HD_DataBuffer<aSize>::GetSize() const
{
	return myReadWriteIndex;
}

template<int aSize>
template<typename T>
void HD_DataBuffer<aSize>::ReadFromBuffer(T& aDataToWriteTo, int aSizeOfDataToWriteTo)
{
	memcpy(&aDataToWriteTo, myData + myReadWriteIndex, aSizeOfDataToWriteTo);
	myReadWriteIndex += aSizeOfDataToWriteTo;
}

template<int aSize>
template<typename T>
void HD_DataBuffer<aSize>::WriteToBuffer(const T& aDataToReadFrom, int aSizeOfDataToReadFrom)
{
	memcpy(myData + myReadWriteIndex, &aDataToReadFrom, aSizeOfDataToReadFrom);
	myReadWriteIndex += aSizeOfDataToReadFrom;
}
