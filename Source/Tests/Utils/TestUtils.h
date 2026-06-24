#pragma once

#include "CppUnitTest.h"

#include "HD_Math.h"
#include "HD_Matrix.h"
#include "HD_StaticString.h"
#include "HD_String.h"
#include "HD_Vector2.h"
#include "HD_Vector3.h"
#include "HD_Vector4.h"

#define FLOAT_EQUAL_TOLERANCE F_SMALL

namespace TestUtils
{
	template<typename T>
	void String_IsUninitialized(const HD_Str<T>& aStringToCheck);

	template<typename T, int aCapacity>
	void StaticString_IsUninitialized(const HD_StaticStr<T, aCapacity>& aStringToCheck);

	template<typename T>
	void Vector2_AreEqual(const HD_Vector2<T>& aVector, T aX, T aY);

	template<typename T>
	void Vector3_AreEqual(const HD_Vector3<T>& aVector, T aX, T aY, T aZ);

	template<typename T>
	void Vector4_AreEqual(const HD_Vector4<T>& aVector, T aX, T aY, T aZ, T aW);

	template<typename T>
	void Matrix3x3_AreEqual(const HD_Matrix3x3<T>& aMatrix, T a11, T a12, T a13, T a21, T a22, T a23, T a31, T a32, T a33);

	template<typename T>
	void Matrix4x4_AreEqual(const HD_Matrix4x4<T>& aMatrix, T a11, T a12, T a13, T a14, T a21, T a22, T a23, T a24, T a31, T a32, T a33, T a34, T a41, T a42, T a43, T a44);

	template<>
	void Vector2_AreEqual(const HD_Vector2f& aVector, f32 aX, f32 aY);

	template<>
	void Vector3_AreEqual(const HD_Vector3f& aVector, f32 aX, f32 aY, f32 aZ);

	template<>
	void Vector4_AreEqual(const HD_Vector4f& aVector, f32 aX, f32 aY, f32 aZ, f32 aW);

	template<>
	void Matrix3x3_AreEqual(const HD_Matrix3x3f& aMatrix, f32 a11, f32 a12, f32 a13, f32 a21, f32 a22, f32 a23, f32 a31, f32 a32, f32 a33);

	template<>
	void Matrix4x4_AreEqual(const HD_Matrix4x4f& aMatrix, f32 a11, f32 a12, f32 a13, f32 a14, f32 a21, f32 a22, f32 a23, f32 a24, f32 a31, f32 a32, f32 a33, f32 a34, f32 a41, f32 a42, f32 a43, f32 a44);

	template<typename T>
	void String_IsUninitialized(const HD_Str<T>& aStringToCheck)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(aStringToCheck.GetBuffer());
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetLength(), 0);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetCapacity(), 0);
	}

	template<typename T, int aCapacity>
	void StaticString_IsUninitialized(const HD_StaticStr<T, aCapacity>& aStringToCheck)
	{
		T zeroMemory[aCapacity]{ 0 };
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(memcmp(aStringToCheck.GetBuffer(), zeroMemory, aCapacity * sizeof(T)) == 0);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aStringToCheck.GetLength(), 0);
	}

	template<typename T>
	void Vector2_AreEqual(const HD_Vector2<T>& aVector, T aX, T aY)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY);
	}

	template<typename T>
	void Vector3_AreEqual(const HD_Vector3<T>& aVector, T aX, T aY, T aZ)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myZ, aZ);
	}

	template<typename T>
	void Vector4_AreEqual(const HD_Vector4<T>& aVector, T aX, T aY, T aZ, T aW)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myZ, aZ);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myW, aW);
	}

	template<typename T>
	void Matrix3x3_AreEqual(const HD_Matrix3x3<T>& aMatrix, T a11, T a12, T a13, T a21, T a22, T a23, T a31, T a32, T a33)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m11, a11);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m12, a12);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m13, a13);

		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m21, a21);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m22, a22);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m23, a23);

		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m31, a31);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m32, a32);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m33, a33);
	}

	template<typename T>
	void Matrix4x4_AreEqual(const HD_Matrix4x4<T>& aMatrix, T a11, T a12, T a13, T a14, T a21, T a22, T a23, T a24, T a31, T a32, T a33, T a34, T a41, T a42, T a43, T a44)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m11, a11);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m12, a12);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m13, a13);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m14, a14);

		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m21, a21);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m22, a22);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m23, a23);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m24, a24);

		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m31, a31);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m32, a32);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m33, a33);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m34, a34);

		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m41, a41);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m42, a42);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m43, a43);
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m44, a44);
	}
}
