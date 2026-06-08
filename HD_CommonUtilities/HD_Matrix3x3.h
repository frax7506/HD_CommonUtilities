#pragma once

#include "HD_Swap.h"

#include <cassert>
#include <cstring>
#include <initializer_list>

template<typename T>
class HD_Vector3;

template<typename T>
class HD_Matrix4x4;

template<typename T>
class HD_Matrix3x3
{
public:
	HD_Matrix3x3();
	HD_Matrix3x3(const HD_Matrix3x3& aMatrix);
	HD_Matrix3x3(const HD_Matrix4x4<T>& aMatrix);
	HD_Matrix3x3(std::initializer_list<T> aInitializerList);

	HD_Matrix3x3& operator=(const HD_Matrix3x3& aMatrix);
	HD_Matrix3x3& operator=(const HD_Matrix4x4<T>& aMatrix);
	HD_Matrix3x3& operator=(std::initializer_list<T> aInitializerList);

	T& operator()(int aRow, int aCol);
	const T& operator()(int aRow, int aCol) const;

	HD_Matrix3x3& operator+=(const HD_Matrix3x3& aMatrix);
	HD_Matrix3x3& operator-=(const HD_Matrix3x3& aMatrix);
	HD_Matrix3x3& operator*=(const HD_Matrix3x3& aMatrix);

	bool operator==(const HD_Matrix3x3& aMatrix) const;
	bool operator!=(const HD_Matrix3x3& aMatrix) const;

	HD_Matrix3x3 GetTranspose() const;

	T m11, m12, m13, m21, m22, m23, m31, m32, m33;

public:
	static HD_Matrix3x3 CreateRotationAroundX(T aAngleInRadians);
	static HD_Matrix3x3 CreateRotationAroundY(T aAngleInRadians);
	static HD_Matrix3x3 CreateRotationAroundZ(T aAngleInRadians);

	static HD_Matrix3x3 Create2DRotation(T aAngleInRadians);
	static HD_Matrix3x3 Create2DTranslation(T aX, T aY);

	static const HD_Matrix3x3 Identity;
};

template<typename T> HD_Matrix3x3<T> operator+(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1);
template<typename T> HD_Matrix3x3<T> operator-(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1);
template<typename T> HD_Matrix3x3<T> operator*(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1);
template<typename T> HD_Matrix3x3<T> operator*(const HD_Matrix3x3<T>& aMatrix, T aScalar);
template<typename T> HD_Matrix3x3<T> operator*(T aScalar, const HD_Matrix3x3<T>& aMatrix);
template<typename T> HD_Vector3<T> operator*(const HD_Vector3<T>& aVector, const HD_Matrix3x3<T>& aMatrix);

template<typename T>
HD_Matrix3x3<T>::HD_Matrix3x3()
	: m11(), m12(), m13(), m21(), m22(), m23(), m31(), m32(), m33()
{
}

template<typename T>
HD_Matrix3x3<T>::HD_Matrix3x3(const HD_Matrix3x3& aMatrix)
{
	(*this) = aMatrix;
}

template<typename T>
HD_Matrix3x3<T>::HD_Matrix3x3(const HD_Matrix4x4<T>& aMatrix)
{
	(*this) = aMatrix;
}

