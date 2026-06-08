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
			TestUtils::Matrix3x3_AreEqual(matrix, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2(matrix1);
			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
		}

		TEST_METHOD(Constructor_Copy_Matrix4x4)
		{
			HD_Matrix4x4f matrix1 =
			{
				0.f, 1.f, 2.f, 3.f,
				4.f, 5.f, 6.f, 7.f,
				8.f, 9.f, 10.f, 11.f,
				12.f, 13.f, 14.f, 15.f
			};

			HD_Matrix3x3f matrix2(matrix1);
			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 1.f, 2.f, 4.f, 5.f, 6.f, 8.f, 9.f, 10.f);
		}

		TEST_METHOD(Constructor_InitializerList)
		{
			HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			TestUtils::Matrix3x3_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

			HD_Matrix3x3f matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
		}

		TEST_METHOD(Operator_Assignment_Copy_Matrix4x4)
		{
			HD_Matrix4x4f matrix1 =
			{
				0.f, 1.f, 2.f, 3.f,
				4.f, 5.f, 6.f, 7.f,
				8.f, 9.f, 10.f, 11.f,
				12.f, 13.f, 14.f, 15.f
			};

			HD_Matrix3x3f matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 1.f, 2.f, 4.f, 5.f, 6.f, 8.f, 9.f, 10.f);
		}

		TEST_METHOD(Operator_Assignment_InitializerList)
		{
			HD_Matrix3x3f matrix;
			matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			TestUtils::Matrix3x3_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);
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

			TestUtils::Matrix3x3_AreEqual(matrix1, 9.f, 11.f, 13.f, 15.f, 17.f, 19.f, 21.f, 23.f, 25.f);
		}

		TEST_METHOD(Operator_Minus_Equals)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };

			matrix1 -= matrix2;

			TestUtils::Matrix3x3_AreEqual(matrix1, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f);
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
			HD_Matrix3x3f matrix =
			{
				0.f, 1.f, 2.f,
				3.f, 4.f, 5.f,
				6.f, 7.f, 8.f
			};

			HD_Matrix3x3f transpose = matrix.GetTranspose();

			TestUtils::Matrix3x3_AreEqual(transpose,
				0.f, 3.f, 6.f,
				1.f, 4.f, 7.f,
				2.f, 5.f, 8.f
			);
		}

		TEST_METHOD(CreateRotationAroundX)
		{
			HD_Vector3f vector(1.f, 1.f, 1.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotationAroundX(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector3_AreEqual(vector, 1.f, -1.f, 1.f);
		}

		TEST_METHOD(CreateRotationAroundY)
		{
			HD_Vector3f vector(1.f, 1.f, 1.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotationAroundY(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector3_AreEqual(vector, 1.f, 1.f, -1.f);
		}

		TEST_METHOD(CreateRotationAroundZ)
		{
			HD_Vector3f vector(1.f, 1.f, 1.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotationAroundZ(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector3_AreEqual(vector, -1.f, 1.f, 1.f);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };
			HD_Matrix3x3f matrix3 = matrix1 + matrix2;

			TestUtils::Matrix3x3_AreEqual(matrix3, 9.f, 11.f, 13.f, 15.f, 17.f, 19.f, 21.f, 23.f, 25.f);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = { 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f };
			HD_Matrix3x3f matrix3 = matrix1 - matrix2;

			TestUtils::Matrix3x3_AreEqual(matrix3, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f);
		}

		TEST_METHOD(Operator_Multiplication)
		{
			HD_Matrix3x3f rotation90AroundX = HD_Matrix3x3f::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix3x3f rotation90AroundY = HD_Matrix3x3f::CreateRotationAroundY(F_PI_HALF);
			HD_Matrix3x3f rotation90AroundXAndRotation90AroundY = rotation90AroundX * rotation90AroundY;

			HD_Vector3f vector(1.f, 1.f, 1.f);
			vector *= rotation90AroundXAndRotation90AroundY;

			TestUtils::Vector3_AreEqual(vector, 1.f, -1.f, -1.f);
		}

		TEST_METHOD(Operator_Multiplication_Matrix_Scalar)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = matrix1 * 2.f;

			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f);
		}

		TEST_METHOD(Operator_Multiplication_Scalar_Matrix)
		{
			HD_Matrix3x3f matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f matrix2 = 2.f * matrix1;

			TestUtils::Matrix3x3_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f);
		}

		TEST_METHOD(Operator_Multiplication_Vector_Matrix)
		{
			HD_Vector3f vector1(1.f, 1.f, 1.f);
			HD_Vector3f vector2 = vector1 * HD_Matrix3x3f::CreateRotationAroundX(F_PI_HALF);

			TestUtils::Vector3_AreEqual(vector2, 1.f, -1.f, 1.f);
		}
	};
}
