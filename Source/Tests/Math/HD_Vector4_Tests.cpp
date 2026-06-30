#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector4.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Vector4_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector4f floatVector;
			TestUtils::Vector4_AreEqual(floatVector, 0.f, 0.f, 0.f, 0.f);

			HD_Vector4i intVector;
			TestUtils::Vector4_AreEqual(intVector, 0, 0, 0, 0);

			HD_Vector4ui unsignedIntVector;
			TestUtils::Vector4_AreEqual(unsignedIntVector, 0u, 0u, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z_And_W)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			TestUtils::Vector4_AreEqual(floatVector, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4i intVector(5, 6, 7, 8);
			TestUtils::Vector4_AreEqual(intVector, 5, 6, 7, 8);

			HD_Vector4ui unsignedIntVector(9u, 10u, 11u, 12u);
			TestUtils::Vector4_AreEqual(unsignedIntVector, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(floatVector1);
			TestUtils::Vector4_AreEqual(floatVector2, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4i intVector1(5, 6, 7, 8);
			HD_Vector4i intVector2(intVector1);
			TestUtils::Vector4_AreEqual(intVector2, 5, 6, 7, 8);

			HD_Vector4ui unsignedIntVector1(9u, 10u, 11u, 12u);
			HD_Vector4ui unsignedIntVector2(unsignedIntVector1);
			TestUtils::Vector4_AreEqual(unsignedIntVector2, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector4f floatVector;
			floatVector.Set(1.f, 2.f, 3.f, 4.f);
			TestUtils::Vector4_AreEqual(floatVector, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4i intVector;
			intVector.Set(5, 6, 7, 8);
			TestUtils::Vector4_AreEqual(intVector, 5, 6, 7, 8);

			HD_Vector4ui unsignedIntVector;
			unsignedIntVector.Set(9u, 10u, 11u, 12u);
			TestUtils::Vector4_AreEqual(unsignedIntVector, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector4f floatVector(1.f, 1.f, 1.f, 1.f);
			f32 length = floatVector.Length();
			Assert::AreEqual(length, 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector4f floatVector(1.f, 1.f, 1.f, 1.f);
			f32 floatLength2 = floatVector.Length2();
			Assert::AreEqual(floatLength2, 4.f, FLOAT_EQUAL_TOLERANCE);

			HD_Vector4i intVector(2, 2, 2, 2);
			s32 intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 16);

			HD_Vector4ui unsignedIntVector(3u, 3u, 3u, 3u);
			u32 unsignedIntLength2 = unsignedIntVector.Length2();
			Assert::AreEqual(unsignedIntLength2, 36u);
		}

		TEST_METHOD(SetLength)
		{
			HD_Vector4f floatVector(1.f, 1.f, 1.f, 1.f);

			floatVector.SetLength(1.f);
			Assert::AreEqual(floatVector.Length(), 1.f, FLOAT_EQUAL_TOLERANCE);

			floatVector.SetLength(2.f);
			Assert::AreEqual(floatVector.Length(), 2.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector4f floatVector(2.f, 2.f, 2.f, 2.f);
			floatVector.Normalize();
			f32 length = floatVector.Length();
			Assert::AreEqual(length, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector4f floatVector(2.f, 2.f, 2.f, 2.f);
			HD_Vector4f normalizedFloatVector = floatVector.GetNormalized();
			f32 floatVectorLength = floatVector.Length();
			f32 normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::AreEqual(floatVectorLength, 4.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedFloatVectorLength, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2;
			floatVector2 = floatVector1;
			TestUtils::Vector4_AreEqual(floatVector2, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4i intVector1(5, 6, 7, 8);
			HD_Vector4i intVector2;
			intVector2 = intVector1;
			TestUtils::Vector4_AreEqual(intVector2, 5, 6, 7, 8);

			HD_Vector4ui unsignedIntVector1(9u, 10u, 11u, 12u);
			HD_Vector4ui unsignedIntVector2;
			unsignedIntVector2 = unsignedIntVector1;
			TestUtils::Vector4_AreEqual(unsignedIntVector2, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			floatVector1 += floatVector2;
			TestUtils::Vector4_AreEqual(floatVector1, 6.f, 8.f, 10.f, 12.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			intVector1 += intVector2;
			TestUtils::Vector4_AreEqual(intVector1, 6, 8, 10, 12);

			HD_Vector4ui unsignedIntVector1(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedIntVector2(5u, 6u, 7u, 8u);
			unsignedIntVector1 += unsignedIntVector2;
			TestUtils::Vector4_AreEqual(unsignedIntVector1, 6u, 8u, 10u, 12u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			floatVector1 -= floatVector2;
			TestUtils::Vector4_AreEqual(floatVector1, -4.f, -4.f, -4.f, -4.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			intVector1 -= intVector2;
			TestUtils::Vector4_AreEqual(intVector1, -4, -4, -4, -4);

			HD_Vector4ui unsignedIntVector1(5u, 6u, 7u, 8u);
			HD_Vector4ui unsignedIntVector2(1u, 2u, 3u, 4u);
			unsignedIntVector1 -= unsignedIntVector2;
			TestUtils::Vector4_AreEqual(unsignedIntVector1, 4u, 4u, 4u, 4u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			floatVector *= 2.f;
			TestUtils::Vector4_AreEqual(floatVector, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			intVector *= 2;
			TestUtils::Vector4_AreEqual(intVector, 2, 4, 6, 8);

			HD_Vector4ui unsignedIntVector(1u, 2u, 3u, 4u);
			unsignedIntVector *= 2u;
			TestUtils::Vector4_AreEqual(unsignedIntVector, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			floatVector /= 2.f;
			TestUtils::Vector4_AreEqual(floatVector, 0.5f, 1.f, 1.5f, 2.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			intVector /= 2;
			TestUtils::Vector4_AreEqual(intVector, 0, 1, 1, 2);

			HD_Vector4ui unsignedIntVector(1u, 2u, 3u, 4u);
			unsignedIntVector /= 2u;
			TestUtils::Vector4_AreEqual(unsignedIntVector, 0u, 1u, 1u, 2u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4f floatVectorResult = floatVector1 + floatVector2;
			TestUtils::Vector4_AreEqual(floatVectorResult, 6.f, 8.f, 10.f, 12.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			HD_Vector4i intVectorResult = intVector1 + intVector2;
			TestUtils::Vector4_AreEqual(intVectorResult, 6, 8, 10, 12);

			HD_Vector4ui unsignedIntVector1(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedIntVector2(5u, 6u, 7u, 8u);
			HD_Vector4ui unsignedIntVectorResult = unsignedIntVector1 + unsignedIntVector2;
			TestUtils::Vector4_AreEqual(unsignedIntVectorResult, 6u, 8u, 10u, 12u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4f floatVectorResult = floatVector1 - floatVector2;
			TestUtils::Vector4_AreEqual(floatVectorResult, -4.f, -4.f, -4.f, -4.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			HD_Vector4i intVectorResult = intVector1 - intVector2;
			TestUtils::Vector4_AreEqual(intVectorResult, -4, -4, -4, -4);

			HD_Vector4ui unsignedIntVector1(5u, 6u, 7u, 8u);
			HD_Vector4ui unsignedIntVector2(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedIntVectorResult = unsignedIntVector1 - unsignedIntVector2;
			TestUtils::Vector4_AreEqual(unsignedIntVectorResult, 4u, 4u, 4u, 4u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = floatVector * 2.f;
			TestUtils::Vector4_AreEqual(floatVectorResult, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = intVector * 2;
			TestUtils::Vector4_AreEqual(intVectorResult, 2, 4, 6, 8);

			HD_Vector4ui unsignedintVector(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedintVectorResult = unsignedintVector * 2u;
			TestUtils::Vector4_AreEqual(unsignedintVectorResult, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = 2.f * floatVector;
			TestUtils::Vector4_AreEqual(floatVectorResult, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = 2 * intVector;
			TestUtils::Vector4_AreEqual(intVectorResult, 2, 4, 6, 8);

			HD_Vector4ui unsignedIntVector(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedIntVectorResult = 2u * unsignedIntVector;
			TestUtils::Vector4_AreEqual(unsignedIntVectorResult, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = floatVector / 2.f;
			TestUtils::Vector4_AreEqual(floatVectorResult, 0.5f, 1.f, 1.5f, 2.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = intVector / 2;
			TestUtils::Vector4_AreEqual(intVectorResult, 0, 1, 1, 2);

			HD_Vector4ui unsignedIntVector(1u, 2u, 3u, 4u);
			HD_Vector4ui unsignedIntVectorResult = unsignedIntVector / 2u;
			TestUtils::Vector4_AreEqual(unsignedIntVectorResult, 0u, 1u, 1u, 2u);
		}
	};
}
