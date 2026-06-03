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
			Assert::AreEqual(floatVector.myX, 0.f);
			Assert::AreEqual(floatVector.myY, 0.f);
			Assert::AreEqual(floatVector.myZ, 0.f);

			HD_Vector3i intVector;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 0);
			Assert::AreEqual(intVector.myZ, 0);

			// htodo: complement this test file with tests for HD_Vector3ui
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);
			Assert::AreEqual(floatVector.myZ, 3.f);

			HD_Vector3i intVector(3, 4, 5);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
			Assert::AreEqual(intVector.myZ, 5);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(floatVector1);
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);
			Assert::AreEqual(floatVector2.myZ, 3.f);

			HD_Vector3i intVector1(3, 4, 5);
			HD_Vector3i intVector2(intVector1);
			Assert::AreEqual(intVector2.myX, 3);
			Assert::AreEqual(intVector2.myY, 4);
			Assert::AreEqual(intVector2.myZ, 5);
		}

		TEST_METHOD(Set)
		{
			HD_Vector3f floatVector;
			floatVector.Set(1.f, 2.f, 3.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);
			Assert::AreEqual(floatVector.myZ, 3.f);

			HD_Vector3i intVector;
			intVector.Set(3, 4, 5);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
			Assert::AreEqual(intVector.myZ, 5);
		}

		TEST_METHOD(Length)
		{
			HD_Vector3f floatVector(1.f, 1.f, 1.f);
			f32 length = floatVector.Length();
			Assert::IsTrue(TestUtils::AreFloatValuesClose(length, HD_Sqrtf(3.f)));
		}

		TEST_METHOD(Length2)
		{
			HD_Vector3f floatVector(1.f, 1.f, 1.f);
			f32 floatLength2 = floatVector.Length2();
			Assert::IsTrue(TestUtils::AreFloatValuesClose(floatLength2, 3.f));

			HD_Vector3i intVector(2, 2, 2);
			s32 intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 12);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			floatVector.Normalize();
			f32 length = floatVector.Length();
			Assert::IsTrue(TestUtils::AreFloatValuesClose(length, 1.f));
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			HD_Vector3f normalizedFloatVector = floatVector.GetNormalized();
			f32 floatVectorLength = floatVector.Length();
			f32 normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::IsTrue(TestUtils::AreFloatValuesClose(floatVectorLength, HD_Sqrtf(12.f)));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(normalizedFloatVectorLength, 1.f));
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

			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftUpBack, cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterUpBack, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightUpBack, cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftCenterBack, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterCenterBack, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightCenterBack, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftDownBack, -1.f * cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterDownBack, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightDownBack, -1.f * cornerDotValue));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftUpCenter, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterUpCenter, 1.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightUpCenter, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftCenterCenter, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterCenterCenter, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightCenterCenter, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftDownCenter, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterDownCenter, -1.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightDownCenter, -1.f * F_ONE_OVER_SQRT_TWO));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftUpForward, cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterUpForward, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightUpForward, cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftCenterForward, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterCenterForward, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightCenterForward, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotLeftDownForward, -1.f * cornerDotValue));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotCenterDownForward, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(upDotRightDownForward, -1.f * cornerDotValue));
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

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterForward.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterForward.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterForward.myY, 0.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightForward.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightForward.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightForward.myY, 1.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightCenter.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightCenter.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightCenter.myY, 1.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightBack.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightBack.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossRightBack.myY, 1.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterBack.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterBack.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossCenterBack.myY, 0.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftBack.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftBack.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftBack.myY, -1.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftCenter.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftCenter.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftCenter.myY, -1.f));

			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftForward.myX, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftForward.myZ, 0.f));
			Assert::IsTrue(TestUtils::AreFloatValuesClose(forwardCrossLeftForward.myY, -1.f));
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2;
			floatVector2 = floatVector1;
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);
			Assert::AreEqual(floatVector2.myZ, 3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2;
			intVector2 = intVector1;
			Assert::AreEqual(intVector2.myX, 1);
			Assert::AreEqual(intVector2.myY, 2);
			Assert::AreEqual(intVector2.myZ, 3);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			floatVector1 += floatVector2;
			Assert::AreEqual(floatVector1.myX, 5.f);
			Assert::AreEqual(floatVector1.myY, 7.f);
			Assert::AreEqual(floatVector1.myZ, 9.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			intVector1 += intVector2;
			Assert::AreEqual(intVector1.myX, 5);
			Assert::AreEqual(intVector1.myY, 7);
			Assert::AreEqual(intVector1.myZ, 9);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			floatVector1 -= floatVector2;
			Assert::AreEqual(floatVector1.myX, -3.f);
			Assert::AreEqual(floatVector1.myY, -3.f);
			Assert::AreEqual(floatVector1.myZ, -3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			intVector1 -= intVector2;
			Assert::AreEqual(intVector1.myX, -3);
			Assert::AreEqual(intVector1.myY, -3);
			Assert::AreEqual(intVector1.myZ, -3);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			floatVector *= 2.f;
			Assert::AreEqual(floatVector.myX, 2.f);
			Assert::AreEqual(floatVector.myY, 4.f);
			Assert::AreEqual(floatVector.myZ, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			intVector *= 2;
			Assert::AreEqual(intVector.myX, 2);
			Assert::AreEqual(intVector.myY, 4);
			Assert::AreEqual(intVector.myZ, 6);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			floatVector /= 2.f;
			Assert::AreEqual(floatVector.myX, 0.5f);
			Assert::AreEqual(floatVector.myY, 1.f);
			Assert::AreEqual(floatVector.myZ, 1.5f);

			HD_Vector3i intVector(1, 2, 3);
			intVector /= 2;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 1);
			Assert::AreEqual(intVector.myZ, 1);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatVectorResult = floatVector1 + floatVector2;
			Assert::AreEqual(floatVectorResult.myX, 5.f);
			Assert::AreEqual(floatVectorResult.myY, 7.f);
			Assert::AreEqual(floatVectorResult.myZ, 9.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intVectorResult = intVector1 + intVector2;
			Assert::AreEqual(intVectorResult.myX, 5);
			Assert::AreEqual(intVectorResult.myY, 7);
			Assert::AreEqual(intVectorResult.myZ, 9);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatVectorResult = floatVector1 - floatVector2;
			Assert::AreEqual(floatVectorResult.myX, -3.f);
			Assert::AreEqual(floatVectorResult.myY, -3.f);
			Assert::AreEqual(floatVectorResult.myZ, -3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intVectorResult = intVector1 - intVector2;
			Assert::AreEqual(intVectorResult.myX, -3);
			Assert::AreEqual(intVectorResult.myY, -3);
			Assert::AreEqual(intVectorResult.myZ, -3);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = floatVector * 2.f;
			Assert::AreEqual(floatVectorResult.myX, 2.f);
			Assert::AreEqual(floatVectorResult.myY, 4.f);
			Assert::AreEqual(floatVectorResult.myZ, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = intVector * 2;
			Assert::AreEqual(intVectorResult.myX, 2);
			Assert::AreEqual(intVectorResult.myY, 4);
			Assert::AreEqual(intVectorResult.myZ, 6);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = 2.f * floatVector;
			Assert::AreEqual(floatVectorResult.myX, 2.f);
			Assert::AreEqual(floatVectorResult.myY, 4.f);
			Assert::AreEqual(floatVectorResult.myZ, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = 2 * intVector;
			Assert::AreEqual(intVectorResult.myX, 2);
			Assert::AreEqual(intVectorResult.myY, 4);
			Assert::AreEqual(intVectorResult.myZ, 6);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatVectorResult = floatVector / 2.f;
			Assert::AreEqual(floatVectorResult.myX, 0.5f);
			Assert::AreEqual(floatVectorResult.myY, 1.f);
			Assert::AreEqual(floatVectorResult.myZ, 1.5f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intVectorResult = intVector / 2;
			Assert::AreEqual(intVectorResult.myX, 0);
			Assert::AreEqual(intVectorResult.myY, 1);
			Assert::AreEqual(intVectorResult.myZ, 1);
		}
	};
}
