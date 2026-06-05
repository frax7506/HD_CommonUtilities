#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Matrix.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Matrix3x3_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Matrix3x3f matrix;

			Assert::AreEqual(matrix.m11, 0.f);
			Assert::AreEqual(matrix.m12, 0.f);
			Assert::AreEqual(matrix.m13, 0.f);
			Assert::AreEqual(matrix.m21, 0.f);
			Assert::AreEqual(matrix.m22, 0.f);
			Assert::AreEqual(matrix.m23, 0.f);
			Assert::AreEqual(matrix.m31, 0.f);
			Assert::AreEqual(matrix.m32, 0.f);
			Assert::AreEqual(matrix.m33, 0.f);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Matrix3x3f matrix1;
			matrix1.m11 = 0.f;
			matrix1.m12 = 1.f;
			matrix1.m13 = 2.f;
			matrix1.m21 = 3.f;
			matrix1.m22 = 4.f;
			matrix1.m23 = 5.f;
			matrix1.m31 = 6.f;
			matrix1.m32 = 7.f;
			matrix1.m33 = 8.f;

			HD_Matrix3x3f matrix2(matrix1);

			Assert::AreEqual(matrix2.m11, 0.f);
			Assert::AreEqual(matrix2.m12, 1.f);
			Assert::AreEqual(matrix2.m13, 2.f);
			Assert::AreEqual(matrix2.m21, 3.f);
			Assert::AreEqual(matrix2.m22, 4.f);
			Assert::AreEqual(matrix2.m23, 5.f);
			Assert::AreEqual(matrix2.m31, 6.f);
			Assert::AreEqual(matrix2.m32, 7.f);
			Assert::AreEqual(matrix2.m33, 8.f);
		}

		TEST_METHOD(Constructor_Copy_Matrix4x4)
		{
			HD_Matrix4x4f matrix1;
			matrix1.m11 = 0.f;
			matrix1.m12 = 1.f;
			matrix1.m13 = 2.f;
			matrix1.m14 = 3.f;
			matrix1.m21 = 4.f;
			matrix1.m22 = 5.f;
			matrix1.m23 = 6.f;
			matrix1.m24 = 7.f;
			matrix1.m31 = 8.f;
			matrix1.m32 = 9.f;
			matrix1.m33 = 10.f;
			matrix1.m34 = 11.f;
			matrix1.m41 = 12.f;
			matrix1.m42 = 13.f;
			matrix1.m43 = 14.f;
			matrix1.m44 = 15.f;

			HD_Matrix3x3f matrix2(matrix1);

			Assert::AreEqual(matrix2.m11, 0.f);
			Assert::AreEqual(matrix2.m12, 1.f);
			Assert::AreEqual(matrix2.m13, 2.f);
			Assert::AreEqual(matrix2.m21, 4.f);
			Assert::AreEqual(matrix2.m22, 5.f);
			Assert::AreEqual(matrix2.m23, 6.f);
			Assert::AreEqual(matrix2.m31, 8.f);
			Assert::AreEqual(matrix2.m32, 9.f);
			Assert::AreEqual(matrix2.m33, 10.f);
		}

		TEST_METHOD(Constructor_InitializerList)
		{
			HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

			Assert::AreEqual(matrix.m11, 0.f);
			Assert::AreEqual(matrix.m12, 1.f);
			Assert::AreEqual(matrix.m13, 2.f);
			Assert::AreEqual(matrix.m21, 3.f);
			Assert::AreEqual(matrix.m22, 4.f);
			Assert::AreEqual(matrix.m23, 5.f);
			Assert::AreEqual(matrix.m31, 6.f);
			Assert::AreEqual(matrix.m32, 7.f);
			Assert::AreEqual(matrix.m33, 8.f);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_Matrix3x3f matrix1;
			matrix1.m11 = 0.f;
			matrix1.m12 = 1.f;
			matrix1.m13 = 2.f;
			matrix1.m21 = 3.f;
			matrix1.m22 = 4.f;
			matrix1.m23 = 5.f;
			matrix1.m31 = 6.f;
			matrix1.m32 = 7.f;
			matrix1.m33 = 8.f;

			HD_Matrix3x3f matrix2;
			matrix2 = matrix1;

			Assert::AreEqual(matrix2.m11, 0.f);
			Assert::AreEqual(matrix2.m12, 1.f);
			Assert::AreEqual(matrix2.m13, 2.f);
			Assert::AreEqual(matrix2.m21, 3.f);
			Assert::AreEqual(matrix2.m22, 4.f);
			Assert::AreEqual(matrix2.m23, 5.f);
			Assert::AreEqual(matrix2.m31, 6.f);
			Assert::AreEqual(matrix2.m32, 7.f);
			Assert::AreEqual(matrix2.m33, 8.f);
		}

		TEST_METHOD(Operator_Assignment_Copy_Matrix4x4)
		{
			HD_Matrix4x4f matrix1;
			matrix1.m11 = 0.f;
			matrix1.m12 = 1.f;
			matrix1.m13 = 2.f;
			matrix1.m14 = 3.f;
			matrix1.m21 = 4.f;
			matrix1.m22 = 5.f;
			matrix1.m23 = 6.f;
			matrix1.m24 = 7.f;
			matrix1.m31 = 8.f;
			matrix1.m32 = 9.f;
			matrix1.m33 = 10.f;
			matrix1.m34 = 11.f;
			matrix1.m41 = 12.f;
			matrix1.m42 = 13.f;
			matrix1.m43 = 14.f;
			matrix1.m44 = 15.f;

			HD_Matrix3x3f matrix2;
			matrix2 = matrix1;

			Assert::AreEqual(matrix2.m11, 0.f);
			Assert::AreEqual(matrix2.m12, 1.f);
			Assert::AreEqual(matrix2.m13, 2.f);
			Assert::AreEqual(matrix2.m21, 4.f);
			Assert::AreEqual(matrix2.m22, 5.f);
			Assert::AreEqual(matrix2.m23, 6.f);
			Assert::AreEqual(matrix2.m31, 8.f);
			Assert::AreEqual(matrix2.m32, 9.f);
			Assert::AreEqual(matrix2.m33, 10.f);
		}

		TEST_METHOD(Operator_Assignment_InitializerList)
		{
			HD_Matrix3x3f matrix;
			matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

			Assert::AreEqual(matrix.m11, 0.f);
			Assert::AreEqual(matrix.m12, 1.f);
			Assert::AreEqual(matrix.m13, 2.f);
			Assert::AreEqual(matrix.m21, 3.f);
			Assert::AreEqual(matrix.m22, 4.f);
			Assert::AreEqual(matrix.m23, 5.f);
			Assert::AreEqual(matrix.m31, 6.f);
			Assert::AreEqual(matrix.m32, 7.f);
			Assert::AreEqual(matrix.m33, 8.f);
		}

		TEST_METHOD(Operator_Function_Call_Row_And_Col)
		{
			HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

			Assert::AreEqual(matrix(1, 1), 0.f);
			Assert::AreEqual(matrix(1, 2), 1.f);
			Assert::AreEqual(matrix(1, 3), 2.f);
			Assert::AreEqual(matrix(2, 1), 3.f);
			Assert::AreEqual(matrix(2, 2), 4.f);
			Assert::AreEqual(matrix(2, 3), 5.f);
			Assert::AreEqual(matrix(3, 1), 6.f);
			Assert::AreEqual(matrix(3, 2), 7.f);
			Assert::AreEqual(matrix(3, 3), 8.f);
		}

		TEST_METHOD(Operator_Plus_Equals)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };

			matrix1 += matrix2;

			Assert::AreEqual(matrix1.m11, 9.f);
			Assert::AreEqual(matrix1.m12, 11.f);
			Assert::AreEqual(matrix1.m13, 13.f);
			Assert::AreEqual(matrix1.m21, 15.f);
			Assert::AreEqual(matrix1.m22, 17.f);
			Assert::AreEqual(matrix1.m23, 19.f);
			Assert::AreEqual(matrix1.m31, 21.f);
			Assert::AreEqual(matrix1.m32, 23.f);
			Assert::AreEqual(matrix1.m33, 25.f);
		}

		TEST_METHOD(Operator_Minus_Equals)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };

			matrix1 -= matrix2;

			Assert::AreEqual(matrix1.m11, -9.f);
			Assert::AreEqual(matrix1.m12, -9.f);
			Assert::AreEqual(matrix1.m13, -9.f);
			Assert::AreEqual(matrix1.m21, -9.f);
			Assert::AreEqual(matrix1.m22, -9.f);
			Assert::AreEqual(matrix1.m23, -9.f);
			Assert::AreEqual(matrix1.m31, -9.f);
			Assert::AreEqual(matrix1.m32, -9.f);
			Assert::AreEqual(matrix1.m33, -9.f);
		}

		TEST_METHOD(Operator_Multiplication_Equals)
		{
			HD_Matrix3x3f translation = HD_Matrix3x3f::Create2DTranslation(1.f, 1.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::Create2DRotation(F_PI_HALF);

			HD_Matrix3x3f translationAndRotation = translation;
			translationAndRotation *= rotation;

			HD_Vector3f point2D(1.f, 1.f, 1.f);
			point2D *= translationAndRotation;

			Assert::AreEqual(point2D.myX, -2.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(point2D.myY, 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Equals)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix3 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };

			Assert::IsTrue(matrix1 == matrix2);
			Assert::IsFalse(matrix1 == matrix3);
		}

		TEST_METHOD(Operator_Not_Equals)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix3 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };

			Assert::IsFalse(matrix1 != matrix2);
			Assert::IsTrue(matrix1 != matrix3);
		}

		TEST_METHOD(GetTranspose)
		{
			HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f transpose = matrix.GetTranspose();

			Assert::AreEqual(transpose.m11, 0.f);
			Assert::AreEqual(transpose.m12, 3.f);
			Assert::AreEqual(transpose.m13, 6.f);
			Assert::AreEqual(transpose.m21, 1.f);
			Assert::AreEqual(transpose.m22, 4.f);
			Assert::AreEqual(transpose.m23, 7.f);
			Assert::AreEqual(transpose.m31, 2.f);
			Assert::AreEqual(transpose.m32, 5.f);
			Assert::AreEqual(transpose.m33, 8.f);
		}

		TEST_METHOD(CreateRotationAroundX)
		{
			// fortsätt här
			Assert::IsTrue(false);
		}

		TEST_METHOD(CreateRotationAroundY)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(CreateRotationAroundZ)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Plus)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Minus)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Multiplication)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Multiplication_Matrix_Scalar)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Multiplication_Scalar_Matrix)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Operator_Multiplication_Vector_Matrix)
		{
			Assert::IsTrue(false);
		}
	};
}
