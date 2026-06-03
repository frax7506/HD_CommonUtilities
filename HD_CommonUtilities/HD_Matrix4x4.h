#pragma once

#include "HD_Swap.h"

#include <cassert>
#include <cstring>
#include <initializer_list>

template<typename T>
class HD_Vector4;

template<typename T>
class HD_Matrix3x3;

template<typename T>
class HD_Matrix4x4
{
public:
	HD_Matrix4x4();
	HD_Matrix4x4(const HD_Matrix4x4& aMatrix);
	HD_Matrix4x4(const HD_Matrix3x3<T>& aMatrix);
	HD_Matrix4x4(std::initializer_list<T> aInitializerList);

	HD_Matrix4x4& operator=(const HD_Matrix4x4& aMatrix);
	HD_Matrix4x4& operator=(const HD_Matrix3x3<T>& aMatrix);
	HD_Matrix4x4& operator=(std::initializer_list<T> aInitializerList);

	T& operator()(int aRow, int aCol);
	const T& operator()(int aRow, int aCol) const;

	HD_Matrix4x4& operator+=(const HD_Matrix4x4& aMatrix);
	HD_Matrix4x4& operator-=(const HD_Matrix4x4& aMatrix);
	HD_Matrix4x4& operator*=(const HD_Matrix4x4& aMatrix);

	bool operator==(const HD_Matrix4x4& aMatrix) const;
	bool operator!=(const HD_Matrix4x4& aMatrix) const;

	HD_Matrix4x4 GetTranspose() const;

	T m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

public:
	static HD_Matrix4x4 CreateRotationAroundX(T aAngleInRadians);
	static HD_Matrix4x4 CreateRotationAroundY(T aAngleInRadians);
	static HD_Matrix4x4 CreateRotationAroundZ(T aAngleInRadians);

	static const HD_Matrix4x4 Identity;
};

template<typename T> HD_Matrix4x4<T> operator+(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1);
template<typename T> HD_Matrix4x4<T> operator-(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1);
template<typename T> HD_Matrix4x4<T> operator*(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1);
template<typename T> HD_Matrix4x4<T> operator*(const HD_Matrix4x4<T>& aMatrix, T aScalar);
template<typename T> HD_Matrix4x4<T> operator*(T aScalar, const HD_Matrix4x4<T>& aMatrix);
template<typename T> HD_Vector4<T> operator*(const HD_Vector4<T>& aVector, const HD_Matrix4x4<T>& aMatrix);

template<typename T>
HD_Matrix4x4<T>::HD_Matrix4x4()
{
	memset(&m11, T(), 4 * 4 * sizeof(T));
}

template<typename T>
HD_Matrix4x4<T>::HD_Matrix4x4(const HD_Matrix4x4& aMatrix)
{
	(*this) = aMatrix;
}

template<typename T>
HD_Matrix4x4<T>::HD_Matrix4x4(const HD_Matrix3x3<T>& aMatrix)
{
	(*this) = aMatrix;
}

