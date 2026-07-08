#pragma once

#include "HD_Types.h"

#include <cassert>

template<typename T, SizeType aSize>
class HD_StaticStack
{
public:
	HD_StaticStack();

	void Push(const T& aData);
	void Pop();
	const T& Top();

	void PopN(u32 aN);
	void MoveN(HD_StaticStack& aMoveFrom, u32 aN);

	SizeType GetNrOfPushedElements();

private:
	T myData[aSize];
	SizeType myNrOfPushedElements;
};

template<typename T, SizeType aSize>
HD_StaticStack<T, aSize>::HD_StaticStack()
	: myNrOfPushedElements(0)
{
	for (u32 i = 0; i < aSize; i++)
		myData[i] = T();
}

template<typename T, SizeType aSize>
void HD_StaticStack<T, aSize>::Push(const T& aData)
{
	assert(myNrOfPushedElements < aSize);
	myData[myNrOfPushedElements] = aData;
	myNrOfPushedElements++;
}

template<typename T, SizeType aSize>
void HD_StaticStack<T, aSize>::Pop()
{
	assert(myNrOfPushedElements > 0);
	myNrOfPushedElements--;
}

template<typename T, SizeType aSize>
const T& HD_StaticStack<T, aSize>::Top()
{
	assert(myNrOfPushedElements > 0);
	return myData[myNrOfPushedElements - 1];
}

template<typename T, SizeType aSize>
void HD_StaticStack<T, aSize>::PopN(u32 aN)
{
	assert(myNrOfPushedElements >= aN);
	myNrOfPushedElements -= aN;
}

template<typename T, SizeType aSize>
void HD_StaticStack<T, aSize>::MoveN(HD_StaticStack& aMoveFrom, u32 aN)
{
	SizeType moveFromNrOfPushedElements = aMoveFrom.GetNrOfPushedElements();
	assert(myNrOfPushedElements + aN <= aSize && moveFromNrOfPushedElements >= aN);

	for (u32 i = 0; i < aN; i++)
	{
		Push(aMoveFrom.myData[moveFromNrOfPushedElements - aN + i]);
		aMoveFrom.Pop();
	}
}

template<typename T, SizeType aSize>
SizeType HD_StaticStack<T, aSize>::GetNrOfPushedElements()
{
	return myNrOfPushedElements;
}
