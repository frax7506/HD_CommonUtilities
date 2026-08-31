#pragma once

// See notes of HD_HashMap
	// * This class is heavily based on that one, but storing values
	//		instead of key value paris.

// Future work
	// * The most important future work is to see if this and HD_HashMap
	//		somehow can make use of some shared code. Lots of code is
	//		the same or very similar.

#include "HD_Hash.h"
#include "HD_HashArrayIterator.h"
#include "HD_Move.h"
#include "HD_SafeDelete.h"
#include "HD_Types.h"

template<typename V>
class HD_HashSet
{
public:
	typedef HD_HashArrayIterator<V> Iterator;
	typedef HD_HashArrayIterator<const V> ConstIterator;
	friend class Iterator;
	friend class ConstIterator;

	HD_HashSet();
	HD_HashSet(SizeType aCapacity);
	HD_HashSet(const HD_HashSet& aHashSet);
	HD_HashSet(HD_HashSet&& aHashSet);
	~HD_HashSet();

	HD_HashSet& operator=(const HD_HashSet& aHashSet);
	HD_HashSet& operator=(HD_HashSet&& aHashSet);

	const V* GetIfExists(const V& aValue) const;

	void Insert(const V& aValue);
	void Remove(const V& aValue);

	void Clear();

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	enum eControlByte : ControlByte_Type
	{
		eControlByte_Empty = 0b00000000,
		eControlByte_Deleted = 0b01111111,
		// ControlByte_Full = 0b1xxxxxxx
	};

	static constexpr f32 ourMaximumLoadFactor = 0.5f;
	static constexpr f32 ourGrowFactor = 2.f;

	void InitWithCapacity(SizeType aCapacity);

	void InsertValueAtIndex(const V& aValue, u32 aIndex);

	void Rehash();

	// Finds the index where an element is, or would be.
	u32 GetSlotIndexForValue(const V& aValue) const;

	u32 GetFirstSlotIndex() const;

	bool GetIsSlotFullAtIndex(u32 aIndex) const;

	u64 GetLevel1Hash(u64 aHash) const { return aHash >> 7; }
	ControlByte_Type GetLevel2Hash(u64 aHash) const { return aHash & 0x7F; }

	u8* myData;
	ControlByte_Type* myControlBytes;
	V* myValues;
	SizeType mySizeIncludingTombstones;
	SizeType myCapacity;
};

template<typename V>
HD_HashSet<V>::HD_HashSet()
	: myData(nullptr)
	, myControlBytes(nullptr)
	, myValues(nullptr)
	, mySizeIncludingTombstones(0)
	, myCapacity(0)
{
}

template<typename V>
HD_HashSet<V>::HD_HashSet(SizeType aCapacity)
	: myData(nullptr)
	, myControlBytes(nullptr)
	, myValues(nullptr)
	, mySizeIncludingTombstones(0)
	, myCapacity(0)
{
	InitWithCapacity(aCapacity);
}

template<typename V>
HD_HashSet<V>::HD_HashSet(const HD_HashSet& aHashSet)
	: myData(nullptr)
	, myControlBytes(nullptr)
	, myValues(nullptr)
	, mySizeIncludingTombstones(0)
	, myCapacity(0)
{
	InitWithCapacity(aHashSet.myCapacity);

	for (auto it = aHashSet.begin(); it != aHashSet.end(); it++)
	{
		const V& value = *it;

		u32 index = GetSlotIndexForValue(value);
		InsertValueAtIndex(value, index);
		mySizeIncludingTombstones++;
	}
}

template<typename V>
HD_HashSet<V>::HD_HashSet(HD_HashSet&& aHashSet)
	: myData(nullptr)
	, myControlBytes(nullptr)
	, myValues(nullptr)
	, mySizeIncludingTombstones(aHashSet.mySizeIncludingTombstones)
	, myCapacity(aHashSet.myCapacity)
{
	myData = aHashSet.myData;
	myControlBytes = myData;
	myValues = reinterpret_cast<V*>(myControlBytes + myCapacity);

	aHashSet.myData = nullptr;
	aHashSet.myControlBytes = nullptr;
	aHashSet.myValues = nullptr;
	aHashSet.mySizeIncludingTombstones = 0;
	aHashSet.myCapacity = 0;
}

template<typename V>
HD_HashSet<V>::~HD_HashSet()
{
	HD_SafeDeleteArray(myData);
}

template<typename V>
HD_HashSet<V>& HD_HashSet<V>::operator=(const HD_HashSet& aHashSet)
{
	if (myCapacity > 0)
	{
		Clear();
	}

	bool isCapacitySmaller = myCapacity < aHashSet.myCapacity;

	if (isCapacitySmaller)
	{
		HD_SafeDeleteArray(myData);
		InitWithCapacity(aHashSet.myCapacity);
	}

	for (auto it = aHashSet.begin(); it != aHashSet.end(); it++)
	{
		const V& value = *it;

		u32 index = GetSlotIndexForValue(value);
		InsertValueAtIndex(value, index);
		mySizeIncludingTombstones++;
	}

	return *this;
}

