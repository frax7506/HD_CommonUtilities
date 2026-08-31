#pragma once

#include "HD_Types.h"

typedef u8 ControlByte_Type;

template<typename T>
class HD_HashArrayIterator
{
public:
	HD_HashArrayIterator();
	HD_HashArrayIterator(const ControlByte_Type* aControlBytes, T* aArray, u32 aIndex, SizeType aHashArrayCapacity);
	HD_HashArrayIterator(const HD_HashArrayIterator& aIterator);

	HD_HashArrayIterator& operator++();
	HD_HashArrayIterator& operator--();
	HD_HashArrayIterator operator++(s32);
	HD_HashArrayIterator operator--(s32);
	HD_HashArrayIterator& operator+=(u32 aIncrement);
	HD_HashArrayIterator& operator-=(u32 aDecrement);
	bool operator==(const HD_HashArrayIterator& aIterator) const;
	bool operator!=(const HD_HashArrayIterator& aIterator) const;
	T& operator*() const;
	T* operator->() const;

private:
	const ControlByte_Type* myControlBytes;
	T* myArray;

	u32 myIndex;
	SizeType myHashArrayCapacity;
};

template<typename T>
HD_HashArrayIterator<T>::HD_HashArrayIterator()
	: myControlBytes(nullptr)
	, myArray(nullptr)
	, myIndex(0)
	, myHashArrayCapacity(0)
{
}

template<typename T>
HD_HashArrayIterator<T>::HD_HashArrayIterator(const ControlByte_Type* aControlBytes, T* aArray, u32 aIndex, u32 aHashArrayCapacity)
	: myControlBytes(aControlBytes)
	, myArray(aArray)
	, myIndex(aIndex)
	, myHashArrayCapacity(aHashArrayCapacity)
{
}

template<typename T>
HD_HashArrayIterator<T>::HD_HashArrayIterator(const HD_HashArrayIterator& aIterator)
	: myControlBytes(aIterator.myControlBytes)
	, myArray(aIterator.myArray)
	, myIndex(aIterator.myIndex)
	, myHashArrayCapacity(aIterator.myHashArrayCapacity)
{
}

template<typename T>
HD_HashArrayIterator<T>& HD_HashArrayIterator<T>::operator++()
{
	do
	{
		myIndex++;
	}
	while (myIndex < myHashArrayCapacity && !(myControlBytes[myIndex] & 0b10000000));

	return *this;
}

template<typename T>
HD_HashArrayIterator<T>& HD_HashArrayIterator<T>::operator--()
{
	do
	{
		myIndex--;
	}
	while (myIndex > 0 && !(myControlBytes[myIndex] & 0b10000000));

	return *this;
}

template<typename T>
HD_HashArrayIterator<T> HD_HashArrayIterator<T>::operator++(s32)
{
	HD_HashArrayIterator iterator = *this;
	++(*this);
	return iterator;
}

template<typename T>
HD_HashArrayIterator<T> HD_HashArrayIterator<T>::operator--(s32)
{
	HD_HashArrayIterator iterator = *this;
	--(*this);
	return iterator;
}

template<typename T>
HD_HashArrayIterator<T>& HD_HashArrayIterator<T>::operator+=(u32 aIncrement)
{
	for (u32 i = 0; i < aIncrement; ++i)
		++(*this);

	return *this;
}

template<typename T>
HD_HashArrayIterator<T>& HD_HashArrayIterator<T>::operator-=(u32 aDecrement)
{
	for (u32 i = 0; i < aDecrement; ++i)
		--(*this);

	return *this;
}

template<typename T>
bool HD_HashArrayIterator<T>::operator==(const HD_HashArrayIterator& aIterator) const
{
	return myControlBytes == aIterator.myControlBytes && myIndex == aIterator.myIndex;
}

template<typename T>
bool HD_HashArrayIterator<T>::operator!=(const HD_HashArrayIterator& aIterator) const
{
	return !(*this == aIterator);
}

template<typename T>
T& HD_HashArrayIterator<T>::operator*() const
{
	return myArray[myIndex];
}

template<typename T>
T* HD_HashArrayIterator<T>::operator->() const
{
	return myArray + myIndex;
}
