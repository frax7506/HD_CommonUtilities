#include "stdafx.h"
#include "HD_String.h"

#define UNACCEPTABLE_BUFFER_OVERSIZE_FACTOR 1.5f

HD_String::HD_String()
	: myLength(0)
	, myData(nullptr)
{
}

HD_String::HD_String(const char* aString)
{
	myLength = HD_Strlen(aString);
	myData = new char[myLength + 1] { 0 };
	memcpy(myData, aString, myLength);
}

HD_String::HD_String(const HD_String& aString)
	: HD_String(aString.GetBuffer())
{
}

HD_String::HD_String(HD_String&& aString)
{
	myLength = aString.myLength;
	myData = aString.myData;
	aString.myData = nullptr;
}

HD_String::~HD_String()
{
	HD_SafeDeleteArray(myData);
}

const char* HD_String::GetBuffer() const
{
	return myData;
}

int HD_String::GetLength() const
{
	return myLength;
}

char HD_String::GetCharAt(int aIndex) const
{
	assert(0 <= aIndex && aIndex < myLength);
	return myData[aIndex];
}

HD_String& HD_String::operator=(const char* aString)
{
	int length = HD_Strlen(aString);

	bool isCurrentBufferTooSmall = myLength < length;
	bool isCurrentBufferTooBig = static_cast<float>(myLength) / static_cast<float>(length) >= UNACCEPTABLE_BUFFER_OVERSIZE_FACTOR;

	if (isCurrentBufferTooSmall || isCurrentBufferTooBig)
	{
		HD_SafeDeleteArray(myData);
		myData = new char[length + 1] { 0 };
	}

	myLength = length;
	memcpy(myData, aString, myLength);

	return *this;
}

HD_String& HD_String::operator=(const HD_String& aString)
{
	*this = aString.GetBuffer();
	return *this;
}

HD_String& HD_String::operator=(HD_String&& aString)
{
	myLength = aString.myLength;
	myData = aString.myData;
	aString.myData = nullptr;

	return *this;
}
