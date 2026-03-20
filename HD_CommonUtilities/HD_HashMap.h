// WIP

#pragma once

// Inspired by Google's flat_hash_set: https://www.youtube.com/watch?v=ncHmEUmJZf4
	// * Uses open addressing to handle collissions. Key-values are stored directly
	//		in the data array, minimizing the amount of indirections. This table
	//		uses linear probing.
	// * Metadata is stored at the beginning of the array(1b for each element),
	//		containing information about the slots' states. This means that even
	//		though 8b keys are stored in the array, the whole array can be scanned
	//		quickly and cache-friendly using this metadata.
	// * Removing entries creates tombstones. These slots can be reused on insert,
	//		but are skipped during find. This means that removing many elements and then
	//		trying to find an element can be expensive. If this is an issue then HD_Map
	//		should be used instead, which is an AVL-tree structure.
	// * Overall this map favors speed on insert and find, at the cost of memory.

#include "HD_Hash.h"
#include "HD_Pair.h"
#include "HD_Utilities.h"

template<typename V>
using HashCodeValuePair = HD_Pair<size_t, V>;

template<typename K, typename V>
class HD_HashMap;

template<typename K, typename V>
class HD_HashMapIterator
{
public:
	HD_HashMapIterator();
	HD_HashMapIterator(HD_HashMap<K, V>* aHashMap, int aIndex);
	HD_HashMapIterator(const HD_HashMapIterator& aIterator);

	HD_HashMapIterator& operator++();
	HD_HashMapIterator& operator--();
	HD_HashMapIterator operator++(int);
	HD_HashMapIterator operator--(int);
	HD_HashMapIterator& operator+=(int aIncrement);
	HD_HashMapIterator& operator-=(int aDecrement);
	bool operator==(const HD_HashMapIterator& aIterator) const;
	bool operator!=(const HD_HashMapIterator& aIterator) const;
	HashCodeValuePair<V>& operator*() const;
	HashCodeValuePair<V>* operator->() const;

private:
	HD_HashMap<K, V>* myHashMap;
	int myIndex;
};

template<typename K, typename V>
class HD_HashMap
{
public:
	typedef HD_HashMapIterator<K, V> Iterator;
	typedef HD_HashMapIterator<K, const V> ConstIterator;
	friend class Iterator;
	friend class ConstIterator;

	HD_HashMap();
	HD_HashMap(const HD_HashMap& aHashMap);
	HD_HashMap(HD_HashMap&& aHashMap);
	~HD_HashMap();

	const V* GetIfExists(const K& aKey) const;

	V& operator[](const K& aKey);

	HD_HashMap& operator=(const HD_HashMap& aHashMap);
	HD_HashMap& operator=(HD_HashMap&& aHashMap);

	void Remove(const K& aKey);

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

private:
	typedef char ControlByte_t;

	enum ControlByte : ControlByte_t
	{
		ControlByte_Empty = 0b00000000,
		ControlByte_Deleted = 0b01111111,
		// ControlByte_Full = 0b1xxxxxxx
	};

	void InitWithCapacity(int aCapacity);

	void InsertValueAtIndex(int aIndex, const V& aValue);

	void Rehash();

	// Finds the index where an element is, or would be.
	int FindSlotIndexForHashCode(size_t aHashCode) const;

	bool GetIsValueAtIndexPresent(int aIndex) const;

	size_t GetLevel1Hash(size_t aHash) const { return aHash >> 7; }
	ControlByte_t GetLevel2Hash(size_t aHash) const { return aHash & 0x7F; }

	static constexpr float ourMaximumLoadFactor = 0.5f;
	static constexpr float ourGrowFactor = 2.f;

	char* myControlBytes;
	HashCodeValuePair<V>* myHashCodeValuePairs;
	int mySize;
	int myCapacity;
};

template<typename K, typename V>
HD_HashMap<K, V>::HD_HashMap()
	: myControlBytes(nullptr)
	, myHashCodeValuePairs(nullptr)
	, mySize(0)
	, myCapacity(0)
{
	InitWithCapacity(16);
}

template<typename K, typename V>
HD_HashMap<K, V>::HD_HashMap(const HD_HashMap& aHashMap)
	: myControlBytes(nullptr)
	, myHashCodeValuePairs(nullptr)
	, mySize(0)
	, myCapacity(0)
{
	InitWithCapacity(aHashMap.myCapacity);

	for (auto it = aHashMap.begin(); it != aHashMap.end(); it++)
	{
		size_t hashCode = it->myFirst;
		const V& value = it->mySecond;

		int index = FindSlotIndexForHashCode(hashCode);
		InsertValueAtIndex(index, value);
		mySize++;
	}
}

