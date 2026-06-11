#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector2.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Vector2_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector2f floatVector;
			TestUtils::Vector2_AreEqual(floatVector, 0.f, 0.f);

			HD_Vector2i intVector;
			TestUtils::Vector2_AreEqual(intVector, 0, 0);

			HD_Vector2ui unsignedIntVector;
			TestUtils::Vector2_AreEqual(unsignedIntVector, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			TestUtils::Vector2_AreEqual(floatVector, 1.f, 2.f);

			HD_Vector2i intVector(3, 4);
			TestUtils::Vector2_AreEqual(intVector, 3, 4);

			HD_Vector2ui unsignedIntVector(5u, 6u);
			TestUtils::Vector2_AreEqual(unsignedIntVector, 5u, 6u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(floatVector1);
			TestUtils::Vector2_AreEqual(floatVector2, 1.f, 2.f);

			HD_Vector2i intVector1(3, 4);
			HD_Vector2i intVector2(intVector1);
			TestUtils::Vector2_AreEqual(intVector2, 3, 4);

			HD_Vector2ui unsignedIntVector1(5u, 6u);
			HD_Vector2ui unsignedIntVector2(unsignedIntVector1);
			TestUtils::Vector2_AreEqual(unsignedIntVector2, 5u, 6u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector2f floatVector;
			floatVector.Set(1.f, 2.f);
			TestUtils::Vector2_AreEqual(floatVector, 1.f, 2.f);

			HD_Vector2i intVector;
			intVector.Set(3, 4);
			TestUtils::Vector2_AreEqual(intVector, 3, 4);

			HD_Vector2ui unsignedIntVector;
			unsignedIntVector.Set(5u, 6u);
			TestUtils::Vector2_AreEqual(unsignedIntVector, 5u, 6u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			f32 length = floatVector.Length();
			Assert::AreEqual(length, HD_Sqrt(2.f), FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			f32 floatLength2 = floatVector.Length2();
			Assert::AreEqual(floatLength2, 2.f, FLOAT_EQUAL_TOLERANCE);

			HD_Vector2i intVector(2, 2);
			s32 intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 8);

			HD_Vector2ui unsignedIntVector(3, 3);
			u32 unsignedintLength2 = unsignedIntVector.Length2();
			Assert::AreEqual(unsignedintLength2, 18u);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			floatVector.Normalize();
			f32 length = floatVector.Length();
			Assert::AreEqual(length, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			HD_Vector2f normalizedFloatVector = floatVector.GetNormalized();
			f32 floatVectorLength = floatVector.Length();
			f32 normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::AreEqual(floatVectorLength, HD_Sqrt(8.f), FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedFloatVectorLength, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Dot)
		{
			HD_Vector2f up(0.f, 1.f);
			HD_Vector2f upRight(1.f, 1.f);
			HD_Vector2f right(1.f, 0.f);
			HD_Vector2f downRight(1.f, -1.f);
			HD_Vector2f down(0.f, -1.f);
			HD_Vector2f downLeft(-1.f, -1.f);
			HD_Vector2f left(-1.f, 0.f);
			HD_Vector2f upLeft(-1.f, 1.f);

			upRight.Normalize();
			downRight.Normalize();
			downLeft.Normalize();
			upLeft.Normalize();

			f32 upDotUp = up.Dot(up);
			f32 upDotUpRight = up.Dot(upRight);
			f32 upDotRight = up.Dot(right);
			f32 upDotDownRight = up.Dot(downRight);
			f32 upDotDown = up.Dot(down);
			f32 upDotDownLeft = up.Dot(downLeft);
			f32 upDotLeft = up.Dot(left);
			f32 upDotUpLeft = up.Dot(upLeft);

			Assert::AreEqual(upDotUp, 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotUpRight, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRight, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDownRight, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDown, -1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDownLeft, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeft, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotUpLeft, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2;
			floatVector2 = floatVector1;
			TestUtils::Vector2_AreEqual(floatVector2, 1.f, 2.f);

			HD_Vector2i intVector1(3, 4);
			HD_Vector2i intVector2;
			intVector2 = intVector1;
			TestUtils::Vector2_AreEqual(intVector2, 3, 4);

			HD_Vector2ui unsignedIntVector1(5u, 6u);
			HD_Vector2ui unsignedIntVector2;
			unsignedIntVector2 = unsignedIntVector1;
			TestUtils::Vector2_AreEqual(unsignedIntVector2, 5u, 6u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 += floatVector2;
			TestUtils::Vector2_AreEqual(floatVector1, 4.f, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 += intVector2;
			TestUtils::Vector2_AreEqual(intVector1, 4, 6);

			HD_Vector2ui unsignedIntVector1(1u, 2u);
			HD_Vector2ui unsignedIntVector2(3u, 4u);
			unsignedIntVector1 += unsignedIntVector2;
			TestUtils::Vector2_AreEqual(unsignedIntVector1, 4u, 6u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 -= floatVector2;
			TestUtils::Vector2_AreEqual(floatVector1, -2.f, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 -= intVector2;
			TestUtils::Vector2_AreEqual(intVector1, -2, -2);

			HD_Vector2ui unsignedIntVector1(4u, 3u);
			HD_Vector2ui unsignedIntVector2(2u, 1u);
			unsignedIntVector1 -= unsignedIntVector2;
			TestUtils::Vector2_AreEqual(unsignedIntVector1, 2u, 2u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector *= 2.f;
			TestUtils::Vector2_AreEqual(floatVector, 2.f, 4.f);

			HD_Vector2i intVector(1, 2);
			intVector *= 2;
			TestUtils::Vector2_AreEqual(intVector, 2, 4);

			HD_Vector2ui unsignedIntVector(1u, 2u);
			unsignedIntVector *= 2u;
			TestUtils::Vector2_AreEqual(unsignedIntVector, 2u, 4u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector /= 2.f;
			TestUtils::Vector2_AreEqual(floatVector, 0.5f, 1.f);

			HD_Vector2i intVector(1, 2);
			intVector /= 2;
			TestUtils::Vector2_AreEqual(intVector, 0, 1);

			HD_Vector2ui unsignedIntVector(1u, 2u);
			unsignedIntVector /= 2u;
			TestUtils::Vector2_AreEqual(unsignedIntVector, 0u, 1u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatVectorResult = floatVector1 + floatVector2;
			TestUtils::Vector2_AreEqual(floatVectorResult, 4.f, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intVectorResult = intVector1 + intVector2;
			TestUtils::Vector2_AreEqual(intVectorResult, 4, 6);

			HD_Vector2ui unsignedIntVector1(1u, 2u);
			HD_Vector2ui unsignedIntVector2(3u, 4u);
			HD_Vector2ui unsignedIntVectorResult = unsignedIntVector1 + unsignedIntVector2;
			TestUtils::Vector2_AreEqual(unsignedIntVectorResult, 4u, 6u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatVectorResult = floatVector1 - floatVector2;
			TestUtils::Vector2_AreEqual(floatVectorResult, -2.f, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intVectorResult = intVector1 - intVector2;
			TestUtils::Vector2_AreEqual(intVectorResult, -2, -2);

			HD_Vector2ui unsignedIntVector1(4u, 3u);
			HD_Vector2ui unsignedIntVector2(2u, 1u);
			HD_Vector2ui unsignedIntVectorResult = unsignedIntVector1 - unsignedIntVector2;
			TestUtils::Vector2_AreEqual(unsignedIntVectorResult, 2u, 2u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatVectorResult = floatVector * 2.f;
			TestUtils::Vector2_AreEqual(floatVectorResult, 2.f, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intVectorResult = intVector * 2;
			TestUtils::Vector2_AreEqual(intVectorResult, 2, 4);

			HD_Vector2ui unsignedIntVector(1u, 2u);
			HD_Vector2ui unsignedIntVectorResult = unsignedIntVector * 2u;
			TestUtils::Vector2_AreEqual(unsignedIntVectorResult, 2u, 4u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatVectorResult = 2.f * floatVector;
			TestUtils::Vector2_AreEqual(floatVectorResult, 2.f, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intVectorResult = 2 * intVector;
			TestUtils::Vector2_AreEqual(intVectorResult, 2, 4);

			HD_Vector2ui unsignedIntVector(1u, 2u);
			HD_Vector2ui unsignedIntVectorResult = 2u * unsignedIntVector;
			TestUtils::Vector2_AreEqual(unsignedIntVectorResult, 2u, 4u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatVectorResult = floatVector / 2.f;
			TestUtils::Vector2_AreEqual(floatVectorResult, 0.5f, 1.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intVectorResult = intVector / 2;
			TestUtils::Vector2_AreEqual(intVectorResult, 0, 1);

			HD_Vector2ui unsignedIntVector(1u, 2u);
			HD_Vector2ui unsignedIntVectorResult = unsignedIntVector / 2u;
			TestUtils::Vector2_AreEqual(unsignedIntVectorResult, 0u, 1u);
		}
	};
}
