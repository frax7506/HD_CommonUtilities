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

template<typename K, typename V>
class HD_HashMap
{
public:
	HD_HashMap();
	~HD_HashMap();

	const V* GetIfExists(const K& aKey) const;
	V& operator[](const K& aKey);

	void Remove(const K& aKey);

private:
	typedef char ControlByte_t;

	enum ControlByte : ControlByte_t
	{
		ControlByte_Empty = 0b00000000,
		ControlByte_Deleted = 0b01111111,
		// ControlByte_Full	= 0b1xxxxxxx
	};

	void Rehash();

	int FindSlotIndex(const K& aKey) const;

	size_t GetLevel1Hash(size_t aHash) const { return aHash >> 7; }
	ControlByte_t GetLevel2Hash(size_t aHash) const { return aHash & 0x7F; }

	static constexpr float ourMaximumLoadFactor = 0.5f;
	static constexpr float ourGrowFactor = 2.f;

	char* myData;
	HD_Pair<size_t, V>* myValues;
	int mySize;
	int myCapacity;
};

template<typename K, typename V>
HD_HashMap<K, V>::HD_HashMap()
	: mySize(0)
	, myCapacity(16)
{
	myData = new char[myCapacity + sizeof(HD_Pair<size_t, V>) * myCapacity] { 0 };
	myValues = myData + myCapacity;
}

template<typename K, typename V>
HD_HashMap<K, V>::~HD_HashMap()
{
	HD_SafeDeleteArray(myData);
}

template<typename K, typename V>
const V* HD_HashMap<K, V>::GetIfExists(const K& aKey) const
{
	aKey;
}

template<typename K, typename V>
V& HD_HashMap<K, V>::operator[](const K& aKey)
{
	size_t hashCode = HD_Hash(aKey);
	hashCode;
}

template<typename K, typename V>
void HD_HashMap<K, V>::Remove(const K& aKey)
{
	aKey;
}

template<typename K, typename V>
void HD_HashMap<K, V>::Rehash()
{

}

template<typename K, typename V>
int HD_HashMap<K, V>::FindSlotIndex(const K& aKey) const
{
	size_t hashCode = HD_Hash(aKey);
	int index = GetLevel1Hash(hashCode) % myCapacity;

	while (true)
	{
		bool isSlotEmpty = myData[index] == ControlByte_Empty;
		bool isLevel2HashSame = myData[index] == GetLevel2Hash(hashCode);

		if (isSlotEmpty || (isLevel2HashSame && myValues[index].myFirst == hashCode)
		{
			return index;
		}

		index++;
	}
}
