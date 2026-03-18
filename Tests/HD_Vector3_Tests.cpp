#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector3.h"

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
			float length = floatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(length, HD_Sqrtf(3.f)));
		}

		TEST_METHOD(Length2)
		{
			HD_Vector3f floatVector(1.f, 1.f, 1.f);
			float floatLength2 = floatVector.Length2();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(floatLength2, 3.f));

			HD_Vector3i intVector(2, 2, 2);
			int intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 12);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			floatVector.Normalize();
			float length = floatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(length, 1.f));
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector3f floatVector(2.f, 2.f, 2.f);
			HD_Vector3f normalizedFloatVector = floatVector.GetNormalized();
			float floatVectorLength = floatVector.Length();
			float normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(floatVectorLength, HD_Sqrtf(12.f)));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(normalizedFloatVectorLength, 1.f));
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

			float upDotLeftUpBack = up.Dot(leftUpBack);
			float upDotCenterUpBack = up.Dot(centerUpBack);
			float upDotRightUpBack = up.Dot(rightUpBack);
			float upDotLeftCenterBack = up.Dot(leftCenterBack);
			float upDotCenterCenterBack = up.Dot(centerCenterBack);
			float upDotRightCenterBack = up.Dot(rightCenterBack);
			float upDotLeftDownBack = up.Dot(leftDownBack);
			float upDotCenterDownBack = up.Dot(centerDownBack);
			float upDotRightDownBack = up.Dot(rightDownBack);

			float upDotLeftUpCenter = up.Dot(leftUpCenter);
			float upDotCenterUpCenter = up.Dot(centerUpCenter);
			float upDotRightUpCenter = up.Dot(rightUpCenter);
			float upDotLeftCenterCenter = up.Dot(leftCenterCenter);
			float upDotCenterCenterCenter = up.Dot(centerCenterCenter);
			float upDotRightCenterCenter = up.Dot(rightCenterCenter);
			float upDotLeftDownCenter = up.Dot(leftDownCenter);
			float upDotCenterDownCenter = up.Dot(centerDownCenter);
			float upDotRightDownCenter = up.Dot(rightDownCenter);

			float upDotLeftUpForward = up.Dot(leftUpForward);
			float upDotCenterUpForward = up.Dot(centerUpForward);
			float upDotRightUpForward = up.Dot(rightUpForward);
			float upDotLeftCenterForward = up.Dot(leftCenterForward);
			float upDotCenterCenterForward = up.Dot(centerCenterForward);
			float upDotRightCenterForward = up.Dot(rightCenterForward);
			float upDotLeftDownForward = up.Dot(leftDownForward);
			float upDotCenterDownForward = up.Dot(centerDownForward);
			float upDotRightDownForward = up.Dot(rightDownForward);

			float cornerDotValue = HD_Sinf(HD_ArcTanf(F_ONE_OVER_SQRT_TWO));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftUpBack, cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterUpBack, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightUpBack, cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftCenterBack, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterCenterBack, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightCenterBack, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftDownBack, -1.f * cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterDownBack, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightDownBack, -1.f * cornerDotValue));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftUpCenter, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterUpCenter, 1.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightUpCenter, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftCenterCenter, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterCenterCenter, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightCenterCenter, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftDownCenter, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterDownCenter, -1.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightDownCenter, -1.f * F_ONE_OVER_SQRT_TWO));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftUpForward, cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterUpForward, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightUpForward, cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftCenterForward, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterCenterForward, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightCenterForward, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeftDownForward, -1.f * cornerDotValue));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotCenterDownForward, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRightDownForward, -1.f * cornerDotValue));
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

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterForward.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterForward.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterForward.myY, 0.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightForward.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightForward.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightForward.myY, 1.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightCenter.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightCenter.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightCenter.myY, 1.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightBack.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightBack.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossRightBack.myY, 1.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterBack.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterBack.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossCenterBack.myY, 0.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftBack.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftBack.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftBack.myY, -1.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftCenter.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftCenter.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftCenter.myY, -1.f));

			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftForward.myX, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftForward.myZ, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(forwardCrossLeftForward.myY, -1.f));
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

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatResult = floatVector1 + floatVector2;
			Assert::AreEqual(floatResult.myX, 5.f);
			Assert::AreEqual(floatResult.myY, 7.f);
			Assert::AreEqual(floatResult.myZ, 9.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intResult = intVector1 + intVector2;
			Assert::AreEqual(intResult.myX, 5);
			Assert::AreEqual(intResult.myY, 7);
			Assert::AreEqual(intResult.myZ, 9);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector3f floatVector1(1.f, 2.f, 3.f);
			HD_Vector3f floatVector2(4.f, 5.f, 6.f);
			HD_Vector3f floatResult = floatVector1 - floatVector2;
			Assert::AreEqual(floatResult.myX, -3.f);
			Assert::AreEqual(floatResult.myY, -3.f);
			Assert::AreEqual(floatResult.myZ, -3.f);

			HD_Vector3i intVector1(1, 2, 3);
			HD_Vector3i intVector2(4, 5, 6);
			HD_Vector3i intResult = intVector1 - intVector2;
			Assert::AreEqual(intResult.myX, -3);
			Assert::AreEqual(intResult.myY, -3);
			Assert::AreEqual(intResult.myZ, -3);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatResult = floatVector * 2.f;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);
			Assert::AreEqual(floatResult.myZ, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intResult = intVector * 2;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
			Assert::AreEqual(intResult.myZ, 6);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatResult = 2.f * floatVector;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);
			Assert::AreEqual(floatResult.myZ, 6.f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intResult = 2 * intVector;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
			Assert::AreEqual(intResult.myZ, 6);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector3f floatVector(1.f, 2.f, 3.f);
			HD_Vector3f floatResult = floatVector / 2.f;
			Assert::AreEqual(floatResult.myX, 0.5f);
			Assert::AreEqual(floatResult.myY, 1.f);
			Assert::AreEqual(floatResult.myZ, 1.5f);

			HD_Vector3i intVector(1, 2, 3);
			HD_Vector3i intResult = intVector / 2;
			Assert::AreEqual(intResult.myX, 0);
			Assert::AreEqual(intResult.myY, 1);
			Assert::AreEqual(intResult.myZ, 1);
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
	};
}
