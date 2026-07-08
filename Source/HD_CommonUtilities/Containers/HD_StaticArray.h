#pragma once

#include "HD_ArrayIterator.h"
#include "HD_Types.h"

#include <cassert>

template<typename T, SizeType aSize>
class HD_StaticArray
{
public:
	typedef HD_ArrayIterator<T> Iterator;
	typedef HD_ArrayIterator<const T> ConstIterator;

	HD_StaticArray();
	HD_StaticArray(const HD_StaticArray& aStaticArray);

	SizeType Size() const;

	T& operator[](u32 aIndex);
	const T& operator[](u32 aIndex) const;

	HD_StaticArray& operator=(const HD_StaticArray& aStaticArray);

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	T myData[aSize];
};

template<typename T, SizeType aSize>
HD_StaticArray<T, aSize>::HD_StaticArray()
{
	for (u32 i = 0; i < aSize; i++)
		myData[i] = T();
}

template<typename T, SizeType aSize>
HD_StaticArray<T, aSize>::HD_StaticArray(const HD_StaticArray& aStaticArray)
{
	(*this) = aStaticArray;
}

template<typename T, SizeType aSize>
SizeType HD_StaticArray<T, aSize>::Size() const
{
	return aSize;
}

template<typename T, SizeType aSize>
T& HD_StaticArray<T, aSize>::operator[](u32 aIndex)
{
	assert(0 <= aIndex && aIndex < aSize);
	return myData[aIndex];
}

template<typename T, SizeType aSize>
const T& HD_StaticArray<T, aSize>::operator[](u32 aIndex) const
{
	assert(0 <= aIndex && aIndex < aSize);
	return myData[aIndex];
}

template<typename T, SizeType aSize>
HD_StaticArray<T, aSize>& HD_StaticArray<T, aSize>::operator=(const HD_StaticArray& aStaticArray)
{
	for (u32 i = 0; i < aSize; i++)
		myData[i] = aStaticArray[i];

	return *this;
}

template<typename T, SizeType aSize>
typename HD_StaticArray<T, aSize>::Iterator HD_StaticArray<T, aSize>::begin()
{
	return Iterator(myData);
}

template<typename T, SizeType aSize>
typename HD_StaticArray<T, aSize>::Iterator HD_StaticArray<T, aSize>::end()
{
	return Iterator(myData + aSize);
}

template<typename T, SizeType aSize>
typename HD_StaticArray<T, aSize>::ConstIterator HD_StaticArray<T, aSize>::begin() const
{
	return ConstIterator(myData);
}

template<typename T, SizeType aSize>
typename HD_StaticArray<T, aSize>::ConstIterator HD_StaticArray<T, aSize>::end() const
{
	return ConstIterator(myData + aSize);
}
