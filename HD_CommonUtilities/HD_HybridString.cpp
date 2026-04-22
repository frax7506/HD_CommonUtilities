#include "stdafx.h"
#include "HD_HybridString.h"

#include "HD_StringUtils.h"

HD_HybridString::HD_HybridString()
	: myData(nullptr)
	, myMode(StringMode_Invalid)
{
}

HD_HybridString::HD_HybridString(const char* aString)
{
	int length = HD_Strlen(aString);
	myData = new char[length + 1] { 0 };
	memcpy(myData, aString, length);

	myMode = StringMode_NonWide;
}

HD_HybridString::HD_HybridString(const wchar_t* aString)
{
	int length = HD_Strlen(aString);
	myData = new char[(sizeof(wchar_t) * length) + 2] { 0 };
	memcpy(myData, aString, sizeof(wchar_t) * length);

	myMode = StringMode_Wide;
}

HD_HybridString::~HD_HybridString()
{
	HD_SafeDeleteArray(myData);
}

const char* HD_HybridString::GetBuffer() const
{
	assert(!GetIsWide() && "HD_HybridString::GetBuffer was called on a wide or invalid instance.");
	return myData;
}

const wchar_t* HD_HybridString::GetWBuffer() const
{
	assert(GetIsWide() && "HD_HybridString::GetWBuffer was called on a non-wide or invalid instance.");
	return reinterpret_cast<const wchar_t*>(myData);
}

bool HD_HybridString::GetIsWide() const
{
	return myMode == StringMode_Wide;
}