template<typename K, typename V>
HD_HashMap<K, V>::HD_HashMap(HD_HashMap&& aHashMap)
	: myControlBytes(nullptr)
	, myHashCodeValuePairs(nullptr)
	, mySize(0)
	, myCapacity(0)
{
	myControlBytes = aHashMap.myControlBytes;
	myHashCodeValuePairs = aHashMap.myHashCodeValuePairs;
	mySize = aHashMap.mySize;
	myCapacity = aHashMap.myCapacity;

	aHashMap.myControlBytes = nullptr;
}

template<typename K, typename V>
HD_HashMap<K, V>::~HD_HashMap()
{
	// The pointer to myControlBytes is used to allocate the whole data block.
	HD_SafeDeleteArray(myControlBytes);
}

template<typename K, typename V>
const V* HD_HashMap<K, V>::GetIfExists(const K& aKey) const
{
	int index = FindSlotIndex(aKey);
	bool isPresent = GetIsValueAtIndexPresent(index);

	if (isPresent)
	{
		return &myHashCodeValuePairs[index].mySecond;
	}

	return nullptr;
}

template<typename K, typename V>
V& HD_HashMap<K, V>::operator[](const K& aKey)
{
	size_t hashCode = HD_Hash(aKey);
	int index = FindSlotIndexForHashCode(hashCode);
	bool isPresent = GetIsValueAtIndexPresent(index);

	if (isPresent)
	{
		return myHashCodeValuePairs[index].mySecond;
	}

	float newLoadFactor = static_cast<float>(mySize + 1) / myCapacity;
	if (newLoadFactor > ourMaximumLoadFactor)
	{
		Rehash();
		index = FindSlotIndexForHashCode(hashCode);
	}

	if (myControlBytes[index] == ControlByte_Empty)
	{
		mySize++;
	}

	InsertValueAtIndex(index, V());
	return myHashCodeValuePairs[index].mySecond;
}

template<typename K, typename V>
HD_HashMap<K, V>& HD_HashMap<K, V>::operator=(const HD_HashMap& aHashMap)
{
	bool isCapacitySame = myCapacity == aHashMap.myCapacity;

	if (!isCapacitySame)
	{
		HD_SafeDeleteArray(myControlBytes);
		InitWithCapacity(aHashMap.myCapacity);
	}

	for (auto it = aHashMap.begin(); it != aHashMap.end(); it++)
	{
		size_t hashCode = it->myFirst;
		const V& value = it->mySecond;

		int index = FindSlotIndexForHashCode(hashCode);
		InsertValueAtIndex(index, value);
		mySize++;
	}

	return *this;
}

template<typename K, typename V>
HD_HashMap<K, V>& HD_HashMap<K, V>::operator=(HD_HashMap&& aHashMap)
{
	myControlBytes = aHashMap.myControlBytes;
	myHashCodeValuePairs = aHashMap.myHashCodeValuePairs;
	mySize = aHashMap.mySize;
	myCapacity = aHashMap.myCapacity;

	aHashMap.myControlBytes = nullptr;

	return *this;
}

template<typename K, typename V>
void HD_HashMap<K, V>::Remove(const K& aKey)
{
	int index = FindSlotIndex(aKey);
	bool isPresent = GetIsValueAtIndexPresent(index);

	if (isPresent)
	{
		myControlBytes[index] = ControlByte_Deleted;
	}
}

template<typename K, typename V>
typename HD_HashMap<K, V>::Iterator HD_HashMap<K, V>::begin()
{
	return Iterator(this, 0);
}

template<typename K, typename V>
typename HD_HashMap<K, V>::Iterator HD_HashMap<K, V>::end()
{
	return Iterator(this, myCapacity);
}

template<typename K, typename V>
typename HD_HashMap<K, V>::ConstIterator HD_HashMap<K, V>::begin() const
{
	return ConstIterator(this, 0);
}

template<typename K, typename V>
typename HD_HashMap<K, V>::ConstIterator HD_HashMap<K, V>::end() const
{
	return ConstIterator(this, myCapacity);
}

template<typename K, typename V>
void HD_HashMap<K, V>::InitWithCapacity(int aCapacity)
{
	myCapacity = aCapacity;
	mySize = 0;

	// The pointer to myControlBytes is used to allocate the whole data block.
	// This is mostly because we need something to point to the whole data
	// block in order to delete it properly.

	myControlBytes = new char[myCapacity + sizeof(HD_Pair<size_t, V>) * myCapacity] { 0 };
	myHashCodeValuePairs = reinterpret_cast<HashCodeValuePair<V>*>(myControlBytes + myCapacity);
}

