#pragma once

#include "HD_Move.h"
#include "HD_Types.h"

#include <cassert>

// HD_CircularArray
// * If overflow is enabled and PushBack is called on a full array it will start
//   to overwrite the oldest items.
// * The GetFirstAndRemove function gets the oldest item and removes it, which means
//   that PushBack and GetFirstAndRemove can be used to make this array a FIFO queue.

template<typename T, SizeType aCapacity>
class HD_CircularArray
{
public:
	HD_CircularArray();

	void PushBack(const T& aItem);
	void PushBack(T&& aItem);

	template<typename... Args>
	void EmplaceBack(Args&&... args);

	void GetFirstAndRemove(T& outItem);

	void Clear();

	SizeType GetSize() const;
	SizeType GetCapacity() const;
	bool GetIsEmpty() const;

	void EnableOverflow();
	void DisableOverflow();

	T& operator[](u32 aIndex);
	const T& operator[](u32 aIndex) const;

private:
	enum eOverflowBehaviour : u8
	{
		eOverflowBehaviour_Enable,
		eOverflowBehaviour_Disable,
	};

	u32 myFirstIndex;
	u32 myWriteIndex;
	SizeType mySize;

	eOverflowBehaviour myOverflowBehaviour;
	T myData[aCapacity];
};

template<typename T, SizeType aCapacity>
HD_CircularArray<T, aCapacity>::HD_CircularArray()
	: myFirstIndex(0)
	, myWriteIndex(0)
	, mySize(0)
	, myOverflowBehaviour(eOverflowBehaviour_Enable)
	, myData()
{
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::PushBack(const T& aItem)
{
	EmplaceBack(aItem);
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::PushBack(T&& aItem)
{
	EmplaceBack(HD_Move(aItem));
}

template<typename T, SizeType aCapacity>
template<typename... Args>
void HD_CircularArray<T, aCapacity>::EmplaceBack(Args&&... args)
{
	assert(myOverflowBehaviour != eOverflowBehaviour_Disable || mySize + 1 <= aCapacity);

	new (myData + myWriteIndex) T(HD_Forward<Args>(args)...);

	if (myWriteIndex == myFirstIndex && mySize > 0)
	{
		myWriteIndex = (myWriteIndex + 1) % aCapacity;
		myFirstIndex = (myFirstIndex + 1) % aCapacity;
	}
	else
	{
		myWriteIndex = (myWriteIndex + 1) % aCapacity;
		++mySize;
	}
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::GetFirstAndRemove(T& outItem)
{
	assert(!GetIsEmpty());

	outItem = myData[myFirstIndex];
	myFirstIndex = (myFirstIndex + 1) % aCapacity;
	mySize--;
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::Clear()
{
	myFirstIndex = 0;
	myWriteIndex = 0;
	mySize = 0;
}

template<typename T, SizeType aCapacity>
SizeType HD_CircularArray<T, aCapacity>::GetSize() const
{
	return mySize;
}

template<typename T, SizeType aCapacity>
SizeType HD_CircularArray<T, aCapacity>::GetCapacity() const
{
	return aCapacity;
}

template<typename T, SizeType aCapacity>
bool HD_CircularArray<T, aCapacity>::GetIsEmpty() const
{
	return mySize == 0;
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::EnableOverflow()
{
	myOverflowBehaviour = eOverflowBehaviour_Enable;
}

template<typename T, SizeType aCapacity>
void HD_CircularArray<T, aCapacity>::DisableOverflow()
{
	myOverflowBehaviour = eOverflowBehaviour_Disable;
}

template<typename T, SizeType aCapacity>
T& HD_CircularArray<T, aCapacity>::operator[](u32 aIndex)
{
	assert(aIndex < GetSize());

	return myData[(myFirstIndex + aIndex) % aCapacity];
}

template<typename T, SizeType aCapacity>
const T& HD_CircularArray<T, aCapacity>::operator[](u32 aIndex) const
{
	assert(aIndex < GetSize());

	return myData[(myFirstIndex + aIndex) % aCapacity];
}
