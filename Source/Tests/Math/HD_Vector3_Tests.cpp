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
			HD_Vector3_f32 f32Vector;
			TestUtils::Vector3_AreEqual(f32Vector, 0.f, 0.f, 0.f);

			HD_Vector3_s32 s32Vector;
			TestUtils::Vector3_AreEqual(s32Vector, 0, 0, 0);

			HD_Vector3_u32 u32Vector;
			TestUtils::Vector3_AreEqual(u32Vector, 0u, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			TestUtils::Vector3_AreEqual(f32Vector, 1.f, 2.f, 3.f);

			HD_Vector3_s32 s32Vector(4, 5, 6);
			TestUtils::Vector3_AreEqual(s32Vector, 4, 5, 6);

			HD_Vector3_u32 u32Vector(7u, 8u, 9u);
			TestUtils::Vector3_AreEqual(u32Vector, 7u, 8u, 9u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2(f32Vector1);
			TestUtils::Vector3_AreEqual(f32Vector2, 1.f, 2.f, 3.f);

			HD_Vector3_s32 s32Vector1(4, 5, 6);
			HD_Vector3_s32 s32Vector2(s32Vector1);
			TestUtils::Vector3_AreEqual(s32Vector2, 4, 5, 6);

			HD_Vector3_u32 u32Vector1(7u, 8u, 9u);
			HD_Vector3_u32 u32Vector2(u32Vector1);
			TestUtils::Vector3_AreEqual(u32Vector2, 7u, 8u, 9u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector3_f32 f32Vector;
			f32Vector.Set(1.f, 2.f, 3.f);
			TestUtils::Vector3_AreEqual(f32Vector, 1.f, 2.f, 3.f);

			HD_Vector3_s32 s32Vector;
			s32Vector.Set(4, 5, 6);
			TestUtils::Vector3_AreEqual(s32Vector, 4, 5, 6);

			HD_Vector3_u32 u32Vector;
			u32Vector.Set(7u, 8u, 9u);
			TestUtils::Vector3_AreEqual(u32Vector, 7u, 8u, 9u);
		}

		TEST_METHOD(GetLength)
		{
			HD_Vector3_f32 f32Vector(1.f, 1.f, 1.f);
			f32 length = f32Vector.GetLength();
			Assert::AreEqual(length, HD_Sqrt(3.f), F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetLength2)
		{
			HD_Vector3_f32 f32Vector(1.f, 1.f, 1.f);
			f32 f32Length2 = f32Vector.GetLength2();
			Assert::AreEqual(f32Length2, 3.f, F32_EQUAL_TOLERANCE);

			HD_Vector3_s32 s32Vector(2, 2, 2);
			s32 s32Length2 = s32Vector.GetLength2();
			Assert::AreEqual(s32Length2, 12);

			HD_Vector3_u32 u32Vector(3u, 3u, 3u);
			u32 u32Length2 = u32Vector.GetLength2();
			Assert::AreEqual(u32Length2, 27u);
		}

		TEST_METHOD(SetLength)
		{
			HD_Vector3_f32 f32Vector(1.f, 1.f, 1.f);

			f32Vector.SetLength(1.f);
			Assert::AreEqual(f32Vector.GetLength(), 1.f, F32_EQUAL_TOLERANCE);

			f32Vector.SetLength(2.f);
			Assert::AreEqual(f32Vector.GetLength(), 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Limit)
		{
			HD_Vector3_f32 f32Vector1(1.f, 1.f, 1.f);
			f32Vector1.Limit(1.f);
			Assert::AreEqual(f32Vector1.GetLength(), 1.f, F32_EQUAL_TOLERANCE);


			HD_Vector3_f32 f32Vector2(0.5f, 0.f, 0.f);
			f32Vector2.Limit(1.f);
			Assert::AreEqual(f32Vector2.GetLength(), 0.5f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector3_f32 f32Vector(2.f, 2.f, 2.f);
			f32Vector.Normalize();
			f32 length = f32Vector.GetLength();
			Assert::AreEqual(length, 1.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector3_f32 f32Vector(2.f, 2.f, 2.f);
			HD_Vector3_f32 normalizedf32Vector = f32Vector.GetNormalized();
			f32 f32VectorLength = f32Vector.GetLength();
			f32 normalizedf32VectorLength = normalizedf32Vector.GetLength();
			Assert::AreEqual(f32VectorLength, HD_Sqrt(12.f), F32_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedf32VectorLength, 1.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Dot)
		{
			HD_Vector3_f32 leftUpBack(-1.f, 1.f, -1.f);
			HD_Vector3_f32 centerUpBack(0.f, 1.f, -1.f);
			HD_Vector3_f32 rightUpBack(1.f, 1.f, -1.f);
			HD_Vector3_f32 leftCenterBack(-1.f, 0.f, -1.f);
			HD_Vector3_f32 centerCenterBack(0.f, 0.f, -1.f);
			HD_Vector3_f32 rightCenterBack(1.f, 0.f, -1.f);
			HD_Vector3_f32 leftDownBack(-1.f, -1.f, -1.f);
			HD_Vector3_f32 centerDownBack(0.f, -1.f, -1.f);
			HD_Vector3_f32 rightDownBack(1.f, -1.f, -1.f);

			HD_Vector3_f32 leftUpCenter(-1.f, 1.f, 0.f);
			HD_Vector3_f32 centerUpCenter(0.f, 1.f, 0.f);
			HD_Vector3_f32 rightUpCenter(1.f, 1.f, 0.f);
			HD_Vector3_f32 leftCenterCenter(-1.f, 0.f, 0.f);
			HD_Vector3_f32 centerCenterCenter(0.f, 0.f, 0.f);
			HD_Vector3_f32 rightCenterCenter(1.f, 0.f, 0.f);
			HD_Vector3_f32 leftDownCenter(-1.f, -1.f, 0.f);
			HD_Vector3_f32 centerDownCenter(0.f, -1.f, 0.f);
			HD_Vector3_f32 rightDownCenter(1.f, -1.f, 0.f);

			HD_Vector3_f32 leftUpForward(-1.f, 1.f, 1.f);
			HD_Vector3_f32 centerUpForward(0.f, 1.f, 1.f);
			HD_Vector3_f32 rightUpForward(1.f, 1.f, 1.f);
			HD_Vector3_f32 leftCenterForward(-1.f, 0.f, 1.f);
			HD_Vector3_f32 centerCenterForward(0.f, 0.f, 1.f);
			HD_Vector3_f32 rightCenterForward(1.f, 0.f, 1.f);
			HD_Vector3_f32 leftDownForward(-1.f, -1.f, 1.f);
			HD_Vector3_f32 centerDownForward(0.f, -1.f, 1.f);
			HD_Vector3_f32 rightDownForward(1.f, -1.f, 1.f);

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

			HD_Vector3_f32 up(0.f, 1.f, 0.f);

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

			Assert::AreEqual(upDotLeftUpBack, cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpBack, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpBack, cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterBack, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterBack, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterBack, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownBack, -1.f * cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownBack, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownBack, -1.f * cornerDotValue, F32_EQUAL_TOLERANCE);

			Assert::AreEqual(upDotLeftUpCenter, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpCenter, 1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpCenter, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterCenter, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterCenter, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterCenter, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownCenter, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownCenter, -1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownCenter, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);

			Assert::AreEqual(upDotLeftUpForward, cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterUpForward, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightUpForward, cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftCenterForward, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterCenterForward, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightCenterForward, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeftDownForward, -1.f * cornerDotValue, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotCenterDownForward, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRightDownForward, -1.f * cornerDotValue, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Cross)
		{
			HD_Vector3_f32 centerForward(0.f, 0.f, 1.f);
			HD_Vector3_f32 rightForward(1.f, 0.f, 1.f);
			HD_Vector3_f32 rightCenter(1.f, 0.f, 0.f);
			HD_Vector3_f32 rightBack(1.f, 0.f, -1.f);
			HD_Vector3_f32 centerBack(0.f, 0.f, -1.f);
			HD_Vector3_f32 leftBack(-1.f, 0.f, -1.f);
			HD_Vector3_f32 leftCenter(-1.f, 0.f, 0.f);
			HD_Vector3_f32 leftForward(-1.f, 0.f, 1.f);

			HD_Vector3_f32 forward(0.f, 0.f, 1.f);

			HD_Vector3_f32 forwardCrossCenterForward = forward.Cross(centerForward);
			HD_Vector3_f32 forwardCrossRightForward = forward.Cross(rightForward);
			HD_Vector3_f32 forwardCrossRightCenter = forward.Cross(rightCenter);
			HD_Vector3_f32 forwardCrossRightBack = forward.Cross(rightBack);
			HD_Vector3_f32 forwardCrossCenterBack = forward.Cross(centerBack);
			HD_Vector3_f32 forwardCrossLeftBack = forward.Cross(leftBack);
			HD_Vector3_f32 forwardCrossLeftCenter = forward.Cross(leftCenter);
			HD_Vector3_f32 forwardCrossLeftForward = forward.Cross(leftForward);

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
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2;
			f32Vector2 = f32Vector1;
			TestUtils::Vector3_AreEqual(f32Vector2, 1.f, 2.f, 3.f);

			HD_Vector3_s32 s32Vector1(1, 2, 3);
			HD_Vector3_s32 s32Vector2;
			s32Vector2 = s32Vector1;
			TestUtils::Vector3_AreEqual(s32Vector2, 1, 2, 3);

			HD_Vector3_u32 u32Vector1(1u, 2u, 3u);
			HD_Vector3_u32 u32Vector2;
			u32Vector2 = u32Vector1;
			TestUtils::Vector3_AreEqual(u32Vector2, 1u, 2u, 3u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2(4.f, 5.f, 6.f);
			f32Vector1 += f32Vector2;
			TestUtils::Vector3_AreEqual(f32Vector1, 5.f, 7.f, 9.f);

			HD_Vector3_s32 s32Vector1(1, 2, 3);
			HD_Vector3_s32 s32Vector2(4, 5, 6);
			s32Vector1 += s32Vector2;
			TestUtils::Vector3_AreEqual(s32Vector1, 5, 7, 9);

			HD_Vector3_u32 u32Vector1(1u, 2u, 3u);
			HD_Vector3_u32 u32Vector2(4u, 5u, 6u);
			u32Vector1 += u32Vector2;
			TestUtils::Vector3_AreEqual(u32Vector1, 5u, 7u, 9u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2(4.f, 5.f, 6.f);
			f32Vector1 -= f32Vector2;
			TestUtils::Vector3_AreEqual(f32Vector1, -3.f, -3.f, -3.f);

			HD_Vector3_s32 s32Vector1(1, 2, 3);
			HD_Vector3_s32 s32Vector2(4, 5, 6);
			s32Vector1 -= s32Vector2;
			TestUtils::Vector3_AreEqual(s32Vector1, -3, -3, -3);

			HD_Vector3_u32 u32Vector1(4u, 5u, 6u);
			HD_Vector3_u32 u32Vector2(1u, 2u, 3u);
			u32Vector1 -= u32Vector2;
			TestUtils::Vector3_AreEqual(u32Vector1, 3u, 3u, 3u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			f32Vector *= 2.f;
			TestUtils::Vector3_AreEqual(f32Vector, 2.f, 4.f, 6.f);

			HD_Vector3_s32 s32Vector(1, 2, 3);
			s32Vector *= 2;
			TestUtils::Vector3_AreEqual(s32Vector, 2, 4, 6);

			HD_Vector3_u32 u32Vector(1u, 2u, 3u);
			u32Vector *= 2u;
			TestUtils::Vector3_AreEqual(u32Vector, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			f32Vector /= 2.f;
			TestUtils::Vector3_AreEqual(f32Vector, 0.5f, 1.f, 1.5f);

			HD_Vector3_s32 s32Vector(1, 2, 3);
			s32Vector /= 2;
			TestUtils::Vector3_AreEqual(s32Vector, 0, 1, 1);

			HD_Vector3_u32 u32Vector(1u, 2u, 3u);
			u32Vector /= 2u;
			TestUtils::Vector3_AreEqual(u32Vector, 0u, 1u, 1u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector3_f32 f32Vector1(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector2(1.f, 1.f, 1.f);
			f32 length = HD_Vector3_f32::Length(f32Vector1, f32Vector2);
			Assert::AreEqual(length, HD_Sqrt(3.f), F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector3_f32 f32Vector1(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector2(1.f, 1.f, 1.f);
			f32 f32Length2 = HD_Vector3_f32::Length2(f32Vector1, f32Vector2);
			Assert::AreEqual(f32Length2, 3.f, F32_EQUAL_TOLERANCE);

			HD_Vector3_s32 s32Vector1(0, 0, 0);
			HD_Vector3_s32 s32Vector2(2, 2, 2);
			s32 s32Length2 = HD_Vector3_s32::Length2(s32Vector1, s32Vector2);
			Assert::AreEqual(s32Length2, 12);

			HD_Vector3_u32 u32Vector1(0u, 0u, 0u);
			HD_Vector3_u32 u32Vector2(3u, 3u, 3u);
			u32 u32Length2 = HD_Vector3_u32::Length2(u32Vector1, u32Vector2);
			Assert::AreEqual(u32Length2, 27u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2(4.f, 5.f, 6.f);
			HD_Vector3_f32 f32VectorResult = f32Vector1 + f32Vector2;
			TestUtils::Vector3_AreEqual(f32VectorResult, 5.f, 7.f, 9.f);

			HD_Vector3_s32 s32Vector1(1, 2, 3);
			HD_Vector3_s32 s32Vector2(4, 5, 6);
			HD_Vector3_s32 s32VectorResult = s32Vector1 + s32Vector2;
			TestUtils::Vector3_AreEqual(s32VectorResult, 5, 7, 9);

			HD_Vector3_u32 u32Vector1(1u, 2u, 3u);
			HD_Vector3_u32 u32Vector2(4u, 5u, 6u);
			HD_Vector3_u32 u32VectorResult = u32Vector1 + u32Vector2;
			TestUtils::Vector3_AreEqual(u32VectorResult, 5u, 7u, 9u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector3_f32 f32Vector1(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32Vector2(4.f, 5.f, 6.f);
			HD_Vector3_f32 f32VectorResult = f32Vector1 - f32Vector2;
			TestUtils::Vector3_AreEqual(f32VectorResult, -3.f, -3.f, -3.f);

			HD_Vector3_s32 s32Vector1(1, 2, 3);
			HD_Vector3_s32 s32Vector2(4, 5, 6);
			HD_Vector3_s32 s32VectorResult = s32Vector1 - s32Vector2;
			TestUtils::Vector3_AreEqual(s32VectorResult, -3, -3, -3);

			HD_Vector3_u32 u32Vector1(4u, 5u, 6u);
			HD_Vector3_u32 u32Vector2(1u, 2u, 3u);
			HD_Vector3_u32 u32VectorResult = u32Vector1 - u32Vector2;
			TestUtils::Vector3_AreEqual(u32VectorResult, 3u, 3u, 3u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32VectorResult = f32Vector * 2.f;
			TestUtils::Vector3_AreEqual(f32VectorResult, 2.f, 4.f, 6.f);

			HD_Vector3_s32 s32Vector(1, 2, 3);
			HD_Vector3_s32 s32VectorResult = s32Vector * 2;
			TestUtils::Vector3_AreEqual(s32VectorResult, 2, 4, 6);

			HD_Vector3_u32 u32Vector(1u, 2u, 3u);
			HD_Vector3_u32 u32VectorResult = u32Vector * 2u;
			TestUtils::Vector3_AreEqual(u32VectorResult, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32VectorResult = 2.f * f32Vector;
			TestUtils::Vector3_AreEqual(f32VectorResult, 2.f, 4.f, 6.f);

			HD_Vector3_s32 s32Vector(1, 2, 3);
			HD_Vector3_s32 s32VectorResult = 2 * s32Vector;
			TestUtils::Vector3_AreEqual(s32VectorResult, 2, 4, 6);

			HD_Vector3_u32 u32Vector(1u, 2u, 3u);
			HD_Vector3_u32 u32VectorResult = 2u * u32Vector;
			TestUtils::Vector3_AreEqual(u32VectorResult, 2u, 4u, 6u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector3_f32 f32Vector(1.f, 2.f, 3.f);
			HD_Vector3_f32 f32VectorResult = f32Vector / 2.f;
			TestUtils::Vector3_AreEqual(f32VectorResult, 0.5f, 1.f, 1.5f);

			HD_Vector3_s32 s32Vector(1, 2, 3);
			HD_Vector3_s32 s32VectorResult = s32Vector / 2;
			TestUtils::Vector3_AreEqual(s32VectorResult, 0, 1, 1);

			HD_Vector3_u32 u32Vector(1u, 2u, 3u);
			HD_Vector3_u32 u32VectorResult = u32Vector / 2u;
			TestUtils::Vector3_AreEqual(u32VectorResult, 0u, 1u, 1u);
		}

		TEST_METHOD(Operator_Equals)
		{
			HD_Vector3_f32 f32Vector1(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector2(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector3(1.f, 1.f, 1.f);

			Assert::IsTrue(f32Vector1 == f32Vector2);
			Assert::IsFalse(f32Vector1 == f32Vector3);
		}

		TEST_METHOD(Operator_Not_Equals)
		{
			HD_Vector3_f32 f32Vector1(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector2(0.f, 0.f, 0.f);
			HD_Vector3_f32 f32Vector3(1.f, 1.f, 1.f);

			Assert::IsFalse(f32Vector1 != f32Vector2);
			Assert::IsTrue(f32Vector1 != f32Vector3);
		}
	};
}
