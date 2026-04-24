#pragma once

#define HD_FORMAT_MAX_BUFFER_SIZE 512

class HD_Format
{
public:
	HD_Format(const char* aFormat, ...);

	const char* GetBuffer() const;

private:
	char myBuffer[HD_FORMAT_MAX_BUFFER_SIZE];
};
