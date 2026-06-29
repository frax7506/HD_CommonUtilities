#pragma once

#include "HD_Math.h"

#include <cassert>
#include <cstring>

template<int aSize>
class HD_Bitset
{
public:
	// A proxy class that is used to access a single bit
	class Reference
	{
	public:
		Reference(HD_Bitset* aBitset, int aIndex);

		Reference& operator=(const Reference& aOther);
		Reference& operator=(bool aValue);

		operator bool() const;

	private:
		HD_Bitset<aSize>* myBitset;
		int myIndex;
	};

public:
	HD_Bitset();
	HD_Bitset(const HD_Bitset& aOther);
	HD_Bitset(unsigned long long aValue);

	Reference& operator[](int aIndex);

	HD_Bitset& operator&=(const HD_Bitset& aOther);
	HD_Bitset& operator|=(const HD_Bitset& aOther);
	HD_Bitset& operator^=(const HD_Bitset& aOther);

	HD_Bitset& operator<<=(int aValue);
	HD_Bitset& operator>>=(int aValue);

	HD_Bitset operator~() const;
	HD_Bitset operator<<(int aValue) const;
	HD_Bitset operator>>(int aValue) const;

private:
	static constexpr int GetNrOfBytesNeededForNrOfBits(int aNrOfBits) { return (aNrOfBits % 8) == 0 ? (aNrOfBits / 8) : (aNrOfBits / 8) + 1; }
	static constexpr int ourNrOfBytes = GetNrOfBytesNeededForNrOfBits(aSize);

	char myBits[ourNrOfBytes];
};

template<int aSize>
HD_Bitset<aSize>::HD_Bitset()
{
	memset(&myBits, 0, ourNrOfBytes);
}

template<int aSize>
HD_Bitset<aSize>::HD_Bitset(const HD_Bitset& aOther)
{
	memcpy(&myBits, &aOther.myBits, ourNrOfBytes);
}

template<int aSize>
HD_Bitset<aSize>::HD_Bitset(unsigned long long aValue)
{
	int indexOfHighestBit = static_cast<int>(HD_Log2(static_cast<long double>(aValue)));
	assert(indexOfHighestBit <= (aSize - 1));
	int nrOfBytesToCopy = GetNrOfBytesNeededForNrOfBits(indexOfHighestBit + 1);

	memset(&myBits, 0, ourNrOfBytes);
	memcpy(&myBits, &aValue, nrOfBytesToCopy);
}

template<int aSize>
typename HD_Bitset<aSize>::Reference& HD_Bitset<aSize>::operator[](int aIndex)
{
	Reference reference(this, aIndex);
	return reference;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator&=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] &= aOther.myBits[i];
	}
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator|=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] |= aOther.myBits[i];
	}
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator^=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] ^= aOther.myBits[i];
	}
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator<<=(int aValue)
{
	for (int bitIndex = (ourNrOfBytes * 4) - 1; bitIndex >= 0; bitIndex--)
	{
		Reference referenceCurrent(this, bitIndex);

		if (bitIndex - aValue >= 0)
		{
			Reference referenceBitshift(this, bitIndex - aValue);
			referenceCurrent = referenceBitshift;
		}
		else
		{
			referenceCurrent = false;
		}
	}
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator>>=(int aValue)
{
	for (int bitIndex = 0; bitIndex < ourNrOfBytes * 4; bitIndex++)
	{
		Reference referenceCurrent(this, bitIndex);

		if (bitIndex + aValue < (ourNrOfBytes * 4))
		{
			Reference referenceBitshift(this, bitIndex + aValue);
			referenceCurrent = referenceBitshift;
		}
		else
		{
			referenceCurrent = false;
		}
	}
}

template<int aSize>
HD_Bitset<aSize> HD_Bitset<aSize>::operator~() const
{
	HD_Bitset result;

	for (int i = 0; i < ourNrOfBytes; i++)
	{
		result.myBits[i] = ~myBits[i];
	}

	return result;
}

template<int aSize>
HD_Bitset<aSize> HD_Bitset<aSize>::operator<<(int aValue) const
{
	HD_Bitset result = (*this);
	result <<= aValue;
	return result;
}

template<int aSize>
HD_Bitset<aSize> HD_Bitset<aSize>::operator>>(int aValue) const
{
	HD_Bitset result = (*this);
	result >>= aValue;
	return result;
}

template<int aSize>
HD_Bitset<aSize>::Reference::Reference(HD_Bitset* aBitset, int aIndex)
	: myBitset(aBitset)
	, myIndex(aIndex)
{
}

template<int aSize>
typename HD_Bitset<aSize>::Reference& HD_Bitset<aSize>::Reference::operator=(const Reference& aOther)
{
	int byteIndexOther = aOther.myIndex / 8;
	int bitIndexInByteOther = aOther.myIndex % 8;
	char maskOther = static_cast<char>(HD_Pow(2, bitIndexInByteOther));

	bool value = (aOther.myBitset->myBits[byteIndexOther] & maskOther) != 0;
	(*this) = value;
}

template<int aSize>
typename HD_Bitset<aSize>::Reference& HD_Bitset<aSize>::Reference::operator=(bool aValue)
{
	int byteIndex = myIndex / 8;
	int bitIndexInByte = myIndex % 8;
	char mask = static_cast<char>(HD_Pow(2, bitIndexInByte));

	if (aValue)
	{
		myBitset->myBits[byteIndex] |= mask;
	}
	else
	{
		myBitset->myBits[byteIndex] &= ~mask;
	}
}

template<int aSize>
HD_Bitset<aSize>::Reference::operator bool() const
{
	int byteIndex = myIndex / 8;
	int bitIndexInByte = myIndex % 8;
	char mask = static_cast<char>(HD_Pow(2, bitIndexInByte));

	bool result = (myBitset->myBits[byteIndex] & mask) != 0;
	return result;
}
