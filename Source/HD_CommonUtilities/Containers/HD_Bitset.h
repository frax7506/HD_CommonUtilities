#pragma once

#include "HD_Math.h"
#include "HD_String.h"
#include "HD_Types.h"

#include <cassert>
#include <cstring>

template<u32 aNrOfBits>
class HD_Bitset
{
public:
	template<typename BitsetType>
	class BitRef
	{
	public:
		BitRef();
		BitRef(const BitRef& aOther);
		BitRef(BitsetType* aBitset, u32 aIndex);

		BitRef& operator=(const BitRef& aOther);
		BitRef& operator=(bool aValue);

		bool GetValue() const;
		operator bool() const;

	private:
		BitsetType* myBitset;
		u32 myBitIndex;
	};

	typedef BitRef<HD_Bitset> BitReference;
	typedef BitRef<const HD_Bitset> ConstBitReference;

public:
	static constexpr u32 GetNrOfBytesNeededForNrOfBits(u32 aNrOfBits) { return (aNrOfBits % 8) == 0 ? (aNrOfBits / 8) : (aNrOfBits / 8) + 1; }
	static constexpr u32 ourNrOfBytes = GetNrOfBytesNeededForNrOfBits(aNrOfBits);

	HD_Bitset();
	HD_Bitset(const HD_Bitset& aOther);
	HD_Bitset(u64 aMask);

	void EnableAllBits();
	void DisableAllBits();
	void FlipAllBits();

	u8* GetBuffer();
	const u8* GetBuffer() const;

	const char* ToString() const;

	BitReference operator[](u32 aIndex);
	ConstBitReference operator[](u32 aIndex) const;

	ConstBitReference GetIsFlagEnabled(u64 aFlag) const;

	HD_Bitset& operator&=(const HD_Bitset& aOther);
	HD_Bitset& operator|=(const HD_Bitset& aOther);
	HD_Bitset& operator^=(const HD_Bitset& aOther);

	HD_Bitset& operator<<=(u32 aValue);
	HD_Bitset& operator>>=(u32 aValue);

	HD_Bitset operator~() const;
	HD_Bitset operator<<(u32 aValue) const;
	HD_Bitset operator>>(u32 aValue) const;

private:
	u8 myBytes[ourNrOfBytes];
};

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>::HD_Bitset()
{
	memset(&myBytes, 0, ourNrOfBytes);
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>::HD_Bitset(const HD_Bitset& aOther)
{
	memcpy(&myBytes, &aOther.myBytes, ourNrOfBytes);
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>::HD_Bitset(u64 aMask)
{
	u32 indexOfHighestBit = static_cast<u32>(HD_Log2(static_cast<f64>(aMask)));
	assert(indexOfHighestBit <= (aNrOfBits - 1));
	u32 nrOfBytesToCopy = GetNrOfBytesNeededForNrOfBits(indexOfHighestBit + 1);

	memset(&myBytes, 0, ourNrOfBytes);
	memcpy(&myBytes, &aMask, nrOfBytesToCopy);
}

template<u32 aNrOfBits>
void HD_Bitset<aNrOfBits>::EnableAllBits()
{
	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		myBytes[byteIndex] = static_cast<u8>(0xFF);
	}
}

template<u32 aNrOfBits>
void HD_Bitset<aNrOfBits>::DisableAllBits()
{
	memset(myBytes, 0, ourNrOfBytes);
}

template<u32 aNrOfBits>
void HD_Bitset<aNrOfBits>::FlipAllBits()
{
	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		myBytes[byteIndex] = ~myBytes[byteIndex];
	}
}

template<u32 aNrOfBits>
u8* HD_Bitset<aNrOfBits>::GetBuffer()
{
	return myBytes;
}

template<u32 aNrOfBits>
const u8* HD_Bitset<aNrOfBits>::GetBuffer() const
{
	return myBytes;
}

template<u32 aNrOfBits>
const char* HD_Bitset<aNrOfBits>::ToString() const
{
	HD_String string;
	for (s32 bitIndex = (ourNrOfBytes * 8) - 1; bitIndex >= 0; bitIndex--)
	{
		if ((*this)[bitIndex])
		{
			string.Append("1");
		}
		else
		{
			string.Append("0");
		}
	}

	return string.GetBuffer();
}

template<u32 aNrOfBits>
typename HD_Bitset<aNrOfBits>::BitReference HD_Bitset<aNrOfBits>::operator[](u32 aIndex)
{
	BitReference bitReference(this, aIndex);
	return bitReference;
}

template<u32 aNrOfBits>
typename HD_Bitset<aNrOfBits>::ConstBitReference HD_Bitset<aNrOfBits>::operator[](u32 aIndex) const
{
	ConstBitReference constBitReference(this, aIndex);
	return constBitReference;
}

