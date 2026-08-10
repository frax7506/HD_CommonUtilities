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
			HD_Vector2_f32 f32Vector;
			TestUtils::Vector2_AreEqual(f32Vector, 0.f, 0.f);

			HD_Vector2_s32 s32Vector;
			TestUtils::Vector2_AreEqual(s32Vector, 0, 0);

			HD_Vector2_u32 u32Vector;
			TestUtils::Vector2_AreEqual(u32Vector, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			TestUtils::Vector2_AreEqual(f32Vector, 1.f, 2.f);

			HD_Vector2_s32 s32Vector(3, 4);
			TestUtils::Vector2_AreEqual(s32Vector, 3, 4);

			HD_Vector2_u32 u32Vector(5u, 6u);
			TestUtils::Vector2_AreEqual(u32Vector, 5u, 6u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2(f32Vector1);
			TestUtils::Vector2_AreEqual(f32Vector2, 1.f, 2.f);

			HD_Vector2_s32 s32Vector1(3, 4);
			HD_Vector2_s32 s32Vector2(s32Vector1);
			TestUtils::Vector2_AreEqual(s32Vector2, 3, 4);

			HD_Vector2_u32 u32Vector1(5u, 6u);
			HD_Vector2_u32 u32Vector2(u32Vector1);
			TestUtils::Vector2_AreEqual(u32Vector2, 5u, 6u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector2_f32 f32Vector;
			f32Vector.Set(1.f, 2.f);
			TestUtils::Vector2_AreEqual(f32Vector, 1.f, 2.f);

			HD_Vector2_s32 s32Vector;
			s32Vector.Set(3, 4);
			TestUtils::Vector2_AreEqual(s32Vector, 3, 4);

			HD_Vector2_u32 u32Vector;
			u32Vector.Set(5u, 6u);
			TestUtils::Vector2_AreEqual(u32Vector, 5u, 6u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector2_f32 f32Vector(1.f, 1.f);
			f32 length = f32Vector.Length();
			Assert::AreEqual(length, HD_Sqrt(2.f), F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector2_f32 f32Vector(1.f, 1.f);
			f32 f32Length2 = f32Vector.Length2();
			Assert::AreEqual(f32Length2, 2.f, F32_EQUAL_TOLERANCE);

			HD_Vector2_s32 s32Vector(2, 2);
			s32 s32Length2 = s32Vector.Length2();
			Assert::AreEqual(s32Length2, 8);

			HD_Vector2_u32 u32Vector(3, 3);
			u32 u32Length2 = u32Vector.Length2();
			Assert::AreEqual(u32Length2, 18u);
		}

		TEST_METHOD(SetLength)
		{
			HD_Vector2_f32 f32Vector(1.f, 1.f);

			f32Vector.SetLength(1.f);
			Assert::AreEqual(f32Vector.Length(), 1.f, F32_EQUAL_TOLERANCE);

			f32Vector.SetLength(2.f);
			Assert::AreEqual(f32Vector.Length(), 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector2_f32 f32Vector(2.f, 2.f);
			f32Vector.Normalize();
			f32 length = f32Vector.Length();
			Assert::AreEqual(length, 1.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector2_f32 f32Vector(2.f, 2.f);
			HD_Vector2_f32 normalizedf32Vector = f32Vector.GetNormalized();
			f32 f32VectorLength = f32Vector.Length();
			f32 normalizedf32VectorLength = normalizedf32Vector.Length();
			Assert::AreEqual(f32VectorLength, HD_Sqrt(8.f), F32_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedf32VectorLength, 1.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Dot)
		{
			HD_Vector2_f32 up(0.f, 1.f);
			HD_Vector2_f32 upRight(1.f, 1.f);
			HD_Vector2_f32 right(1.f, 0.f);
			HD_Vector2_f32 downRight(1.f, -1.f);
			HD_Vector2_f32 down(0.f, -1.f);
			HD_Vector2_f32 downLeft(-1.f, -1.f);
			HD_Vector2_f32 left(-1.f, 0.f);
			HD_Vector2_f32 upLeft(-1.f, 1.f);

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

			Assert::AreEqual(upDotUp, 1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotUpRight, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotRight, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDownRight, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDown, -1.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotDownLeft, -1.f * F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotLeft, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(upDotUpLeft, F_ONE_OVER_SQRT_TWO, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2;
			f32Vector2 = f32Vector1;
			TestUtils::Vector2_AreEqual(f32Vector2, 1.f, 2.f);

			HD_Vector2_s32 s32Vector1(3, 4);
			HD_Vector2_s32 s32Vector2;
			s32Vector2 = s32Vector1;
			TestUtils::Vector2_AreEqual(s32Vector2, 3, 4);

			HD_Vector2_u32 u32Vector1(5u, 6u);
			HD_Vector2_u32 u32Vector2;
			u32Vector2 = u32Vector1;
			TestUtils::Vector2_AreEqual(u32Vector2, 5u, 6u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2(3.f, 4.f);
			f32Vector1 += f32Vector2;
			TestUtils::Vector2_AreEqual(f32Vector1, 4.f, 6.f);

			HD_Vector2_s32 s32Vector1(1, 2);
			HD_Vector2_s32 s32Vector2(3, 4);
			s32Vector1 += s32Vector2;
			TestUtils::Vector2_AreEqual(s32Vector1, 4, 6);

			HD_Vector2_u32 u32Vector1(1u, 2u);
			HD_Vector2_u32 u32Vector2(3u, 4u);
			u32Vector1 += u32Vector2;
			TestUtils::Vector2_AreEqual(u32Vector1, 4u, 6u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2(3.f, 4.f);
			f32Vector1 -= f32Vector2;
			TestUtils::Vector2_AreEqual(f32Vector1, -2.f, -2.f);

			HD_Vector2_s32 s32Vector1(1, 2);
			HD_Vector2_s32 s32Vector2(3, 4);
			s32Vector1 -= s32Vector2;
			TestUtils::Vector2_AreEqual(s32Vector1, -2, -2);

			HD_Vector2_u32 u32Vector1(4u, 3u);
			HD_Vector2_u32 u32Vector2(2u, 1u);
			u32Vector1 -= u32Vector2;
			TestUtils::Vector2_AreEqual(u32Vector1, 2u, 2u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			f32Vector *= 2.f;
			TestUtils::Vector2_AreEqual(f32Vector, 2.f, 4.f);

			HD_Vector2_s32 s32Vector(1, 2);
			s32Vector *= 2;
			TestUtils::Vector2_AreEqual(s32Vector, 2, 4);

			HD_Vector2_u32 u32Vector(1u, 2u);
			u32Vector *= 2u;
			TestUtils::Vector2_AreEqual(u32Vector, 2u, 4u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			f32Vector /= 2.f;
			TestUtils::Vector2_AreEqual(f32Vector, 0.5f, 1.f);

			HD_Vector2_s32 s32Vector(1, 2);
			s32Vector /= 2;
			TestUtils::Vector2_AreEqual(s32Vector, 0, 1);

			HD_Vector2_u32 u32Vector(1u, 2u);
			u32Vector /= 2u;
			TestUtils::Vector2_AreEqual(u32Vector, 0u, 1u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2(3.f, 4.f);
			HD_Vector2_f32 f32VectorResult = f32Vector1 + f32Vector2;
			TestUtils::Vector2_AreEqual(f32VectorResult, 4.f, 6.f);

			HD_Vector2_s32 s32Vector1(1, 2);
			HD_Vector2_s32 s32Vector2(3, 4);
			HD_Vector2_s32 s32VectorResult = s32Vector1 + s32Vector2;
			TestUtils::Vector2_AreEqual(s32VectorResult, 4, 6);

			HD_Vector2_u32 u32Vector1(1u, 2u);
			HD_Vector2_u32 u32Vector2(3u, 4u);
			HD_Vector2_u32 u32VectorResult = u32Vector1 + u32Vector2;
			TestUtils::Vector2_AreEqual(u32VectorResult, 4u, 6u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector2_f32 f32Vector1(1.f, 2.f);
			HD_Vector2_f32 f32Vector2(3.f, 4.f);
			HD_Vector2_f32 f32VectorResult = f32Vector1 - f32Vector2;
			TestUtils::Vector2_AreEqual(f32VectorResult, -2.f, -2.f);

			HD_Vector2_s32 s32Vector1(1, 2);
			HD_Vector2_s32 s32Vector2(3, 4);
			HD_Vector2_s32 s32VectorResult = s32Vector1 - s32Vector2;
			TestUtils::Vector2_AreEqual(s32VectorResult, -2, -2);

			HD_Vector2_u32 u32Vector1(4u, 3u);
			HD_Vector2_u32 u32Vector2(2u, 1u);
			HD_Vector2_u32 u32VectorResult = u32Vector1 - u32Vector2;
			TestUtils::Vector2_AreEqual(u32VectorResult, 2u, 2u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			HD_Vector2_f32 f32VectorResult = f32Vector * 2.f;
			TestUtils::Vector2_AreEqual(f32VectorResult, 2.f, 4.f);

			HD_Vector2_s32 s32Vector(1, 2);
			HD_Vector2_s32 s32VectorResult = s32Vector * 2;
			TestUtils::Vector2_AreEqual(s32VectorResult, 2, 4);

			HD_Vector2_u32 u32Vector(1u, 2u);
			HD_Vector2_u32 u32VectorResult = u32Vector * 2u;
			TestUtils::Vector2_AreEqual(u32VectorResult, 2u, 4u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			HD_Vector2_f32 f32VectorResult = 2.f * f32Vector;
			TestUtils::Vector2_AreEqual(f32VectorResult, 2.f, 4.f);

			HD_Vector2_s32 s32Vector(1, 2);
			HD_Vector2_s32 s32VectorResult = 2 * s32Vector;
			TestUtils::Vector2_AreEqual(s32VectorResult, 2, 4);

			HD_Vector2_u32 u32Vector(1u, 2u);
			HD_Vector2_u32 u32VectorResult = 2u * u32Vector;
			TestUtils::Vector2_AreEqual(u32VectorResult, 2u, 4u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector2_f32 f32Vector(1.f, 2.f);
			HD_Vector2_f32 f32VectorResult = f32Vector / 2.f;
			TestUtils::Vector2_AreEqual(f32VectorResult, 0.5f, 1.f);

			HD_Vector2_s32 s32Vector(1, 2);
			HD_Vector2_s32 s32VectorResult = s32Vector / 2;
			TestUtils::Vector2_AreEqual(s32VectorResult, 0, 1);

			HD_Vector2_u32 u32Vector(1u, 2u);
			HD_Vector2_u32 u32VectorResult = u32Vector / 2u;
			TestUtils::Vector2_AreEqual(u32VectorResult, 0u, 1u);
		}
	};
}
