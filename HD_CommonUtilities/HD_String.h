#pragma once

class HD_String
{
public:
	HD_String();
	~HD_String();
	HD_String(const char* aString);
	HD_String(const HD_String& aString);
	HD_String(HD_String&& aString);

	const char* GetBuffer();

	HD_String& operator=(const char* String);
	HD_String& operator=(const HD_String& aString);
	HD_String& operator=(HD_String&& aString);

private:
	char* myData;
	int mySize;
	int myCapacity;
};

// fortsätt här
