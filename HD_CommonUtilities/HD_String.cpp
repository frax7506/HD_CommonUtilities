#include "stdafx.h"
#include "HD_String.h"

HD_String::HD_String()
	: myLength(0)
	, myData(nullptr)
{
}

HD_String::HD_String(const char* aString)
{
	*this = aString;
}

HD_String::HD_String(const HD_String& aString)
{
	*this = aString;
}

HD_String::HD_String(HD_String&& aString)
{
	*this = HD_Move(aString);
}

HD_String::~HD_String()
{
	HD_SafeDeleteArray(myData);
}

const char* HD_String::GetBuffer() const
{
	return myData;
}

unsigned int HD_String::GetLength() const
{
	return myLength;
}

HD_String& HD_String::operator=(const char* aString)
{
	HD_SafeDeleteArray(myData);
	myLength = HD_Strlen(aString);
	myData = new char[myLength + 1];
	memset(myData, 0, myLength + 1);
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
	HD_SafeDeleteArray(myData);
	myLength = aString.myLength;
	myData = aString.myData;
	aString.myData = nullptr;

	return *this;
}
