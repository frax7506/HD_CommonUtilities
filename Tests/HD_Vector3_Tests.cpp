#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector3.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Vector3_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector3f floatVector;
			TestUtils::Vector3_AreEqual(floatVector, 0.f, 0.f, 0.f);

			HD_Vector3i intVector;
			TestUtils::Vector3_AreEqual(intVector, 0, 0, 0);

			HD_Vector3ui unsignedIntVector;
			TestUtils::Vector3_AreEqual(unsignedIntVector, 0u, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			TestUtils::Vector3_AreEqual(floatVector, 1.f, 2.f, 3.f);

			HD_Vector3i intVector(4, 5, 6);
			TestUtils::Vector3_AreEqual(intVector, 4, 5, 6);

			HD_Vector3ui unsignedIntVector(7u, 8u, 9u);
			TestUtils::Vector3_AreEqual(unsignedIntVector, 7u, 8u, 9u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(floatVector1);
			TestUtils::Vector3_AreEqual(floatVector2, 1.f, 2.f, 3.f);

			HD_Vector3i intVector1(4, 5, 6);
			HD_Vector3i intVector2(intVector1);
			TestUtils::Vector3_AreEqual(intVector2, 4, 5, 6);

			HD_Vector3ui unsignedIntVector1(7u, 8u, 9u);
			HD_Vector3ui unsignedIntVector2(unsignedIntVector1);
			TestUtils::Vector3_AreEqual(unsignedIntVector2, 7u, 8u, 9u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector3f floatVector;
			floatVector.Set(1.f, 2.f, 3.f);
			TestUtils::Vector3_AreEqual(floatVector, 1.f, 2.f, 3.f);

			HD_Vector3i intVector;
			intVector.Set(4, 5, 6);
			TestUtils::Vector3_AreEqual(intVector, 4, 5, 6);

			HD_Vector3ui unsignedIntVector;
			unsignedIntVector.Set(7u, 8u, 9u);
			TestUtils::Vector3_AreEqual(unsignedIntVector, 7u, 8u, 9u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector3f floatVector(1.f, 1.f, 1.f);
			f32 length = floatVector.Length();
			Assert::AreEqual(length, HD_Sqrt(3.f), FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector3f floatVector(1.f, 1.f, 1.f);
			f32 floatLength2 = floatVector.Length2();
			Assert::AreEqual(floatLength2, 3.f, FLOAT_EQUAL_TOLERANCE);

			HD_Vector3i intVector(2, 2, 2);
			s32 intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 12);

			HD_Vector3ui unsignedIntVector(3u, 3u, 3u);
			u32 unsignedIntLength2 = unsignedIntVector.Length2();
			Assert::AreEqual(unsignedIntLength2, 27u);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			floatVector.Normalize();
			f32 length = floatVector.Length();
			Assert::AreEqual(length, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			HD_Vector3f normalizedFloatVector = floatVector.GetNormalized();
			f32 floatVectorLength = floatVector.Length();
			f32 normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::AreEqual(floatVectorLength, HD_Sqrt(12.f), FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedFloatVectorLength, 1.f, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Dot)
		{
			HD_Vector3f leftUpBack(-1.f, 1.f, -1.f);
			HD_Vector3f centerUpBack(0.f, 1.f, -1.f);
			HD_Vector3f rightUpBack(1.f, 1.f, -1.f);
			HD_Vector3f leftCenterBack(-1.f, 0.f, -1.f);
			HD_Vector3f centerCenterBack(0.f, 0.f, -1.f);
			HD_Vector3f rightCenterBack(1.f, 0.f, -1.f);
			HD_Vector3f leftDownBack(-1.f, -1.f, -1.f);
			HD_Vector3f centerDownBack(0.f, -1.f, -1.f);
			HD_Vector3f rightDownBack(1.f, -1.f, -1.f);

			HD_Vector3f leftUpCenter(-1.f, 1.f, 0.f);
			HD_Vector3f centerUpCenter(0.f, 1.f, 0.f);
			HD_Vector3f rightUpCenter(1.f, 1.f, 0.f);
			HD_Vector3f leftCenterCenter(-1.f, 0.f, 0.f);
			HD_Vector3f centerCenterCenter(0.f, 0.f, 0.f);
			HD_Vector3f rightCenterCenter(1.f, 0.f, 0.f);
			HD_Vector3f leftDownCenter(-1.f, -1.f, 0.f);
			HD_Vector3f centerDownCenter(0.f, -1.f, 0.f);
			HD_Vector3f rightDownCenter(1.f, -1.f, 0.f);

			HD_Vector3f leftUpForward(-1.f, 1.f, 1.f);
			HD_Vector3f centerUpForward(0.f, 1.f, 1.f);
			HD_Vector3f rightUpForward(1.f, 1.f, 1.f);
			HD_Vector3f leftCenterForward(-1.f, 0.f, 1.f);
			HD_Vector3f centerCenterForward(0.f, 0.f, 1.f);
			HD_Vector3f rightCenterForward(1.f, 0.f, 1.f);
			HD_Vector3f leftDownForward(-1.f, -1.f, 1.f);
			HD_Vector3f centerDownForward(0.f, -1.f, 1.f);
			HD_Vector3f rightDownForward(1.f, -1.f, 1.f);

			leftUpBack.Normalize();
			centerUpBack.Normalize();
			rightUpBack.Normalize();
			leftCenterBack.Normalize();
			rightCenterBack.Normalize();
			leftDownBack.Normalize();
			centerDownBack.Normalize();
			rightDownBack.Normalize();

			leftUpCenter.Normalize();
			rightUpCenter.Normalize();
			leftDownCenter.Normalize();
			rightDownCenter.Normalize();

			leftUpForward.Normalize();
			centerUpForward.Normalize();
			rightUpForward.Normalize();
			leftCenterForward.Normalize();
			rightCenterForward.Normalize();
			leftDownForward.Normalize();
			centerDownForward.Normalize();
			rightDownForward.Normalize();

			HD_Vector3f up(0.f, 1.f, 0.f);

			f32 upDotLeftUpBack = up.Dot(leftUpBack);
			f32 upDotCenterUpBack = up.Dot(centerUpBack);
			f32 upDotRightUpBack = up.Dot(rightUpBack);
			f32 upDotLeftCenterBack = up.Dot(leftCenterBack);
			f32 upDotCenterCenterBack = up.Dot(centerCenterBack);
			f32 upDotRightCenterBack = up.Dot(rightCenterBack);
			f32 upDotLeftDownBack = up.Dot(leftDownBack);
			f32 upDotCenterDownBack = up.Dot(centerDownBack);
			f32 upDotRightDownBack = up.Dot(rightDownBack);

			f32 upDotLeftUpCenter = up.Dot(leftUpCenter);
			f32 upDotCenterUpCenter = up.Dot(centerUpCenter);
			f32 upDotRightUpCenter = up.Dot(rightUpCenter);
			f32 upDotLeftCenterCenter = up.Dot(leftCenterCenter);
			f32 upDotCenterCenterCenter = up.Dot(centerCenterCenter);
			f32 upDotRightCenterCenter = up.Dot(rightCenterCenter);
			f32 upDotLeftDownCenter = up.Dot(leftDownCenter);
			f32 upDotCenterDownCenter = up.Dot(centerDownCenter);
			f32 upDotRightDownCenter = up.Dot(rightDownCenter);

			f32 upDotLeftUpForward = up.Dot(leftUpForward);
			f32 upDotCenterUpForward = up.Dot(centerUpForward);
			f32 upDotRightUpForward = up.Dot(rightUpForward);
			f32 upDotLeftCenterForward = up.Dot(leftCenterForward);
			f32 upDotCenterCenterForward = up.Dot(centerCenterForward);
			f32 upDotRightCenterForward = up.Dot(rightCenterForward);
			f32 upDotLeftDownForward = up.Dot(leftDownForward);
			f32 upDotCenterDownForward = up.Dot(centerDownForward);
			f32 upDotRightDownForward = up.Dot(rightDownForward);

			f32 cornerDotValue = HD_Sin(HD_ArcTan(F_ONE_OVER_SQRT_TWO));

			Assert::AreEqual(upDotLeftUpBack, cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpBack, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpBack, cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterBack, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterBack, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterBack, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownBack, -1.f * cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownBack, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownBack, -1.f * cornerDotValue, FLOAT_EQUAL_TOLERANCE);

			Assert::AreEqual(upDotLeftUpCenter, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpCenter, 1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpCenter, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterCenter, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterCenter, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterCenter, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownCenter, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownCenter, -1.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownCenter, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);

			Assert::AreEqual(upDotLeftUpForward, cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpForward, F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpForward, cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterForward, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterForward, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterForward, 0.f, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownForward, -1.f * cornerDotValue, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownForward, -1.f * F_ONE_OVER_SQRT_TWO, FLOAT_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownForward, -1.f * cornerDotValue, FLOAT_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Cross)
		{
			HD_Vector3f centerForward(0.f, 0.f, 1.f);
			HD_Vector3f rightForward(1.f, 0.f, 1.f);
			HD_Vector3f rightCenter(1.f, 0.f, 0.f);
			HD_Vector3f rightBack(1.f, 0.f, -1.f);
			HD_Vector3f centerBack(0.f, 0.f, -1.f);
			HD_Vector3f leftBack(-1.f, 0.f, -1.f);
			HD_Vector3f leftCenter(-1.f, 0.f, 0.f);
			HD_Vector3f leftForward(-1.f, 0.f, 1.f);

			HD_Vector3f forward(0.f, 0.f, 1.f);

			HD_Vector3f forwardCrossCenterForward = forward.Cross(centerForward);
			HD_Vector3f forwardCrossRightForward = forward.Cross(rightForward);
			HD_Vector3f forwardCrossRightCenter = forward.Cross(rightCenter);
			HD_Vector3f forwardCrossRightBack = forward.Cross(rightBack);
			HD_Vector3f forwardCrossCenterBack = forward.Cross(centerBack);
			HD_Vector3f forwardCrossLeftBack = forward.Cross(leftBack);
			HD_Vector3f forwardCrossLeftCenter = forward.Cross(leftCenter);
			HD_Vector3f forwardCrossLeftForward = forward.Cross(leftForward);

			TestUtils::Vector3_AreEqual(forwardCrossCenterForward, 0.f, 0.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossRightForward, 0.f, 1.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossRightCenter, 0.f, 1.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossRightBack, 0.f, 1.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossCenterBack, 0.f, 0.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossLeftBack, 0.f, -1.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossLeftCenter, 0.f, -1.f, 0.f);
			TestUtils::Vector3_AreEqual(forwardCrossLeftForward, 0.f, -1.f, 0.f);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2;
			floatVector2 = floatVector1;
			TestUtils::Vector3_AreEqual(floatVector2, 1.f, 2.f, 3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2;
			intVector2 = intVector1;
			TestUtils::Vector3_AreEqual(intVector2, 1, 2, 3);

			HD_Vector3ui unsignedIntVector1(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVector2;
			unsignedIntVector2 = unsignedIntVector1;
			TestUtils::Vector3_AreEqual(unsignedIntVector2, 1u, 2u, 3u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			floatVector1 += floatVector2;
			TestUtils::Vector3_AreEqual(floatVector1, 5.f, 7.f, 9.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			intVector1 += intVector2;
			TestUtils::Vector3_AreEqual(intVector1, 5, 7, 9);

			HD_Vector3ui unsignedIntVector1(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVector2(4u, 5u, 6u);
			unsignedIntVector1 += unsignedIntVector2;
			TestUtils::Vector3_AreEqual(unsignedIntVector1, 5u, 7u, 9u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			floatVector1 -= floatVector2;
			TestUtils::Vector3_AreEqual(floatVector1, -3.f, -3.f, -3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			intVector1 -= intVector2;
			TestUtils::Vector3_AreEqual(intVector1, -3, -3, -3);

			HD_Vector3ui unsignedIntVector1(4u, 5u, 6u);
			HD_Vector3ui unsignedIntVector2(1u, 2u, 3u);
			unsignedIntVector1 -= unsignedIntVector2;
			TestUtils::Vector3_AreEqual(unsignedIntVector1, 3u, 3u, 3u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			floatVector *= 2.f;
			TestUtils::Vector3_AreEqual(floatVector, 2.f, 4.f, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			intVector *= 2;
			TestUtils::Vector3_AreEqual(intVector, 2, 4, 6);

			HD_Vector3ui unsignedIntVector(1u, 2u, 3u);
			unsignedIntVector *= 2u;
			TestUtils::Vector3_AreEqual(unsignedIntVector, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			floatVector /= 2.f;
			TestUtils::Vector3_AreEqual(floatVector, 0.5f, 1.f, 1.5f);

			HD_Vector3i intVector(1, 2, 3);
			intVector /= 2;
			TestUtils::Vector3_AreEqual(intVector, 0, 1, 1);

			HD_Vector3ui unsignedIntVector(1u, 2u, 3u);
			unsignedIntVector /= 2u;
			TestUtils::Vector3_AreEqual(unsignedIntVector, 0u, 1u, 1u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatVectorResult = floatVector1 + floatVector2;
			TestUtils::Vector3_AreEqual(floatVectorResult, 5.f, 7.f, 9.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intVectorResult = intVector1 + intVector2;
			TestUtils::Vector3_AreEqual(intVectorResult, 5, 7, 9);

			HD_Vector3ui unsignedIntVector1(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVector2(4u, 5u, 6u);
			HD_Vector3ui unsignedIntVectorResult = unsignedIntVector1 + unsignedIntVector2;
			TestUtils::Vector3_AreEqual(unsignedIntVectorResult, 5u, 7u, 9u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatVectorResult = floatVector1 - floatVector2;
			TestUtils::Vector3_AreEqual(floatVectorResult, -3.f, -3.f, -3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intVectorResult = intVector1 - intVector2;
			TestUtils::Vector3_AreEqual(intVectorResult, -3, -3, -3);

			HD_Vector3ui unsignedIntVector1(4u, 5u, 6u);
			HD_Vector3ui unsignedIntVector2(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVectorResult = unsignedIntVector1 - unsignedIntVector2;
			TestUtils::Vector3_AreEqual(unsignedIntVectorResult, 3u, 3u, 3u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = floatVector * 2.f;
			TestUtils::Vector3_AreEqual(floatVectorResult, 2.f, 4.f, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = intVector * 2;
			TestUtils::Vector3_AreEqual(intVectorResult, 2, 4, 6);

			HD_Vector3ui unsignedIntVector(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVectorResult = unsignedIntVector * 2u;
			TestUtils::Vector3_AreEqual(unsignedIntVectorResult, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = 2.f * floatVector;
			TestUtils::Vector3_AreEqual(floatVectorResult, 2.f, 4.f, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = 2 * intVector;
			TestUtils::Vector3_AreEqual(intVectorResult, 2, 4, 6);

			HD_Vector3ui unsignedIntVector(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVectorResult = 2u * unsignedIntVector;
			TestUtils::Vector3_AreEqual(unsignedIntVectorResult, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = floatVector / 2.f;
			TestUtils::Vector3_AreEqual(floatVectorResult, 0.5f, 1.f, 1.5f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = intVector / 2;
			TestUtils::Vector3_AreEqual(intVectorResult, 0, 1, 1);

			HD_Vector3ui unsignedIntVector(1u, 2u, 3u);
			HD_Vector3ui unsignedIntVectorResult = unsignedIntVector / 2u;
			TestUtils::Vector3_AreEqual(unsignedIntVectorResult, 0u, 1u, 1u);
		}
	};
}
