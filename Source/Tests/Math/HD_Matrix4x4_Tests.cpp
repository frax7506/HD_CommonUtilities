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
			HD_Matrix4x4_f32 matrix;
			TestUtils::Matrix4x4_AreEqual(matrix, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2(matrix1);
			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Constructor_Copy_Matrix3x3)
		{
			HD_Matrix3x3_f32 matrix1 =
			{
				0.f, 1.f, 2.f,
				3.f, 4.f, 5.f,
				6.f, 7.f, 8.f
			};

			HD_Matrix4x4_f32 matrix2(matrix1);

			TestUtils::Matrix4x4_AreEqual(matrix2,
				0.f, 1.f, 2.f, 0.f,
				3.f, 4.f, 5.f, 0.f,
				6.f, 7.f, 8.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		TEST_METHOD(Constructor_InitializerList)
		{
			HD_Matrix4x4_f32 matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			TestUtils::Matrix4x4_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_Assignment_Copy)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };

			HD_Matrix4x4_f32 matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_Assignment_Matrix3x3)
		{
			HD_Matrix3x3_f32 matrix1 =
			{
				0.f, 1.f, 2.f,
				3.f, 4.f, 5.f,
				6.f, 7.f, 8.f
			};

			HD_Matrix4x4_f32 matrix2;
			matrix2 = matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2,
				0.f, 1.f, 2.f, 0.f,
				3.f, 4.f, 5.f, 0.f,
				6.f, 7.f, 8.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			);
		}

		TEST_METHOD(Operator_Assignment_InitializerList)
		{
			HD_Matrix4x4_f32 matrix;
			matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			TestUtils::Matrix4x4_AreEqual(matrix, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			matrix1 += matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix1, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			matrix1 -= matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix1, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Matrix4x4_f32 rotation = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix4x4_f32 translation = HD_Matrix4x4_f32::CreateTranslation(1.f, 1.f, 1.f);

			HD_Matrix4x4_f32 rotationAndTranslation = rotation;
			rotationAndTranslation *= translation;

			HD_Vector4_f32 point3D(1.f, 1.f, 1.f, 1.f);
			point3D *= rotationAndTranslation;

			TestUtils::Vector4_AreEqual(point3D, 2.f, 0.f, 2.f, 1.f);
		}

		TEST_METHOD(SetScaleInX)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInX(2.f);
			f32 scaleInX = matrix.GetScaleInX();

			Assert::AreEqual(scaleInX, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(SetScaleInY)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInY(2.f);
			f32 scaleInX = matrix.GetScaleInY();

			Assert::AreEqual(scaleInX, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(SetScaleInZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInZ(2.f);
			f32 scaleInX = matrix.GetScaleInZ();

			Assert::AreEqual(scaleInX, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(SetRotationAroundX)
		{
			{
				HD_Matrix4x4_f32 matrix;
				matrix.SetRotationAroundX(F_PI / 4.f);
				f32 rotationAroundX = matrix.GetRotationAroundX();

				Assert::AreEqual(rotationAroundX, F_PI / 4.f, F32_EQUAL_TOLERANCE);
			}

			{
				HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateTranslation(1.f, 1.f, 1.f);
				matrix.SetRotationAroundX(F_PI / 4.f);
				f32 rotationAroundX = matrix.GetRotationAroundX();
				Assert::AreEqual(rotationAroundX, F_PI / 4.f, F32_EQUAL_TOLERANCE);

				HD_Vector3_f32 position = matrix.GetPosition();
				TestUtils::Vector3_AreEqual(position, 1.f, 1.f, 1.f);
			}
		}

		TEST_METHOD(SetRotationAroundY)
		{
			{
				HD_Matrix4x4_f32 matrix;
				matrix.SetRotationAroundY(F_PI / 4.f);
				f32 rotationAroundY = matrix.GetRotationAroundY();

				Assert::AreEqual(rotationAroundY, F_PI / 4.f, F32_EQUAL_TOLERANCE);
			}

			{
				HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateTranslation(1.f, 1.f, 1.f);
				matrix.SetRotationAroundY(F_PI / 4.f);
				f32 rotationAroundY = matrix.GetRotationAroundY();
				Assert::AreEqual(rotationAroundY, F_PI / 4.f, F32_EQUAL_TOLERANCE);

				HD_Vector3_f32 position = matrix.GetPosition();
				TestUtils::Vector3_AreEqual(position, 1.f, 1.f, 1.f);
			}
		}

		TEST_METHOD(SetRotationAroundZ)
		{
			{
				HD_Matrix4x4_f32 matrix;
				matrix.SetRotationAroundZ(F_PI / 4.f);
				f32 rotationAroundZ = matrix.GetRotationAroundZ();

				Assert::AreEqual(rotationAroundZ, F_PI / 4.f, F32_EQUAL_TOLERANCE);
			}

			{
				HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateTranslation(1.f, 1.f, 1.f);
				matrix.SetRotationAroundZ(F_PI / 4.f);
				f32 rotationAroundZ = matrix.GetRotationAroundZ();
				Assert::AreEqual(rotationAroundZ, F_PI / 4.f, F32_EQUAL_TOLERANCE);

				HD_Vector3_f32 position = matrix.GetPosition();
				TestUtils::Vector3_AreEqual(position, 1.f, 1.f, 1.f);
			}
		}

		TEST_METHOD(SetPositionX)
		{
			HD_Matrix4x4_f32 matrix;
			matrix.SetPositionX(2.f);

			Assert::AreEqual(matrix.GetPositionX(), 2.f);
		}

		TEST_METHOD(SetPositionY)
		{
			HD_Matrix4x4_f32 matrix;
			matrix.SetPositionY(2.f);

			Assert::AreEqual(matrix.GetPositionY(), 2.f);
		}

		TEST_METHOD(SetPositionZ)
		{
			HD_Matrix4x4_f32 matrix;
			matrix.SetPositionZ(2.f);

			Assert::AreEqual(matrix.GetPositionZ(), 2.f);
		}

		TEST_METHOD(SetPosition)
		{
			HD_Matrix4x4_f32 matrix;
			matrix.SetPosition({ 2.f, 3.f, 4.f });

			HD_Vector3_f32 position = matrix.GetPosition();
			TestUtils::Vector3_AreEqual(position, 2.f, 3.f, 4.f);
		}

		TEST_METHOD(Operator_Function_Call_Row_And_Col)
		{
			HD_Matrix4x4_f32 matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };

			Assert::AreEqual(matrix(1, 1), 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 2), 1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 3), 2.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 4), 3.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 1), 4.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 2), 5.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 3), 6.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 4), 7.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 1), 8.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 2), 9.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 3), 10.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 4), 11.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 1), 12.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 2), 13.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 3), 14.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 4), 15.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Function_Call_Row_And_Col_Const)
		{
			HD_Matrix4x4_f32 matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };

			Assert::AreEqual(matrix(1, 1), 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 2), 1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 3), 2.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(1, 4), 3.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 1), 4.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 2), 5.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 3), 6.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(2, 4), 7.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 1), 8.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 2), 9.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 3), 10.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(3, 4), 11.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 1), 12.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 2), 13.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 3), 14.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(matrix(4, 4), 15.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetRightVector)
		{
			HD_Matrix4x4_f32 identity = HD_Matrix4x4_f32::Identity;
			HD_Matrix4x4_f32 rotated90InY = HD_Matrix4x4_f32::CreateRotationAroundY(F_PI_HALF);

			HD_Vector3_f32 identityRight = identity.GetRightVector();
			HD_Vector3_f32 rotated90InYRight = rotated90InY.GetRightVector();

			TestUtils::Vector3_AreEqual(identityRight, 1.f, 0.f, 0.f);
			TestUtils::Vector3_AreEqual(rotated90InYRight, 0.f, 0.f, -1.f);
		}

		TEST_METHOD(GetUpVector)
		{
			HD_Matrix4x4_f32 identity = HD_Matrix4x4_f32::Identity;
			HD_Matrix4x4_f32 rotated90InZ = HD_Matrix4x4_f32::CreateRotationAroundZ(F_PI_HALF);

			HD_Vector3_f32 identityUp = identity.GetUpVector();
			HD_Vector3_f32 rotated90InZUp = rotated90InZ.GetUpVector();

			TestUtils::Vector3_AreEqual(identityUp, 0.f, 1.f, 0.f);
			TestUtils::Vector3_AreEqual(rotated90InZUp, -1.f, 0.f, 0.f);
		}

		TEST_METHOD(GetForwardVector)
		{
			HD_Matrix4x4_f32 identity = HD_Matrix4x4_f32::Identity;
			HD_Matrix4x4_f32 rotated90InX = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);

			HD_Vector3_f32 identityUp = identity.GetUpVector();
			HD_Vector3_f32 rotated90InXUp = rotated90InX.GetUpVector();

			TestUtils::Vector3_AreEqual(identityUp, 0.f, 1.f, 0.f);
			TestUtils::Vector3_AreEqual(rotated90InXUp, 0.f, 0.f, 1.f);
		}

		TEST_METHOD(GetScaleInX)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInX(2.f);
			f32 scaleInX = matrix.GetScaleInX();

			Assert::AreEqual(scaleInX, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetScaleInY)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInY(2.f);
			f32 scaleInY = matrix.GetScaleInY();

			Assert::AreEqual(scaleInY, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetScaleInZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInZ(2.f);
			f32 scaleInZ = matrix.GetScaleInZ();

			Assert::AreEqual(scaleInZ, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetScaleInXYZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix.SetScaleInX(2.f);
			matrix.SetScaleInY(3.f);
			matrix.SetScaleInZ(4.f);
			HD_Vector3_f32 scaleInXYZ = matrix.GetScaleInXYZ();

			TestUtils::Vector3_AreEqual(scaleInXYZ, 2.f, 3.f, 4.f);
		}

		TEST_METHOD(GetRotationAroundX)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI / 4.f);
			f32 rotation = matrix.GetRotationAroundX();
			Assert::AreEqual(rotation, F_PI / 4.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetRotationAroundY)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateRotationAroundY(F_PI / 4.f);
			f32 rotation = matrix.GetRotationAroundY();
			Assert::AreEqual(rotation, F_PI / 4.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetRotationAroundZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::CreateRotationAroundZ(F_PI / 4.f);
			f32 rotation = matrix.GetRotationAroundZ();
			Assert::AreEqual(rotation, F_PI / 4.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetRotationInXYZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateRotationAroundX(F_PI / 4.f);
			matrix *= HD_Matrix4x4_f32::CreateRotationAroundY(F_PI / 4.f);

			HD_Vector3_f32 rotation = matrix.GetRotationInXYZ();
			TestUtils::Vector3_AreEqual(rotation, F_PI / 4.f, F_PI / 4.f, 0.f);
		}

		TEST_METHOD(GetRotationInHPB)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateRotationAroundX(F_PI / 4.f);
			matrix *= HD_Matrix4x4_f32::CreateRotationAroundY(F_PI / 4.f);

			HD_Vector3_f32 rotation = matrix.GetRotationInHPB();
			TestUtils::Vector3_AreEqual(rotation, F_PI / 4.f, F_PI / 4.f, 0.f);
		}

		TEST_METHOD(GetPositionX)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateTranslation(2.f, 3.f, 4.f);

			f32 positionX = matrix.GetPositionX();
			Assert::AreEqual(positionX, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPositionY)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateTranslation(2.f, 3.f, 4.f);

			f32 positionY = matrix.GetPositionY();
			Assert::AreEqual(positionY, 3.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPositionZ)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateTranslation(2.f, 3.f, 4.f);

			f32 positionZ = matrix.GetPositionZ();
			Assert::AreEqual(positionZ, 4.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetPosition)
		{
			HD_Matrix4x4_f32 matrix = HD_Matrix4x4_f32::Identity;
			matrix *= HD_Matrix4x4_f32::CreateTranslation(2.f, 3.f, 4.f);

			HD_Vector3_f32 position = matrix.GetPosition();
			TestUtils::Vector3_AreEqual(position, 2.f, 3.f, 4.f);
		}

		TEST_METHOD(GetTranspose)
		{
			HD_Matrix4x4_f32 matrix =
			{
				0.f, 1.f, 2.f, 3.f,
				4.f, 5.f, 6.f, 7.f,
				8.f, 9.f, 10.f, 11.f,
				12.f, 13.f, 14.f, 15.f
			};

			HD_Matrix4x4_f32 transpose = matrix.GetTranspose();

			TestUtils::Matrix4x4_AreEqual(transpose,
				0.f, 4.f, 8.f, 12.f,
				1.f, 5.f, 9.f, 13.f,
				2.f, 6.f, 10.f, 14.f,
				3.f, 7.f, 11.f, 15.f
			);
		}

		TEST_METHOD(GetFastInverse)
		{
			HD_Matrix4x4_f32 scale = HD_Matrix4x4_f32::CreateScale(2.f, 3.f, 4.f);
			HD_Matrix4x4_f32 rotation = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix4x4_f32 translation = HD_Matrix4x4_f32::CreateTranslation(1.f, 1.f, 1.f);

			HD_Matrix4x4_f32 scaleRotationTranslation = scale * rotation * translation;
			HD_Matrix4x4_f32 inverse = scaleRotationTranslation.GetFastInverse();
			HD_Matrix4x4_f32 inversed = scaleRotationTranslation * inverse;

			Assert::IsTrue(inversed == HD_Matrix4x4_f32::Identity);
		}

		TEST_METHOD(Get3x3)
		{
			HD_Matrix4x4_f32 matrix = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 threeByThree = matrix.Get3x3();
			TestUtils::Matrix4x4_AreEqual(threeByThree, 0.f, 1.f, 2.f, 0.f, 4.f, 5.f, 6.f, 0.f, 8.f, 9.f, 10.f, 0.f, 0.f, 0.f, 0.f, 1.f);
		}

		TEST_METHOD(CreateScale)
		{
			HD_Vector4_f32 vector(1.f, 1.f, 1.f, 0.f);
			vector *= HD_Matrix4x4_f32::CreateScale(2.f, 3.f, 4.f);

			TestUtils::Vector4_AreEqual(vector, 2.f, 3.f, 4.f, 0.f);
		}

		TEST_METHOD(CreateRotationAroundX)
		{
			HD_Vector4_f32 vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4_f32 rotation = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, 1.f, -1.f, 1.f, 0.f);
		}

		TEST_METHOD(CreateRotationAroundY)
		{
			HD_Vector4_f32 vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4_f32 rotation = HD_Matrix4x4_f32::CreateRotationAroundY(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, 1.f, 1.f, -1.f, 0.f);
		}

		TEST_METHOD(CreateRotationAroundZ)
		{
			HD_Vector4_f32 vector(1.f, 1.f, 1.f, 0.f);
			HD_Matrix4x4_f32 rotation = HD_Matrix4x4_f32::CreateRotationAroundZ(F_PI_HALF);

			vector *= rotation;

			TestUtils::Vector4_AreEqual(vector, -1.f, 1.f, 1.f, 0.f);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };
			HD_Matrix4x4_f32 matrix3 = matrix1 + matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix3, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };
			HD_Matrix4x4_f32 matrix3 = matrix1 - matrix2;

			TestUtils::Matrix4x4_AreEqual(matrix3, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f);
		}

		TEST_METHOD(Operator_Multiplication)
		{
			HD_Matrix4x4_f32 rotation90AroundX = HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);
			HD_Matrix4x4_f32 rotation90AroundY = HD_Matrix4x4_f32::CreateRotationAroundY(F_PI_HALF);
			HD_Matrix4x4_f32 rotation90AroundXAndRotation90AroundY = rotation90AroundX * rotation90AroundY;

			HD_Vector4_f32 vector(1.f, 1.f, 1.f, 0.f);
			vector *= rotation90AroundXAndRotation90AroundY;

			TestUtils::Vector4_AreEqual(vector, 1.f, -1.f, -1.f, 0.f);
		}

		TEST_METHOD(Operator_Multiplication_Matrix_Scalar)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = matrix1 * 2.f;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f);
		}

		TEST_METHOD(Operator_Multiplication_Scalar_Matrix)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = 2.f * matrix1;

			TestUtils::Matrix4x4_AreEqual(matrix2, 0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f);
		}

		TEST_METHOD(Operator_Multiplication_Vector_Matrix)
		{
			HD_Vector4_f32 vector1(1.f, 1.f, 1.f, 0.f);
			HD_Vector4_f32 vector2 = vector1 * HD_Matrix4x4_f32::CreateRotationAroundX(F_PI_HALF);

			TestUtils::Vector4_AreEqual(vector2, 1.f, -1.f, 1.f, 0.f);
		}

		TEST_METHOD(Operator_Equals)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix3 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			Assert::IsTrue(matrix1 == matrix2);
			Assert::IsFalse(matrix1 == matrix3);
		}

		TEST_METHOD(Operator_Not_Equals)
		{
			HD_Matrix4x4_f32 matrix1 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix2 = { 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f };
			HD_Matrix4x4_f32 matrix3 = { 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f };

			Assert::IsFalse(matrix1 != matrix2);
			Assert::IsTrue(matrix1 != matrix3);
		}
	};
}
