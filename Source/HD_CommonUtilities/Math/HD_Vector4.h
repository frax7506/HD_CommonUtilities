#pragma once

#include "HD_Types.h"

template<typename T>
class HD_Matrix4x4;

template<typename T>
class HD_Vector4
{
public:
	HD_Vector4();
	HD_Vector4(T aX, T aY, T aZ, T aW);
	HD_Vector4(const HD_Vector4& aOther);

	void Set(T aX, T aY, T aZ, T aW);

	T GetLength() const;
	T GetLength2() const;

	void SetLength(T aLength);
	void Limit(T aLength);

	void Normalize();
	HD_Vector4 GetNormalized() const;

	HD_Vector4& operator=(const HD_Vector4& aOther);
	HD_Vector4& operator+=(const HD_Vector4& aOther);
	HD_Vector4& operator-=(const HD_Vector4& aOther);
	HD_Vector4& operator*=(const HD_Matrix4x4<T>& aMatrix);
	HD_Vector4& operator*=(T aScalar);
	HD_Vector4& operator/=(T aScalar);

	T myX, myY, myZ, myW;

public:
	typedef T DataType;

	static T Length(const HD_Vector4& aStart, const HD_Vector4& aEnd);
	static T Length2(const HD_Vector4& aStart, const HD_Vector4& aEnd);
};

template<typename T> HD_Vector4<T> operator+(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1);
template<typename T> HD_Vector4<T> operator-(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1);
template<typename T> HD_Vector4<T> operator*(const HD_Vector4<T>& aVector, T aScalar);
template<typename T> HD_Vector4<T> operator*(T aScalar, const HD_Vector4<T>& aVector);
template<typename T> HD_Vector4<T> operator/(const HD_Vector4<T>& aVector, T aScalar);
template<typename T> bool operator==(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1);
template<typename T> bool operator!=(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1);

template<typename T>
HD_Vector4<T>::HD_Vector4()
	: myX()
	, myY()
	, myZ()
	, myW()
{
}

template<typename T>
HD_Vector4<T>::HD_Vector4(T aX, T aY, T aZ, T aW)
	: myX(aX)
	, myY(aY)
	, myZ(aZ)
	, myW(aW)
{
}

template<typename T>
HD_Vector4<T>::HD_Vector4(const HD_Vector4& aOther)
	: myX(aOther.myX)
	, myY(aOther.myY)
	, myZ(aOther.myZ)
	, myW(aOther.myW)
{
}

template<typename T>
void HD_Vector4<T>::Set(T aX, T aY, T aZ, T aW)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
	myW = aW;
}

template<typename T>
T HD_Vector4<T>::GetLength() const
{
	return HD_Sqrt(myX * myX + myY * myY + myZ * myZ + myW * myW);
}

template<typename T>
T HD_Vector4<T>::GetLength2() const
{
	return myX * myX + myY * myY + myZ * myZ + myW * myW;
}

template<typename T>
void HD_Vector4<T>::SetLength(T aLength)
{
	Normalize();
	(*this) *= aLength;
}

template<typename T>
void HD_Vector4<T>::Limit(T aLength)
{
	T length2 = GetLength2();
	if (length2 > aLength * aLength)
	{
		SetLength(aLength);
	}
}

template<typename T>
void HD_Vector4<T>::Normalize()
{
	// Note: will not compile if used on non-floating point types
	// with warning level 4 and warnings treated as errors due to
	// data loss in the float -> non-float conversion. But normalizing
	// a non-floating point type vector should be unusual anyway,
	// since in those cases the vector is used more like a container
	// than a mathematical vector.

	T length = GetLength();
	(*this) /= length;
}

template<typename T>
HD_Vector4<T> HD_Vector4<T>::GetNormalized() const
{
	// Note: same note as Normalize.

	HD_Vector4<T> temp(*this);
	temp.Normalize();
	return temp;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator=(const HD_Vector4<T>& aOther)
{
	myX = aOther.myX;
	myY = aOther.myY;
	myZ = aOther.myZ;
	myW = aOther.myW;

	return *this;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator+=(const HD_Vector4<T>& aOther)
{
	myX += aOther.myX;
	myY += aOther.myY;
	myZ += aOther.myZ;
	myW += aOther.myW;

	return *this;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator-=(const HD_Vector4<T>& aOther)
{
	myX -= aOther.myX;
	myY -= aOther.myY;
	myZ -= aOther.myZ;
	myW -= aOther.myW;

	return *this;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator*=(const HD_Matrix4x4<T>& aMatrix)
{
	(*this) = (*this) * aMatrix;
	return *this;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator*=(T aScalar)
{
	myX *= aScalar;
	myY *= aScalar;
	myZ *= aScalar;
	myW *= aScalar;

	return *this;
}

template<typename T>
HD_Vector4<T>& HD_Vector4<T>::operator/=(T aScalar)
{
	myX /= aScalar;
	myY /= aScalar;
	myZ /= aScalar;
	myW /= aScalar;

	return *this;
}

template<typename T>
T HD_Vector4<T>::Length(const HD_Vector4& aStart, const HD_Vector4& aEnd)
{
	HD_Vector4 startToEnd = aEnd - aStart;
	return startToEnd.GetLength();
}

template<typename T>
T HD_Vector4<T>::Length2(const HD_Vector4& aStart, const HD_Vector4& aEnd)
{
	HD_Vector4 startToEnd = aEnd - aStart;
	return startToEnd.GetLength2();
}

template<typename T>
HD_Vector4<T> operator+(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1)
{
	return { aVector0.myX + aVector1.myX, aVector0.myY + aVector1.myY, aVector0.myZ + aVector1.myZ, aVector0.myW + aVector1.myW };
}

template<typename T>
HD_Vector4<T> operator-(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1)
{
	return { aVector0.myX - aVector1.myX, aVector0.myY - aVector1.myY, aVector0.myZ - aVector1.myZ, aVector0.myW - aVector1.myW };
}

template<typename T>
HD_Vector4<T> operator*(const HD_Vector4<T>& aVector, T aScalar)
{
	return { aVector.myX * aScalar, aVector.myY * aScalar, aVector.myZ * aScalar, aVector.myW * aScalar };
}

template<typename T>
HD_Vector4<T> operator*(T aScalar, const HD_Vector4<T>& aVector)
{
	return aVector * aScalar;
}

template<typename T>
HD_Vector4<T> operator/(const HD_Vector4<T>& aVector, T aScalar)
{
	return { aVector.myX / aScalar, aVector.myY / aScalar, aVector.myZ / aScalar, aVector.myW / aScalar };
}

template<typename T>
bool operator==(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1)
{
	return aVector0.myX == aVector1.myX && aVector0.myY == aVector1.myY && aVector0.myZ == aVector1.myZ && aVector0.myW == aVector1.myW;
}

template<typename T>
bool operator!=(const HD_Vector4<T>& aVector0, const HD_Vector4<T>& aVector1)
{
	return !(aVector0 == aVector1);
}

typedef HD_Vector4<f32> HD_Vector4_f32;
typedef HD_Vector4<f64> HD_Vector4_f64;
typedef HD_Vector4<s32> HD_Vector4_s32;
typedef HD_Vector4<u32> HD_Vector4_u32;
