#include "stdafx.h"
#include "HD_Format.h"

#include <cstdarg>

HD_Format::HD_Format(const char* aFormat, ...)
{
	memset(myBuffer, 0, HD_FORMAT_MAX_BUFFER_SIZE);

	va_list args;
	va_start(args, aFormat);
	vsprintf_s(myBuffer, aFormat, args);
	va_end(args);
}

const char* HD_Format::GetBuffer() const
{
	return myBuffer;
}
