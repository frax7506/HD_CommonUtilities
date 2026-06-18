#include "stdafx.h"
#include "TestUtils.h"

template<>
void TestUtils::Vector2_AreEqual(const HD_Vector2f& aVector, f32 aX, f32 aY)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY, FLOAT_EQUAL_TOLERANCE);
}

template<>
void TestUtils::Vector3_AreEqual(const HD_Vector3f& aVector, f32 aX, f32 aY, f32 aZ)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myZ, aZ, FLOAT_EQUAL_TOLERANCE);
}

template<>
void TestUtils::Vector4_AreEqual(const HD_Vector4f& aVector, f32 aX, f32 aY, f32 aZ, f32 aW)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myX, aX, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myY, aY, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myZ, aZ, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aVector.myW, aW, FLOAT_EQUAL_TOLERANCE);
}

template<>
void TestUtils::Matrix3x3_AreEqual(const HD_Matrix3x3f& aMatrix, f32 a11, f32 a12, f32 a13, f32 a21, f32 a22, f32 a23, f32 a31, f32 a32, f32 a33)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m11, a11, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m12, a12, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m13, a13, FLOAT_EQUAL_TOLERANCE);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m21, a21, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m22, a22, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m23, a23, FLOAT_EQUAL_TOLERANCE);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m31, a31, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m32, a32, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m33, a33, FLOAT_EQUAL_TOLERANCE);
}

template<>
void TestUtils::Matrix4x4_AreEqual(const HD_Matrix4x4f& aMatrix, f32 a11, f32 a12, f32 a13, f32 a14, f32 a21, f32 a22, f32 a23, f32 a24, f32 a31, f32 a32, f32 a33, f32 a34, f32 a41, f32 a42, f32 a43, f32 a44)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m11, a11, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m12, a12, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m13, a13, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m14, a14, FLOAT_EQUAL_TOLERANCE);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m21, a21, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m22, a22, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m23, a23, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m24, a24, FLOAT_EQUAL_TOLERANCE);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m31, a31, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m32, a32, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m33, a33, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m34, a34, FLOAT_EQUAL_TOLERANCE);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m41, a41, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m42, a42, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m43, a43, FLOAT_EQUAL_TOLERANCE);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(aMatrix.m44, a44, FLOAT_EQUAL_TOLERANCE);
}