template<typename K, typename V>
void HD_HashMap<K, V>::InsertValueAtIndex(int aIndex, const V& aValue)
{
	myControlBytes[aIndex] = GetLevel2Hash(hashCode) | 0b10000000;
	myHashCodeValuePairs[aIndex].myFirst = hashCode;
	myHashCodeValuePairs[aIndex].mySecond = aValue;
}

template<typename K, typename V>
void HD_HashMap<K, V>::Rehash()
{
	HD_HashMap temp = HD_Move(*this);
	InitWithCapacity(myCapacity * ourGrowFactor);
	(*this) = temp;
}

template<typename K, typename V>
int HD_HashMap<K, V>::FindSlotIndexForHashCode(size_t aHashCode) const
{
	int index = GetLevel1Hash(aHashCode) % myCapacity;

	while (true)
	{
		bool isSlotEmpty = myControlBytes[index] == ControlByte_Empty;
		bool isLevel2HashSame = myControlBytes[index] == GetLevel2Hash(aHashCode);

		if (isSlotEmpty || (isLevel2HashSame && myHashCodeValuePairs[index].myFirst == aHashCode))
		{
			return index;
		}

		index++;
	}
}

template<typename K, typename V>
bool HD_HashMap<K, V>::GetIsValueAtIndexPresent(int aIndex) const
{
	return myControlBytes[index] & 0b10000000;
}

template<typename K, typename V>
HD_HashMapIterator<K, V>::HD_HashMapIterator()
	: myHashMap(nullptr)
	, myIndex(0)
{
}

template<typename K, typename V>
HD_HashMapIterator<K, V>::HD_HashMapIterator(HD_HashMap<K, V>* aHashMap, int aIndex)
	: myHashMap(aHashMap)
	, myIndex(aIndex)
{
}

template<typename K, typename V>
HD_HashMapIterator<K, V>::HD_HashMapIterator(const HD_HashMapIterator& aIterator)
	: myHashMap(aIterator.myHashMap)
	, myIndex(aIterator.myIndex)
{
}

template<typename K, typename V>
HD_HashMapIterator<K, V>& HD_HashMapIterator<K, V>::operator++()
{
	do
	{
		myIndex++;
	}
	while (myIndex < myHashMap->myCapacity && !myHashMap->GetIsValueAtIndexPresent(myIndex));

	return *this;
}

template<typename K, typename V>
HD_HashMapIterator<K, V>& HD_HashMapIterator<K, V>::operator--()
{
	do
	{
		myIndex--;
	}
	while (myIndex >= 0 && !myHashMap->GetIsValueAtIndexPresent(myIndex));

	return *this;
}

template<typename K, typename V>
HD_HashMapIterator<K, V> HD_HashMapIterator<K, V>::operator++(int)
{
	HD_HashMapIterator iterator = *this;
	++(*this);
	return iterator;
}

template<typename K, typename V>
HD_HashMapIterator<K, V> HD_HashMapIterator<K, V>::operator--(int)
{
	HD_HashMapIterator iterator = *this;
	--(*this);
	return iterator;
}

template<typename K, typename V>
HD_HashMapIterator<K, V>& HD_HashMapIterator<K, V>::operator+=(int aIncrement)
{
	for (int i = 0; i < aIncrement; ++i)
		++(*this);

	return *this;
}

template<typename K, typename V>
HD_HashMapIterator<K, V>& HD_HashMapIterator<K, V>::operator-=(int aDecrement)
{
	for (int i = 0; i < aDecrement; ++i)
		--(*this);

	return *this;
}

template<typename K, typename V>
bool HD_HashMapIterator<K, V>::operator==(const HD_HashMapIterator& aIterator) const
{
	return myHashMap == aIterator.myHashMap && myIndex == aIterator.myIndex;
}

template<typename K, typename V>
bool HD_HashMapIterator<K, V>::operator!=(const HD_HashMapIterator& aIterator) const
{
	return !(*this == aIterator);
}

template<typename K, typename V>
HashCodeValuePair<V>& HD_HashMapIterator<K, V>::operator*() const
{
	return myHashMap->myHashCodeValuePairs[myIndex];
}

template<typename K, typename V>
HashCodeValuePair<V>* HD_HashMapIterator<K, V>::operator->() const
{
	return myHashMap->myHashCodeValuePairs + myIndex;
}
