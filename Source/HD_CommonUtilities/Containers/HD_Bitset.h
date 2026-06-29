#pragma once

#include "HD_Math.h"

#include <cassert>
#include <cstring>

template<int aSize>
class HD_Bitset
{
public:
	class Bit
	{
	public:
		Bit();
		Bit(const Bit& aOther);
		Bit(HD_Bitset* aBitset, int aIndex);

		Bit& operator=(const Bit& aOther);
		Bit& operator=(bool aValue);

		bool GetValue() const;
		operator bool() const;

	private:
		HD_Bitset* myBitset;
		int myIndex;
	};

public:
	HD_Bitset();
	HD_Bitset(const HD_Bitset& aOther);
	HD_Bitset(unsigned long long aValue);

	void EnableAllBits();
	void DisableAllBits();
	void FlipAllBits();

	Bit operator[](int aIndex);

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
void HD_Bitset<aSize>::EnableAllBits()
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] = static_cast<char>(0xFF);
	}
}

template<int aSize>
void HD_Bitset<aSize>::DisableAllBits()
{
	memset(myBits, 0, ourNrOfBytes);
}

template<int aSize>
void HD_Bitset<aSize>::FlipAllBits()
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] = ~myBits[i];
	}
}

template<int aSize>
typename HD_Bitset<aSize>::Bit HD_Bitset<aSize>::operator[](int aIndex)
{
	Bit bit(this, aIndex);
	return bit;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator&=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] &= aOther.myBits[i];
	}

	return *this;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator|=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] |= aOther.myBits[i];
	}

	return *this;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator^=(const HD_Bitset& aOther)
{
	for (int i = 0; i < ourNrOfBytes; i++)
	{
		myBits[i] ^= aOther.myBits[i];
	}

	return *this;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator<<=(int aValue)
{
	for (int bitIndex = (ourNrOfBytes * 8) - 1; bitIndex >= 0; bitIndex--)
	{
		Bit bitCurrent(this, bitIndex);

		if (bitIndex - aValue >= 0)
		{
			Bit bitBitshift(this, bitIndex - aValue);
			bitCurrent = bitBitshift.GetValue();
		}
		else
		{
			bitCurrent = false;
		}
	}

	return *this;
}

template<int aSize>
HD_Bitset<aSize>& HD_Bitset<aSize>::operator>>=(int aValue)
{
	for (int bitIndex = 0; bitIndex < ourNrOfBytes * 8; bitIndex++)
	{
		Bit bitCurrent(this, bitIndex);

		if (bitIndex + aValue < (ourNrOfBytes * 8))
		{
			Bit bitBitshift(this, bitIndex + aValue);
			bitCurrent = bitBitshift.GetValue();
		}
		else
		{
			bitCurrent = false;
		}
	}

	return *this;
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
HD_Bitset<aSize>::Bit::Bit()
	: myBitset(nullptr)
	, myIndex(0)
{
}

template<int aSize>
HD_Bitset<aSize>::Bit::Bit(const Bit& aOther)
	: myBitset(aOther.myBitset)
	, myIndex(aOther.myIndex)
{
}

template<int aSize>
HD_Bitset<aSize>::Bit::Bit(HD_Bitset* aBitset, int aIndex)
	: myBitset(aBitset)
	, myIndex(aIndex)
{
}

template<int aSize>
typename HD_Bitset<aSize>::Bit& HD_Bitset<aSize>::Bit::operator=(const Bit& aOther)
{
	myBitset = aOther.myBitset;
	myIndex = aOther.myIndex;

	return *this;
}

template<int aSize>
typename HD_Bitset<aSize>::Bit& HD_Bitset<aSize>::Bit::operator=(bool aValue)
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

	return *this;
}

template<int aSize>
bool HD_Bitset<aSize>::Bit::GetValue() const
{
	int byteIndex = myIndex / 8;
	int bitIndexInByte = myIndex % 8;
	char mask = static_cast<char>(HD_Pow(2, bitIndexInByte));

	bool result = (myBitset->myBits[byteIndex] & mask) != 0;
	return result;
}

template<int aSize>
HD_Bitset<aSize>::Bit::operator bool() const
{
	bool value = GetValue();
	return value;
}
