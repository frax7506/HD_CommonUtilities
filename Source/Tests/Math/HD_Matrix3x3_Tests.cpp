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
			TestUtils::Matrix3x3_AreEqual(matrix, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
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

			TestUtils::Matrix3x3_AreEqual(matrix2,
				0.f, 1.f, 2.f,
				4.f, 5.f, 6.f,
				8.f, 9.f, 10.f
			);
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

			TestUtils::Matrix3x3_AreEqual(matrix2,
				0.f, 1.f, 2.f,
				4.f, 5.f, 6.f,
				8.f, 9.f, 10.f
			);
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

			Assert::AreEqual(matrix(1, 1), 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 2), 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 3), 2.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 1), 3.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 2), 4.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 3), 5.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 1), 6.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 2), 7.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 3), 8.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Function_Call_Row_And_Col_Const)
		{
			const HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

			Assert::AreEqual(matrix(1, 1), 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 2), 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 3), 2.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 1), 3.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 2), 4.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 3), 5.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 1), 6.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 2), 7.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 3), 8.f, FLOAT_EQUAL_TOLERANCE);
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
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotation(F_PI_HALF);
			HD_Matrix3x3f translation = HD_Matrix3x3f::CreateTranslation(1.f, 1.f);

			HD_Matrix3x3f rotationAndTranslation = rotation;
			rotationAndTranslation *= translation;

			HD_Vector3f point2D(1.f, 1.f, 1.f);
			point2D *= rotationAndTranslation;

			TestUtils::Vector3_AreEqual(point2D, 0.f, 2.f, 1.f);
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

		TEST_METHOD(GetRightVector)
		{
			HD_Matrix3x3f identity = HD_Matrix3x3f::Identity;
			HD_Matrix3x3f rotated90 = HD_Matrix3x3f::CreateRotation(F_PI_HALF);

			HD_Vector2f identityRight = identity.GetRightVector();
			HD_Vector2f rotated90Right = rotated90.GetRightVector();

			TestUtils::Vector2_AreEqual(identityRight, 1.f, 0.f);
			TestUtils::Vector2_AreEqual(rotated90Right, 0.f, 1.f);
		}

		TEST_METHOD(GetUpVector)
		{
			HD_Matrix3x3f identity = HD_Matrix3x3f::Identity;
			HD_Matrix3x3f rotated90 = HD_Matrix3x3f::CreateRotation(F_PI_HALF);

			HD_Vector2f identityUp = identity.GetUpVector();
			HD_Vector2f rotated90Up = rotated90.GetUpVector();

			TestUtils::Vector2_AreEqual(identityUp, 0.f, 1.f);
			TestUtils::Vector2_AreEqual(rotated90Up, -1.f, 0.f);
		}

		TEST_METHOD(GetScaleInX)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::CreateScale(2.f, 1.f);
			f32 scaleInX = matrix.GetScaleInX();

			Assert::AreEqual(scaleInX, 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetScaleInY)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::CreateScale(1.f, 2.f);
			f32 scaleInY = matrix.GetScaleInY();

			Assert::AreEqual(scaleInY, 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetScaleInXY)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::CreateScale(2.f, 3.f);
			HD_Vector2f scaleInXY = matrix.GetScaleInXY();

			TestUtils::Vector2_AreEqual(scaleInXY, 2.f, 3.f);
		}

		TEST_METHOD(GetRotation)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::CreateRotation(F_PI / 4.f);
			f32 rotation = matrix.GetRotation();
			Assert::AreEqual(rotation, F_PI / 4.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPositionX)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::Identity;
			matrix *= HD_Matrix3x3f::CreateTranslation(2.f, 3.f);

			f32 positionX = matrix.GetPositionX();
			Assert::AreEqual(positionX, 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPositionY)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::Identity;
			matrix *= HD_Matrix3x3f::CreateTranslation(2.f, 3.f);

			f32 positionY = matrix.GetPositionY();
			Assert::AreEqual(positionY, 3.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPosition)
		{
			HD_Matrix3x3f matrix = HD_Matrix3x3f::Identity;
			matrix *= HD_Matrix3x3f::CreateTranslation(2.f, 3.f);

			HD_Vector2f position = matrix.GetPosition();
			TestUtils::Vector2_AreEqual(position, 2.f, 3.f);
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

		TEST_METHOD(GetFastInverse)
		{
			HD_Matrix3x3f scale = HD_Matrix3x3f::CreateScale(2.f, 3.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotation(F_PI_HALF);
			HD_Matrix3x3f translation = HD_Matrix3x3f::CreateTranslation(1.f, 1.f);

			HD_Matrix3x3f scaleRotationTranslation = scale * rotation * translation;
			HD_Matrix3x3f inverse = scaleRotationTranslation.GetFastInverse();
			HD_Matrix3x3f inversed = scaleRotationTranslation * inverse;

			Assert::IsTrue(inversed == HD_Matrix3x3f::Identity);
		}

		TEST_METHOD(Get2x2)
		{
			HD_Matrix3x3f matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
			HD_Matrix3x3f twoByTwo = matrix.Get2x2();
			TestUtils::Matrix3x3_AreEqual(twoByTwo, 0.f, 1.f, 0.f, 3.f, 4.f, 0.f, 0.f, 0.f, 1.f);
		}

		TEST_METHOD(CreateScale)
		{
			HD_Vector3f vector(1.f, 1.f, 0.f);
			vector *= HD_Matrix3x3f::CreateScale(2.f, 3.f);

			TestUtils::Vector3_AreEqual(vector, 2.f, 3.f, 0.f);
		}

		TEST_METHOD(CreateRotation)
		{
			HD_Vector3f vector(1.f, 1.f, 0.f);
			HD_Matrix3x3f rotation = HD_Matrix3x3f::CreateRotation(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector3_AreEqual(vector, -1.f, 1.f, 0.f);
		}

		TEST_METHOD(CreateTranslation)
		{
			HD_Matrix3x3f translation = HD_Matrix3x3f::CreateTranslation(1.f, 1.f);
			HD_Vector3f point(0.f, 0.f, 1.f);
			point *= translation;

			TestUtils::Vector3_AreEqual(point, 1.f, 1.f, 1.f);
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
			HD_Matrix3x3f rotation90 = HD_Matrix3x3f::CreateRotation(F_PI_HALF);
			HD_Matrix3x3f rotationMinus45 = HD_Matrix3x3f::CreateRotation(-1.f * (F_PI / 4.f));
			HD_Matrix3x3f rotation90AndRotationMinus45 = rotation90 * rotationMinus45;

			HD_Vector3f vector(1.f, 1.f, 0.f);
			vector *= rotation90AndRotationMinus45;

			TestUtils::Vector3_AreEqual(vector, 0.f, F_SQRT_TWO, 0.f);
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
			HD_Vector3f vector1(1.f, 1.f, 0.f);
			HD_Vector3f vector2 = vector1 * HD_Matrix3x3f::CreateRotation(F_PI_HALF);

			TestUtils::Vector3_AreEqual(vector2, -1.f, 1.f, 0.f);
		}
	};
}