template<u32 aNrOfBits>
typename HD_Bitset<aNrOfBits>::ConstBitReference HD_Bitset<aNrOfBits>::GetIsFlagEnabled(u64 aFlag) const
{
	u32 index = static_cast<u32>(HD_Log2(static_cast<f64>(aFlag)));
	return (*this)[index];
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>& HD_Bitset<aNrOfBits>::operator&=(const HD_Bitset& aOther)
{
	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		myBytes[byteIndex] &= aOther.myBytes[byteIndex];
	}

	return *this;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>& HD_Bitset<aNrOfBits>::operator|=(const HD_Bitset& aOther)
{
	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		myBytes[byteIndex] |= aOther.myBytes[byteIndex];
	}

	return *this;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>& HD_Bitset<aNrOfBits>::operator^=(const HD_Bitset& aOther)
{
	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		myBytes[byteIndex] ^= aOther.myBytes[byteIndex];
	}

	return *this;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>& HD_Bitset<aNrOfBits>::operator<<=(u32 aValue)
{
	for (s32 bitIndex = (ourNrOfBytes * 8) - 1; bitIndex >= 0; bitIndex--)
	{
		BitReference bitReferenceCurrent(this, bitIndex);

		if (bitIndex - static_cast<s32>(aValue) >= 0)
		{
			BitReference bitReferenceBitshift(this, bitIndex - aValue);
			bitReferenceCurrent = bitReferenceBitshift.GetValue();
		}
		else
		{
			bitReferenceCurrent = false;
		}
	}

	return *this;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits>& HD_Bitset<aNrOfBits>::operator>>=(u32 aValue)
{
	for (u32 bitIndex = 0; bitIndex < ourNrOfBytes * 8; bitIndex++)
	{
		BitReference bitReferenceCurrent(this, bitIndex);

		if (bitIndex + aValue < (ourNrOfBytes * 8))
		{
			BitReference bitReferenceBitshift(this, bitIndex + aValue);
			bitReferenceCurrent = bitReferenceBitshift.GetValue();
		}
		else
		{
			bitReferenceCurrent = false;
		}
	}

	return *this;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits> HD_Bitset<aNrOfBits>::operator~() const
{
	HD_Bitset result;

	for (u32 byteIndex = 0; byteIndex < ourNrOfBytes; byteIndex++)
	{
		result.myBytes[byteIndex] = ~myBytes[byteIndex];
	}

	return result;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits> HD_Bitset<aNrOfBits>::operator<<(u32 aValue) const
{
	HD_Bitset result = (*this);
	result <<= aValue;
	return result;
}

template<u32 aNrOfBits>
HD_Bitset<aNrOfBits> HD_Bitset<aNrOfBits>::operator>>(u32 aValue) const
{
	HD_Bitset result = (*this);
	result >>= aValue;
	return result;
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>::BitRef()
	: myBitset(nullptr)
	, myBitIndex(0)
{
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>::BitRef(const BitRef& aOther)
	: myBitset(aOther.myBitset)
	, myBitIndex(aOther.myBitIndex)
{
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>::BitRef(BitsetType* aBitset, u32 aIndex)
	: myBitset(aBitset)
	, myBitIndex(aIndex)
{
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>& HD_Bitset<aNrOfBits>::BitRef<BitsetType>::operator=(const BitRef& aOther)
{
	myBitset = aOther.myBitset;
	myBitIndex = aOther.myBitIndex;

	return *this;
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>& HD_Bitset<aNrOfBits>::BitRef<BitsetType>::operator=(bool aValue)
{
	u32 byteIndex = myBitIndex / 8;
	u32 bitIndexInByte = myBitIndex % 8;
	u8 flag = static_cast<u8>(HD_Pow(2.f, static_cast<f32>(bitIndexInByte)));

	if (aValue)
	{
		myBitset->myBytes[byteIndex] |= flag;
	}
	else
	{
		myBitset->myBytes[byteIndex] &= ~flag;
	}

	return *this;
}

template<u32 aNrOfBits>
template<typename BitsetType>
bool HD_Bitset<aNrOfBits>::BitRef<BitsetType>::GetValue() const
{
	u32 byteIndex = myBitIndex / 8;
	u32 bitIndexInByte = myBitIndex % 8;
	u8 flag = static_cast<u8>(HD_Pow(2.f, static_cast<f32>(bitIndexInByte)));

	bool result = (myBitset->myBytes[byteIndex] & flag) != 0;
	return result;
}

template<u32 aNrOfBits>
template<typename BitsetType>
HD_Bitset<aNrOfBits>::BitRef<BitsetType>::operator bool() const
{
	bool value = GetValue();
	return value;
}