template<typename T>
HD_Matrix4x4<T>::HD_Matrix4x4(std::initializer_list<T> aInitializerList)
{
	(*this) = aInitializerList;
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator=(const HD_Matrix4x4& aMatrix)
{
	memcpy(&m11, &aMatrix, 4 * 4 * sizeof(T));
	return *this;
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator=(const HD_Matrix3x3<T>& aMatrix)
{
	memcpy(&m11, aMatrix.m11, 3 * sizeof(T));
	memcpy(&m21, aMatrix.m21, 3 * sizeof(T));
	memcpy(&m31, aMatrix.m31, 3 * sizeof(T));
	return *this;
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator=(std::initializer_list<T> aInitializerList)
{
	memcpy(&m11, aInitializerList.begin(), 4 * 4 * sizeof(T));
	return *this;
}

template<typename T>
T& HD_Matrix4x4<T>::operator()(int aRow, int aCol)
{
	assert(1 <= aRow && aRow <= 4 && 1 <= aCol && aCol <= 4);
	return *(&m11 + ((aRow - 1) * 4) + (aCol - 1));
}

template<typename T>
const T& HD_Matrix4x4<T>::operator()(int aRow, int aCol) const
{
	assert(1 <= aRow && aRow <= 4 && 1 <= aCol && aCol <= 4);
	return *(&m11 + ((aRow - 1) * 4) + (aCol - 1));
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator+=(const HD_Matrix4x4& aMatrix)
{
	m11 += aMatrix.m11;
	m12 += aMatrix.m12;
	m13 += aMatrix.m13;
	m14 += aMatrix.m14;

	m21 += aMatrix.m21;
	m22 += aMatrix.m22;
	m23 += aMatrix.m23;
	m24 += aMatrix.m24;

	m31 += aMatrix.m31;
	m32 += aMatrix.m32;
	m33 += aMatrix.m33;
	m34 += aMatrix.m34;

	m41 += aMatrix.m41;
	m42 += aMatrix.m42;
	m43 += aMatrix.m43;
	m44 += aMatrix.m44;

	return *this;
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator-=(const HD_Matrix4x4& aMatrix)
{
	m11 -= aMatrix.m11;
	m12 -= aMatrix.m12;
	m13 -= aMatrix.m13;
	m14 -= aMatrix.m14;

	m21 -= aMatrix.m21;
	m22 -= aMatrix.m22;
	m23 -= aMatrix.m23;
	m24 -= aMatrix.m24;

	m31 -= aMatrix.m31;
	m32 -= aMatrix.m32;
	m33 -= aMatrix.m33;
	m34 -= aMatrix.m34;

	m41 -= aMatrix.m41;
	m42 -= aMatrix.m42;
	m43 -= aMatrix.m43;
	m44 -= aMatrix.m44;

	return *this;
}

template<typename T>
HD_Matrix4x4<T>& HD_Matrix4x4<T>::operator*=(const HD_Matrix4x4& aMatrix)
{
	m11 = m11 * aMatrix.m11 + m12 * aMatrix.m21 + m13 * aMatrix.m31 + m14 * aMatrix.m41;
	m12 = m11 * aMatrix.m12 + m12 * aMatrix.m22 + m13 * aMatrix.m32 + m14 * aMatrix.m42;
	m13 = m11 * aMatrix.m13 + m12 * aMatrix.m23 + m13 * aMatrix.m33 + m14 * aMatrix.m43;
	m14 = m11 * aMatrix.m14 + m12 * aMatrix.m24 + m13 * aMatrix.m34 + m14 * aMatrix.m44;

	m21 = m21 * aMatrix.m11 + m22 * aMatrix.m21 + m23 * aMatrix.m31 + m24 * aMatrix.m41;
	m22 = m21 * aMatrix.m12 + m22 * aMatrix.m22 + m23 * aMatrix.m32 + m24 * aMatrix.m42;
	m23 = m21 * aMatrix.m13 + m22 * aMatrix.m23 + m23 * aMatrix.m33 + m24 * aMatrix.m43;
	m24 = m21 * aMatrix.m14 + m22 * aMatrix.m24 + m23 * aMatrix.m34 + m24 * aMatrix.m44;

	m31 = m31 * aMatrix.m11 + m32 * aMatrix.m21 + m33 * aMatrix.m31 + m34 * aMatrix.m41;
	m32 = m31 * aMatrix.m12 + m32 * aMatrix.m22 + m33 * aMatrix.m32 + m34 * aMatrix.m42;
	m33 = m31 * aMatrix.m13 + m32 * aMatrix.m23 + m33 * aMatrix.m33 + m34 * aMatrix.m43;
	m34 = m31 * aMatrix.m14 + m32 * aMatrix.m24 + m33 * aMatrix.m34 + m34 * aMatrix.m44;

	m41 = m41 * aMatrix.m11 + m42 * aMatrix.m21 + m43 * aMatrix.m31 + m44 * aMatrix.m41;
	m42 = m41 * aMatrix.m12 + m42 * aMatrix.m22 + m43 * aMatrix.m32 + m44 * aMatrix.m42;
	m43 = m41 * aMatrix.m13 + m42 * aMatrix.m23 + m43 * aMatrix.m33 + m44 * aMatrix.m43;
	m44 = m41 * aMatrix.m14 + m42 * aMatrix.m24 + m43 * aMatrix.m34 + m44 * aMatrix.m44;

	return *this;
}

template<typename T>
bool HD_Matrix4x4<T>::operator==(const HD_Matrix4x4& aMatrix) const
{
	return	m11 == aMatrix.m11 && m12 == aMatrix.m12 && m13 == aMatrix.m13 && m14 == aMatrix.m14 &&
			m21 == aMatrix.m21 && m22 == aMatrix.m22 && m23 == aMatrix.m23 && m24 == aMatrix.m24 &&
			m31 == aMatrix.m31 && m32 == aMatrix.m32 && m33 == aMatrix.m33 && m34 == aMatrix.m34 &&
			m41 == aMatrix.m41 && m42 == aMatrix.m42 && m43 == aMatrix.m43 && m44 == aMatrix.m44;
}

template<typename T>
bool HD_Matrix4x4<T>::operator!=(const HD_Matrix4x4& aMatrix) const
{
	return !((*this) == aMatrix);
}

template<typename T>
HD_Matrix4x4<T> HD_Matrix4x4<T>::GetTranspose() const
{
	HD_Matrix4x4 transpose = *this;

	HD_Swap(transpose.m21, transpose.m12);
	HD_Swap(transpose.m31, transpose.m13);
	HD_Swap(transpose.m32, transpose.m23);
	HD_Swap(transpose.m41, transpose.m14);
	HD_Swap(transpose.m42, transpose.m24);
	HD_Swap(transpose.m43, transpose.m34);

	return transpose;
}

template<typename T>
HD_Matrix4x4<T> HD_Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
{
	return HD_Matrix3x3<T>::CreateRotationAroundX(aAngleInRadians);
}

template<typename T>
HD_Matrix4x4<T> HD_Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
{
	return HD_Matrix3x3<T>::CreateRotationAroundY(aAngleInRadians);
}

template<typename T>
HD_Matrix4x4<T> HD_Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
{
	return HD_Matrix3x3<T>::CreateRotationAroundZ(aAngleInRadians);
}

template<typename T>
HD_Matrix4x4<T> operator+(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1)
{
	HD_Matrix4x4 result =
	{
		aMatrix0.m11 + aMatrix1.m11, aMatrix0.m12 + aMatrix1.m12, aMatrix0.m13 + aMatrix1.m13, aMatrix0.m14 + aMatrix1.m14,
		aMatrix0.m21 + aMatrix1.m21, aMatrix0.m22 + aMatrix1.m22, aMatrix0.m23 + aMatrix1.m23, aMatrix0.m24 + aMatrix1.m24,
		aMatrix0.m31 + aMatrix1.m31, aMatrix0.m32 + aMatrix1.m32, aMatrix0.m33 + aMatrix1.m33, aMatrix0.m34 + aMatrix1.m34,
		aMatrix0.m41 + aMatrix1.m41, aMatrix0.m42 + aMatrix1.m42, aMatrix0.m43 + aMatrix1.m42, aMatrix0.m44 + aMatrix1.m44
	};

	return result;
}

template<typename T>
HD_Matrix4x4<T> operator-(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1)
{
	HD_Matrix4x4 result =
	{
		aMatrix0.m11 - aMatrix1.m11, aMatrix0.m12 - aMatrix1.m12, aMatrix0.m13 - aMatrix1.m13, aMatrix0.m14 - aMatrix1.m14,
		aMatrix0.m21 - aMatrix1.m21, aMatrix0.m22 - aMatrix1.m22, aMatrix0.m23 - aMatrix1.m23, aMatrix0.m24 - aMatrix1.m24,
		aMatrix0.m31 - aMatrix1.m31, aMatrix0.m32 - aMatrix1.m32, aMatrix0.m33 - aMatrix1.m33, aMatrix0.m34 - aMatrix1.m34,
		aMatrix0.m41 - aMatrix1.m41, aMatrix0.m42 - aMatrix1.m42, aMatrix0.m43 - aMatrix1.m42, aMatrix0.m44 - aMatrix1.m44
	};

	return result;
}

template<typename T>
HD_Matrix4x4<T> operator*(const HD_Matrix4x4<T>& aMatrix0, const HD_Matrix4x4<T>& aMatrix1)
{
	HD_Matrix4x4 result =
	{
		aMatrix0.m11 * aMatrix1.m11 + aMatrix0.m12 * aMatrix1.m21 + aMatrix0.m13 * aMatrix1.m31 + aMatrix0.m14 * aMatrix1.m41,
		aMatrix0.m11 * aMatrix1.m12 + aMatrix0.m12 * aMatrix1.m22 + aMatrix0.m13 * aMatrix1.m32 + aMatrix0.m14 * aMatrix1.m42,
		aMatrix0.m11 * aMatrix1.m13 + aMatrix0.m12 * aMatrix1.m23 + aMatrix0.m13 * aMatrix1.m33 + aMatrix0.m14 * aMatrix1.m43,
		aMatrix0.m11 * aMatrix1.m14 + aMatrix0.m12 * aMatrix1.m24 + aMatrix0.m13 * aMatrix1.m34 + aMatrix0.m14 * aMatrix1.m44,

		aMatrix0.m21 * aMatrix1.m11 + aMatrix0.m22 * aMatrix1.m21 + aMatrix0.m23 * aMatrix1.m31 + aMatrix0.m24 * aMatrix1.m41,
		aMatrix0.m21 * aMatrix1.m12 + aMatrix0.m22 * aMatrix1.m22 + aMatrix0.m23 * aMatrix1.m32 + aMatrix0.m24 * aMatrix1.m42,
		aMatrix0.m21 * aMatrix1.m13 + aMatrix0.m22 * aMatrix1.m23 + aMatrix0.m23 * aMatrix1.m33 + aMatrix0.m24 * aMatrix1.m43,
		aMatrix0.m21 * aMatrix1.m14 + aMatrix0.m22 * aMatrix1.m24 + aMatrix0.m23 * aMatrix1.m34 + aMatrix0.m24 * aMatrix1.m44,

		aMatrix0.m31 * aMatrix1.m11 + aMatrix0.m32 * aMatrix1.m21 + aMatrix0.m33 * aMatrix1.m31 + aMatrix0.m34 * aMatrix1.m41,
		aMatrix0.m31 * aMatrix1.m12 + aMatrix0.m32 * aMatrix1.m22 + aMatrix0.m33 * aMatrix1.m32 + aMatrix0.m34 * aMatrix1.m42,
		aMatrix0.m31 * aMatrix1.m13 + aMatrix0.m32 * aMatrix1.m23 + aMatrix0.m33 * aMatrix1.m33 + aMatrix0.m34 * aMatrix1.m43,
		aMatrix0.m31 * aMatrix1.m14 + aMatrix0.m32 * aMatrix1.m24 + aMatrix0.m33 * aMatrix1.m34 + aMatrix0.m34 * aMatrix1.m44,

		aMatrix0.m41 * aMatrix1.m11 + aMatrix0.m42 * aMatrix1.m21 + aMatrix0.m43 * aMatrix1.m31 + aMatrix0.m44 * aMatrix1.m41,
		aMatrix0.m41 * aMatrix1.m12 + aMatrix0.m42 * aMatrix1.m22 + aMatrix0.m43 * aMatrix1.m32 + aMatrix0.m44 * aMatrix1.m42,
		aMatrix0.m41 * aMatrix1.m13 + aMatrix0.m42 * aMatrix1.m23 + aMatrix0.m43 * aMatrix1.m33 + aMatrix0.m44 * aMatrix1.m43,
		aMatrix0.m41 * aMatrix1.m14 + aMatrix0.m42 * aMatrix1.m24 + aMatrix0.m43 * aMatrix1.m34 + aMatrix0.m44 * aMatrix1.m44
	};

	return result;
}

template<typename T>
HD_Matrix4x4<T> operator*(const HD_Matrix4x4<T>& aMatrix, T aScalar)
{
	HD_Matrix4x4 result =
	{
		aMatrix.m11 * aScalar, aMatrix.m12 * aScalar, aMatrix.m13 * aScalar, aMatrix.m14 * aScalar,
		aMatrix.m21 * aScalar, aMatrix.m22 * aScalar, aMatrix.m23 * aScalar, aMatrix.m24 * aScalar,
		aMatrix.m31 * aScalar, aMatrix.m32 * aScalar, aMatrix.m33 * aScalar, aMatrix.m34 * aScalar,
		aMatrix.m41 * aScalar, aMatrix.m42 * aScalar, aMatrix.m43 * aScalar, aMatrix.m44 * aScalar
	};

	return result;
}

template<typename T>
HD_Matrix4x4<T> operator*(T aScalar, const HD_Matrix4x4<T>& aMatrix)
{
	return aMatrix * aScalar;
}

template<typename T>
HD_Vector4<T> operator*(const HD_Vector4<T>& aVector, const HD_Matrix4x4<T>& aMatrix)
{
	HD_Vector4 result =
	{
		aVector.myX * aMatrix.m11 + aVector.myY * aMatrix.m21 + aVector.myZ * aMatrix.m31, aVector.myW * aMatrix.m41,
		aVector.myX * aMatrix.m21 + aVector.myY * aMatrix.m22 + aVector.myZ * aMatrix.m32, aVector.myW * aMatrix.m42,
		aVector.myX * aMatrix.m31 + aVector.myY * aMatrix.m23 + aVector.myZ * aMatrix.m33, aVector.myW * aMatrix.m43,
		aVector.myX * aMatrix.m41 + aVector.myY * aMatrix.m24 + aVector.myZ * aMatrix.m34, aVector.myW * aMatrix.m44
	};

	return result;
}

typedef HD_Matrix4x4<float> HD_Matrix4x4f;
typedef HD_Matrix4x4<double> HD_Matrix4x4d;

template <> const HD_Matrix4x4<float> HD_Matrix4x4<float>::Identity = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
