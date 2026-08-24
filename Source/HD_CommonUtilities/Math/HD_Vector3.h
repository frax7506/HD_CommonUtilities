#pragma once

#include "HD_Types.h"

template<typename T>
class HD_Matrix3x3;

template<typename T>
class HD_Vector3
{
public:
	HD_Vector3();
	HD_Vector3(T aX, T aY, T aZ);
	HD_Vector3(const HD_Vector3& aOther);

	void Set(T aX, T aY, T aZ);

	T GetLength() const;
	T GetLength2() const;

	void SetLength(T aLength);
	void Limit(T aLength);

	void Normalize();
	HD_Vector3 GetNormalized() const;

	T Dot(const HD_Vector3& aOther) const;
	HD_Vector3 Cross(const HD_Vector3& aOther) const;

	HD_Vector3& operator=(const HD_Vector3& aOther);
	HD_Vector3& operator+=(const HD_Vector3& aOther);
	HD_Vector3& operator-=(const HD_Vector3& aOther);
	HD_Vector3& operator*=(const HD_Matrix3x3<T>& aMatrix);
	HD_Vector3& operator*=(T aScalar);
	HD_Vector3& operator/=(T aScalar);

	T myX, myY, myZ;

public:
	typedef T DataType;

	static const HD_Vector3 Zero;
	static const HD_Vector3 Up;
	static const HD_Vector3 Down;
	static const HD_Vector3 Left;
	static const HD_Vector3 Right;
	static const HD_Vector3 Forward;
	static const HD_Vector3 Back;

	static T Length(const HD_Vector3& aStart, const HD_Vector3& aEnd);
	static T Length2(const HD_Vector3& aStart, const HD_Vector3& aEnd);
};

template<typename T> HD_Vector3<T> operator+(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2);
template<typename T> HD_Vector3<T> operator-(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2);
template<typename T> HD_Vector3<T> operator*(const HD_Vector3<T>& aVector, T aScalar);
template<typename T> HD_Vector3<T> operator*(T aScalar, const HD_Vector3<T>& aVector);
template<typename T> HD_Vector3<T> operator/(const HD_Vector3<T>& aVector, T aScalar);
template<typename T> bool operator==(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2);
template<typename T> bool operator!=(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2);

template<typename T>
HD_Vector3<T>::HD_Vector3()
	: myX()
	, myY()
	, myZ()
{
}

template<typename T>
HD_Vector3<T>::HD_Vector3(T aX, T aY, T aZ)
	: myX(aX)
	, myY(aY)
	, myZ(aZ)
{
}

template<typename T>
HD_Vector3<T>::HD_Vector3(const HD_Vector3& aOther)
	: myX(aOther.myX)
	, myY(aOther.myY)
	, myZ(aOther.myZ)
{
}

template<typename T>
void HD_Vector3<T>::Set(T aX, T aY, T aZ)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
}

template<typename T>
T HD_Vector3<T>::GetLength() const
{
	return HD_Sqrt(myX * myX + myY * myY + myZ * myZ);
}

template<typename T>
T HD_Vector3<T>::GetLength2() const
{
	return myX * myX + myY * myY + myZ * myZ;
}

template<typename T>
void HD_Vector3<T>::SetLength(T aLength)
{
	Normalize();
	(*this) *= aLength;
}

template<typename T>
void HD_Vector3<T>::Limit(T aLength)
{
	T length2 = GetLength2();
	if (length2 > aLength * aLength)
	{
		SetLength(aLength);
	}
}

template<typename T>
void HD_Vector3<T>::Normalize()
{
	// Note: will not compile if used on non-floating point types
	// with warning level 4 and warnings treated as errors due to
	// data loss in the float -> non-float conversion. But normalizing
	// a non-floating point type vector should be unusual anyway,
	// since in those cases the vector is used more like a container
	// than a mathematical vector.

	T length = GetLength();

	if (length == 0)
	{
		return;
	}

	(*this) /= length;
}

template<typename T>
HD_Vector3<T> HD_Vector3<T>::GetNormalized() const
{
	// Note: same note as Normalize.

	HD_Vector3<T> temp(*this);
	temp.Normalize();
	return temp;
}