template<typename T>
HD_Matrix3x3<T>::HD_Matrix3x3(std::initializer_list<T> aInitializerList)
{
	(*this) = aInitializerList;
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator=(const HD_Matrix3x3& aMatrix)
{
	memcpy(this, &aMatrix, 3 * 3 * sizeof(T));
	return *this;
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator=(const HD_Matrix4x4<T>& aMatrix)
{
	memcpy(&m11, &aMatrix.m11, 3 * sizeof(T));
	memcpy(&m21, &aMatrix.m21, 3 * sizeof(T));
	memcpy(&m31, &aMatrix.m31, 3 * sizeof(T));
	return *this;
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator=(std::initializer_list<T> aInitializerList)
{
	memcpy(this, aInitializerList.begin(), 3 * 3 * sizeof(T));
	return *this;
}

template<typename T>
T& HD_Matrix3x3<T>::operator()(int aRow, int aCol)
{
	assert(1 <= aRow && aRow <= 3 && 1 <= aCol && aCol <= 3);
	return *(&m11 + ((aRow - 1) * 3) + (aCol - 1));
}

template<typename T>
const T& HD_Matrix3x3<T>::operator()(int aRow, int aCol) const
{
	assert(1 <= aRow && aRow <= 3 && 1 <= aCol && aCol <= 3);
	return *(&m11 + ((aRow - 1) * 3) + (aCol - 1));
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator+=(const HD_Matrix3x3& aMatrix)
{
	m11 += aMatrix.m11;
	m12 += aMatrix.m12;
	m13 += aMatrix.m13;
	m21 += aMatrix.m21;
	m22 += aMatrix.m22;
	m23 += aMatrix.m23;
	m31 += aMatrix.m31;
	m32 += aMatrix.m32;
	m33 += aMatrix.m33;

	return *this;
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator-=(const HD_Matrix3x3& aMatrix)
{
	m11 -= aMatrix.m11;
	m12 -= aMatrix.m12;
	m13 -= aMatrix.m13;
	m21 -= aMatrix.m21;
	m22 -= aMatrix.m22;
	m23 -= aMatrix.m23;
	m31 -= aMatrix.m31;
	m32 -= aMatrix.m32;
	m33 -= aMatrix.m33;

	return *this;
}

template<typename T>
HD_Matrix3x3<T>& HD_Matrix3x3<T>::operator*=(const HD_Matrix3x3& aMatrix)
{
	(*this) = (*this) * aMatrix;
	return *this;
}

template<typename T>
bool HD_Matrix3x3<T>::operator==(const HD_Matrix3x3& aMatrix) const
{
	return	m11 == aMatrix.m11 && m12 == aMatrix.m12 && m13 == aMatrix.m13 &&
			m21 == aMatrix.m21 && m22 == aMatrix.m22 && m23 == aMatrix.m23 &&
			m31 == aMatrix.m31 && m32 == aMatrix.m32 && m33 == aMatrix.m33;
}

template<typename T>
bool HD_Matrix3x3<T>::operator!=(const HD_Matrix3x3& aMatrix) const
{
	return !((*this) == aMatrix);
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::GetTranspose() const
{
	HD_Matrix3x3 transpose = *this;

	HD_Swap(transpose.m21, transpose.m12);
	HD_Swap(transpose.m31, transpose.m13);
	HD_Swap(transpose.m32, transpose.m23);

	return transpose;
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
{
	HD_Matrix3x3 result =
	{
		1, 0, 0,
		0, HD_Cos(aAngleInRadians), HD_Sin(aAngleInRadians),
		0, -1 * HD_Sin(aAngleInRadians), HD_Cos(aAngleInRadians)
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
{
	HD_Matrix3x3 result =
	{
		HD_Cos(aAngleInRadians), 0, -1 * HD_Sin(aAngleInRadians),
		0, 1, 0,
		HD_Sin(aAngleInRadians), 0, HD_Cos(aAngleInRadians)
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
{
	HD_Matrix3x3 result =
	{
		HD_Cos(aAngleInRadians), HD_Sin(aAngleInRadians), 0,
		-1 * HD_Sin(aAngleInRadians), HD_Cos(aAngleInRadians), 0,
		0, 0, 1
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::Create2DRotation(T aAngleInRadians)
{
	return CreateRotationAroundZ(aAngleInRadians);
}

template<typename T>
HD_Matrix3x3<T> HD_Matrix3x3<T>::Create2DTranslation(T aX, T aY)
{
	HD_Matrix3x3 result = Identity;
	result.m31 = aX;
	result.m32 = aY;

	return result;
}

template<typename T>
HD_Matrix3x3<T> operator+(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1)
{
	HD_Matrix3x3 result =
	{
		aMatrix0.m11 + aMatrix1.m11, aMatrix0.m12 + aMatrix1.m12, aMatrix0.m13 + aMatrix1.m13,
		aMatrix0.m21 + aMatrix1.m21, aMatrix0.m22 + aMatrix1.m22, aMatrix0.m23 + aMatrix1.m23,
		aMatrix0.m31 + aMatrix1.m31, aMatrix0.m32 + aMatrix1.m32, aMatrix0.m33 + aMatrix1.m33
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> operator-(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1)
{
	HD_Matrix3x3 result =
	{
		aMatrix0.m11 - aMatrix1.m11, aMatrix0.m12 - aMatrix1.m12, aMatrix0.m13 - aMatrix1.m13,
		aMatrix0.m21 - aMatrix1.m21, aMatrix0.m22 - aMatrix1.m22, aMatrix0.m23 - aMatrix1.m23,
		aMatrix0.m31 - aMatrix1.m31, aMatrix0.m32 - aMatrix1.m32, aMatrix0.m33 - aMatrix1.m33
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> operator*(const HD_Matrix3x3<T>& aMatrix0, const HD_Matrix3x3<T>& aMatrix1)
{
	HD_Matrix3x3 result =
	{
		aMatrix0.m11 * aMatrix1.m11 + aMatrix0.m12 * aMatrix1.m21 + aMatrix0.m13 * aMatrix1.m31,
		aMatrix0.m11 * aMatrix1.m12 + aMatrix0.m12 * aMatrix1.m22 + aMatrix0.m13 * aMatrix1.m32,
		aMatrix0.m11 * aMatrix1.m13 + aMatrix0.m12 * aMatrix1.m23 + aMatrix0.m13 * aMatrix1.m33,

		aMatrix0.m21 * aMatrix1.m11 + aMatrix0.m22 * aMatrix1.m21 + aMatrix0.m23 * aMatrix1.m31,
		aMatrix0.m21 * aMatrix1.m12 + aMatrix0.m22 * aMatrix1.m22 + aMatrix0.m23 * aMatrix1.m32,
		aMatrix0.m21 * aMatrix1.m13 + aMatrix0.m22 * aMatrix1.m23 + aMatrix0.m23 * aMatrix1.m33,

		aMatrix0.m31 * aMatrix1.m11 + aMatrix0.m32 * aMatrix1.m21 + aMatrix0.m33 * aMatrix1.m31,
		aMatrix0.m31 * aMatrix1.m12 + aMatrix0.m32 * aMatrix1.m22 + aMatrix0.m33 * aMatrix1.m32,
		aMatrix0.m31 * aMatrix1.m13 + aMatrix0.m32 * aMatrix1.m23 + aMatrix0.m33 * aMatrix1.m33
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> operator*(const HD_Matrix3x3<T>& aMatrix, T aScalar)
{
	HD_Matrix3x3 result =
	{
		aMatrix.m11 * aScalar, aMatrix.m12 * aScalar, aMatrix.m13 * aScalar,
		aMatrix.m21 * aScalar, aMatrix.m22 * aScalar, aMatrix.m23 * aScalar,
		aMatrix.m31 * aScalar, aMatrix.m32 * aScalar, aMatrix.m33 * aScalar
	};

	return result;
}

template<typename T>
HD_Matrix3x3<T> operator*(T aScalar, const HD_Matrix3x3<T>& aMatrix)
{
	return aMatrix * aScalar;
}

template<typename T>
HD_Vector3<T> operator*(const HD_Vector3<T>& aVector, const HD_Matrix3x3<T>& aMatrix)
{
	HD_Vector3 result =
	{
		aVector.myX * aMatrix.m11 + aVector.myY * aMatrix.m21 + aVector.myZ * aMatrix.m31,
		aVector.myX * aMatrix.m12 + aVector.myY * aMatrix.m22 + aVector.myZ * aMatrix.m32,
		aVector.myX * aMatrix.m13 + aVector.myY * aMatrix.m23 + aVector.myZ * aMatrix.m33
	};

	return result;
}

typedef HD_Matrix3x3<float> HD_Matrix3x3f;
typedef HD_Matrix3x3<double> HD_Matrix3x3d;

template <> const HD_Matrix3x3<float> HD_Matrix3x3<float>::Identity = { 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f };
