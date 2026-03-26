#pragma once

class HD_String
{
public:
	HD_String();
	HD_String(const char* aString);
	HD_String(const HD_String& aString);
	HD_String(HD_String&& aString);
	~HD_String();

	const char* GetBuffer() const;
	int GetLength() const;
	char GetCharAt(int aIndex) const;

	HD_String& operator=(const char* aString);
	HD_String& operator=(const HD_String& aString);
	HD_String& operator=(HD_String&& aString);

private:
	int myLength;
	char* myData;
};