template<typename T>
T HD_Vector3<T>::Dot(const HD_Vector3<T>& aOther) const
{
	return myX * aOther.myX + myY * aOther.myY + myZ * aOther.myZ;
}

template<typename T>
HD_Vector3<T> HD_Vector3<T>::Cross(const HD_Vector3<T>& aOther) const
{
	HD_Vector3 result(
		myY * aOther.myZ - aOther.myY * myZ,
		myZ * aOther.myX - aOther.myZ * myX,
		myX * aOther.myY - aOther.myX * myY
	);

	return result;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator=(const HD_Vector3<T>& aOther)
{
	myX = aOther.myX;
	myY = aOther.myY;
	myZ = aOther.myZ;

	return *this;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator+=(const HD_Vector3<T>& aOther)
{
	myX += aOther.myX;
	myY += aOther.myY;
	myZ += aOther.myZ;

	return *this;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator-=(const HD_Vector3<T>& aOther)
{
	myX -= aOther.myX;
	myY -= aOther.myY;
	myZ -= aOther.myZ;

	return *this;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator*=(const HD_Matrix3x3<T>& aMatrix)
{
	(*this) = (*this) * aMatrix;
	return *this;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator*=(T aScalar)
{
	myX *= aScalar;
	myY *= aScalar;
	myZ *= aScalar;

	return *this;
}

template<typename T>
HD_Vector3<T>& HD_Vector3<T>::operator/=(T aScalar)
{
	myX /= aScalar;
	myY /= aScalar;
	myZ /= aScalar;

	return *this;
}

template<typename T>
T HD_Vector3<T>::Length(const HD_Vector3& aStart, const HD_Vector3& aEnd)
{
	HD_Vector3 startToEnd = aEnd - aStart;
	return startToEnd.GetLength();
}

template<typename T>
T HD_Vector3<T>::Length2(const HD_Vector3& aStart, const HD_Vector3& aEnd)
{
	HD_Vector3 startToEnd = aEnd - aStart;
	return startToEnd.GetLength2();
}

template<typename T>
HD_Vector3<T> operator+(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2)
{
	return { aVector1.myX + aVector2.myX, aVector1.myY + aVector2.myY, aVector1.myZ + aVector2.myZ };
}

template<typename T>
HD_Vector3<T> operator-(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2)
{
	return { aVector1.myX - aVector2.myX, aVector1.myY - aVector2.myY, aVector1.myZ - aVector2.myZ };
}

template<typename T>
HD_Vector3<T> operator*(const HD_Vector3<T>& aVector, T aScalar)
{
	return { aVector.myX * aScalar, aVector.myY * aScalar, aVector.myZ * aScalar };
}

template<typename T>
HD_Vector3<T> operator*(T aScalar, const HD_Vector3<T>& aVector)
{
	return aVector * aScalar;
}

template<typename T>
HD_Vector3<T> operator/(const HD_Vector3<T>& aVector, T aScalar)
{
	return { aVector.myX / aScalar, aVector.myY / aScalar, aVector.myZ / aScalar };
}

template<typename T>
bool operator==(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2)
{
	return aVector1.myX == aVector2.myX && aVector1.myY == aVector2.myY && aVector1.myZ == aVector2.myZ;
}

template<typename T>
bool operator!=(const HD_Vector3<T>& aVector1, const HD_Vector3<T>& aVector2)
{
	return !(aVector1 == aVector2);
}

typedef HD_Vector3<f32> HD_Vector3_f32;
typedef HD_Vector3<f64> HD_Vector3_f64;
typedef HD_Vector3<s32> HD_Vector3_s32;
typedef HD_Vector3<u32> HD_Vector3_u32;

template<> const HD_Vector3<f32> HD_Vector3<f32>::Zero = { 0.f, 0.f, 0.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Up = { 0.f, 1.f, 0.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Down = { 0.f, -1.f, 0.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Left = { -1.f, 0.f, 0.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Right = { 1.f, 0.f, 0.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Forward = { 0.f, 0.f, 1.f };
template<> const HD_Vector3<f32> HD_Vector3<f32>::Back = { 0.f, 0.f, -1.f };
