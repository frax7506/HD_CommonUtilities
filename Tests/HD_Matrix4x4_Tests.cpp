#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Matrix.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Matrix4x4_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Matrix4x4f matrix;
			TestUtils::Matrix4x4_AreEqual(matrix, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2(matrix1);
			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Constructor_Copy_Matrix3x3)
		{
			HD_Matrix3x3f matrix1 =
			{
				0.f, 1.f, 2.f,
				3.f, 4.f, 5.f,
				6.f, 7.f, 8.f
			};

			HD_Matrix4x4f matrix2(matrix1);

			TestUtils::Matrix4x4_AreEqual(matrix2,
				0.f, 1.f, 2.f, 0.f,
				3.f, 4.f, 5.f, 0.f,
				6.f, 7.f, 8.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		TEST_METHOD(Constructor_InitializerList)
		{
			HD_Matrix4x4f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			TestUtils::Matrix4x4_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };

			HD_Matrix4x4f matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_Assignment_Matrix3x3)
		{
			HD_Matrix3x3f matrix1 =
			{
				0.f, 1.f, 2.f,
				3.f, 4.f, 5.f,
				6.f, 7.f, 8.f
			};

			HD_Matrix4x4f matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2,
				0.f, 1.f, 2.f, 0.f,
				3.f, 4.f, 5.f, 0.f,
				6.f, 7.f, 8.f, 0.f,
				0.f, 0.f, 0.f, 0.f
			);
		}

		TEST_METHOD(Operator_Assignment_InitializerList)
		{
			HD_Matrix4x4f matrix;
			matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			TestUtils::Matrix4x4_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_Function_Call_Row_And_Col)
		{
			HD_Matrix4x4f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };

			Assert::AreEqual(matrix(1, 1), 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 2), 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 3), 2.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 4), 3.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 1), 4.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 2), 5.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 3), 6.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 4), 7.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 1), 8.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 2), 9.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 3), 10.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 4), 11.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 1), 12.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 2), 13.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 3), 14.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 4), 15.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			matrix1 += matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix1, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			matrix1 -= matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix1, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Matrix4x4f rotation = HD_Matrix4x4f::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix4x4f translation = HD_Matrix4x4f::CreateTranslation(1.f, 1.f, 1.f);

			HD_Matrix4x4f rotationAndTranslation = rotation;
			rotationAndTranslation *= translation;

			HD_Vector4f point3D(1.f, 1.f, 1.f, 1.f);
			point3D *= rotationAndTranslation;

			TestUtils::Vector4_AreEqual(point3D, 2.f, 0.f, 2.f, 1.f);
		}

		TEST_METHOD(Operator_Equals)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix3 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			Assert::IsTrue(matrix1 == matrix2);
			Assert::IsFalse(matrix1 == matrix3);
		}

		TEST_METHOD(Operator_Not_Equals)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix3 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			Assert::IsFalse(matrix1 != matrix2);
			Assert::IsTrue(matrix1 != matrix3);
		}

		TEST_METHOD(GetTranspose)
		{
			HD_Matrix4x4f matrix =
			{
				0.f, 1.f, 2.f, 3.f,
				4.f, 5.f, 6.f, 7.f,
				8.f, 9.f, 10.f, 11.f,
				12.f, 13.f, 14.f, 15.f
			};

			HD_Matrix4x4f transpose = matrix.GetTranspose();

			TestUtils::Matrix4x4_AreEqual(transpose,
				0.f, 4.f, 8.f, 12.f,
				1.f, 5.f, 9.f, 13.f,
				2.f, 6.f, 10.f, 14.f,
				3.f, 7.f, 11.f, 15.f
			);
		}

		TEST_METHOD(CreateRotationAroundX)
		{
			HD_Vector4f vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4f rotation = HD_Matrix3x3f::CreateRotationAroundX(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, 1.f, -1.f, 1.f, 0.f);
		}

		TEST_METHOD(CreateRotationAroundY)
		{
			HD_Vector4f vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4f rotation = HD_Matrix3x3f::CreateRotationAroundY(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, 1.f, 1.f, -1.f, 0.f);
		}

		TEST_METHOD(CreateRotationAroundZ)
		{
			HD_Vector4f vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4f rotation = HD_Matrix3x3f::CreateRotationAroundZ(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, -1.f, 1.f, 1.f, 0.f);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };
			HD_Matrix4x4f matrix3 = matrix1 + matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix3, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };
			HD_Matrix4x4f matrix3 = matrix1 - matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix3, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f);
		}

		TEST_METHOD(Operator_Multiplication)
		{
			HD_Matrix4x4f rotation90AroundX = HD_Matrix4x4f::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix4x4f rotation90AroundY = HD_Matrix4x4f::CreateRotationAroundY(F_PI_HALF);
			HD_Matrix4x4f rotation90AroundXAndRotation90AroundY = rotation90AroundX * rotation90AroundY;

			HD_Vector4f vector(1.f, 1.f, 1.f, 0.f);
			vector *= rotation90AroundXAndRotation90AroundY;

			TestUtils::Vector4_AreEqual(vector, 1.f, -1.f, -1.f, 0.f);
		}

		TEST_METHOD(Operator_Multiplication_Matrix_Scalar)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = matrix1 * 2.f;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f);
		}

		TEST_METHOD(Operator_Multiplication_Scalar_Matrix)
		{
			HD_Matrix4x4f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4f matrix2 = 2.f * matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f);
		}

		TEST_METHOD(Operator_Multiplication_Vector_Matrix)
		{
			HD_Vector4f vector1(1.f, 1.f, 1.f, 0.f);
			HD_Vector4f vector2 = vector1 * HD_Matrix4x4f::CreateRotationAroundX(F_PI_HALF);

			TestUtils::Vector4_AreEqual(vector2, 1.f, -1.f, 1.f, 0.f);
		}
	};
}
