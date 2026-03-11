// WIP

#pragma once

// Inspired by Google's flat_hash_set: https://www.youtube.com/watch?v=ncHmEUmJZf4
	// * Values are stored directly in the data array, minimizing the amount of indirections.
	// * Metadata is stored at the beginning of the array (1b for each element), containing information about the slots' states.

#include "HD_Hash.h"
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
	void Rehash();

	char* myData;
	V* myValues;
	int mySize;
	int myCapacity;
};

template<typename K, typename V>
HD_HashMap<K, V>::HD_HashMap()
	: mySize(0)
	, myCapacity(16)
{
	myData = new char[myCapacity + sizeof(V) * myCapacity];
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
