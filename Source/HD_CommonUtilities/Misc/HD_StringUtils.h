#pragma once

#include "HD_Types.h"

#include <cstring>
#include <wchar.h>

template<typename T>
inline SizeType HD_Strlen(const T* aString);

template<typename T>
inline s32 HD_Strcmp(const T* aString1, const T* aString2);

template<>
inline SizeType HD_Strlen(const char* aString)
{
	return static_cast<SizeType>(strlen(aString));
}

template<>
inline SizeType HD_Strlen(const wchar_t* aString)
{
	return static_cast<SizeType>(wcslen(aString));
}

template<>
inline s32 HD_Strcmp(const char* aString1, const char* aString2)
{
	return strcmp(aString1, aString2);
}

template<>
inline s32 HD_Strcmp(const wchar_t* aString1, const wchar_t* aString2)
{
	return wcscmp(aString1, aString2);
}