template<typename V>
HD_HashSet<V>& HD_HashSet<V>::operator=(HD_HashSet&& aHashSet)
{
	myData = aHashSet.myData;
	myControlBytes = aHashSet.myData;
	myValues = reinterpret_cast<V*>(aHashSet.myControlBytes + aHashSet.myCapacity);
	mySizeIncludingTombstones = aHashSet.mySizeIncludingTombstones;
	myCapacity = aHashSet.myCapacity;

	aHashSet.myData = nullptr;
	aHashSet.myControlBytes = nullptr;
	aHashSet.myValues = nullptr;
	aHashSet.mySizeIncludingTombstones = 0;
	aHashSet.myCapacity = 0;

	return *this;
}

template<typename V>
const V* HD_HashSet<V>::GetIfExists(const V& aValue) const
{
	if (myCapacity == 0)
	{
		return nullptr;
	}

	u32 index = GetSlotIndexForValue(aValue);
	bool isFull = GetIsSlotFullAtIndex(index);

	if (isFull)
	{
		return &myValues[index];
	}

	return nullptr;
}

template<typename V>
void HD_HashSet<V>::Insert(const V& aValue)
{
	if (myCapacity == 0)
	{
		InitWithCapacity(16);
	}

	u32 index = GetSlotIndexForValue(aValue);
	bool isFull = GetIsSlotFullAtIndex(index);

	if (isFull)
	{
		return;
	}

	f32 newLoadFactor = static_cast<f32>(mySizeIncludingTombstones + 1) / myCapacity;
	if (newLoadFactor > ourMaximumLoadFactor)
	{
		Rehash();
		index = GetSlotIndexForValue(aValue);
	}

	if (myControlBytes[index] == eControlByte_Empty)
	{
		mySizeIncludingTombstones++;
	}

	InsertValueAtIndex(aValue, index);
}

template<typename V>
void HD_HashSet<V>::Remove(const V& aValue)
{
	if (myCapacity == 0)
	{
		return;
	}

	u32 index = GetSlotIndexForValue(aValue);
	bool isFull = GetIsSlotFullAtIndex(index);

	if (isFull)
	{
		myControlBytes[index] = eControlByte_Deleted;
	}
}

template<typename V>
void HD_HashSet<V>::Clear()
{
	memset(myControlBytes, 0, myCapacity * sizeof(ControlByte_Type));
	mySizeIncludingTombstones = 0;
}

template<typename V>
typename HD_HashSet<V>::Iterator HD_HashSet<V>::begin()
{
	u32 firstIndex = GetFirstSlotIndex();
	return Iterator(myControlBytes, myValues, firstIndex, myCapacity);
}

template<typename V>
typename HD_HashSet<V>::Iterator HD_HashSet<V>::end()
{
	return Iterator(myControlBytes, myValues, myCapacity, myCapacity);
}

template<typename V>
typename HD_HashSet<V>::ConstIterator HD_HashSet<V>::begin() const
{
	u32 firstIndex = GetFirstSlotIndex();
	return ConstIterator(myControlBytes, myValues, firstIndex, myCapacity);
}

template<typename V>
typename HD_HashSet<V>::ConstIterator HD_HashSet<V>::end() const
{
	return ConstIterator(myControlBytes, myValues, myCapacity, myCapacity);
}

template<typename V>
void HD_HashSet<V>::InitWithCapacity(SizeType aCapacity)
{
	myCapacity = aCapacity;
	mySizeIncludingTombstones = 0;

	myData = new u8[myCapacity + myCapacity * sizeof(V)]{ 0 };
	myControlBytes = myData;
	myValues = reinterpret_cast<V*>(myControlBytes + myCapacity);
}

template<typename V>
void HD_HashSet<V>::InsertValueAtIndex(const V& aValue, u32 aIndex)
{
	u64 hashCode = HD_Hash(aValue);
	myControlBytes[aIndex] = GetLevel2Hash(hashCode) | 0b10000000;
	myValues[aIndex] = aValue;
}

template<typename V>
void HD_HashSet<V>::Rehash()
{
	SizeType newCapacity = static_cast<SizeType>(myCapacity * ourGrowFactor);

	HD_HashSet temp = HD_Move(*this);
	InitWithCapacity(newCapacity);
	(*this) = temp;
}

template<typename V>
u32 HD_HashSet<V>::GetSlotIndexForValue(const V& aValue) const
{
	u64 hashCode = HD_Hash(aValue);
	u32 index = GetLevel1Hash(hashCode) % myCapacity;

	while (true)
	{
		bool isSlotEmpty = myControlBytes[index] == eControlByte_Empty;
		bool isLevel2HashSame = GetLevel2Hash(myControlBytes[index]) == GetLevel2Hash(hashCode);

		if (isSlotEmpty || (isLevel2HashSame && myValues[index] == aValue))
		{
			return index;
		}

		index++;
	}
}

template<typename V>
u32 HD_HashSet<V>::GetFirstSlotIndex() const
{
	for (u32 i = 0; i < myCapacity; i++)
	{
		if (GetIsSlotFullAtIndex(i))
		{
			return i;
		}
	}

	assert(false && "GetFirstSlotIndex was called on a full HD_HashSet. This should not happen. The map should rehash before it's full.");
	return 0;
}

template<typename V>
bool HD_HashSet<V>::GetIsSlotFullAtIndex(u32 aIndex) const
{
	return myControlBytes[aIndex] & 0b10000000;
}
