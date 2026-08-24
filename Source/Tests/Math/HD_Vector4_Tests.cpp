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
			HD_Vector4_f32 f32Vector;
			TestUtils::Vector4_AreEqual(f32Vector, 0.f, 0.f, 0.f, 0.f);

			HD_Vector4_s32 s32Vector;
			TestUtils::Vector4_AreEqual(s32Vector, 0, 0, 0, 0);

			HD_Vector4_u32 u32Vector;
			TestUtils::Vector4_AreEqual(u32Vector, 0u, 0u, 0u, 0u);
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z_And_W)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			TestUtils::Vector4_AreEqual(f32Vector, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4_s32 s32Vector(5, 6, 7, 8);
			TestUtils::Vector4_AreEqual(s32Vector, 5, 6, 7, 8);

			HD_Vector4_u32 u32Vector(9u, 10u, 11u, 12u);
			TestUtils::Vector4_AreEqual(u32Vector, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2(f32Vector1);
			TestUtils::Vector4_AreEqual(f32Vector2, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4_s32 s32Vector1(5, 6, 7, 8);
			HD_Vector4_s32 s32Vector2(s32Vector1);
			TestUtils::Vector4_AreEqual(s32Vector2, 5, 6, 7, 8);

			HD_Vector4_u32 u32Vector1(9u, 10u, 11u, 12u);
			HD_Vector4_u32 u32Vector2(u32Vector1);
			TestUtils::Vector4_AreEqual(u32Vector2, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Set)
		{
			HD_Vector4_f32 f32Vector;
			f32Vector.Set(1.f, 2.f, 3.f, 4.f);
			TestUtils::Vector4_AreEqual(f32Vector, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4_s32 s32Vector;
			s32Vector.Set(5, 6, 7, 8);
			TestUtils::Vector4_AreEqual(s32Vector, 5, 6, 7, 8);

			HD_Vector4_u32 u32Vector;
			u32Vector.Set(9u, 10u, 11u, 12u);
			TestUtils::Vector4_AreEqual(u32Vector, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(GetLength)
		{
			HD_Vector4_f32 f32Vector(1.f, 1.f, 1.f, 1.f);
			f32 length = f32Vector.GetLength();
			Assert::AreEqual(length, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetLength2)
		{
			HD_Vector4_f32 f32Vector(1.f, 1.f, 1.f, 1.f);
			f32 f32Length2 = f32Vector.GetLength2();
			Assert::AreEqual(f32Length2, 4.f, F32_EQUAL_TOLERANCE);

			HD_Vector4_s32 s32Vector(2, 2, 2, 2);
			s32 s32Length2 = s32Vector.GetLength2();
			Assert::AreEqual(s32Length2, 16);

			HD_Vector4_u32 u32Vector(3u, 3u, 3u, 3u);
			u32 u32Length2 = u32Vector.GetLength2();
			Assert::AreEqual(u32Length2, 36u);
		}

		TEST_METHOD(SetLength)
		{
			HD_Vector4_f32 f32Vector(1.f, 1.f, 1.f, 1.f);

			f32Vector.SetLength(1.f);
			Assert::AreEqual(f32Vector.GetLength(), 1.f, F32_EQUAL_TOLERANCE);

			f32Vector.SetLength(2.f);
			Assert::AreEqual(f32Vector.GetLength(), 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Limit)
		{
			HD_Vector4_f32 f32Vector1(1.f, 1.f, 1.f, 1.f);
			f32Vector1.Limit(1.f);
			Assert::AreEqual(f32Vector1.GetLength(), 1.f, F32_EQUAL_TOLERANCE);


			HD_Vector4_f32 f32Vector2(0.5f, 0.f, 0.f, 0.f);
			f32Vector2.Limit(1.f);
			Assert::AreEqual(f32Vector2.GetLength(), 0.5f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector4_f32 f32Vector(2.f, 2.f, 2.f, 2.f);
			f32Vector.Normalize();
			f32 length = f32Vector.GetLength();
			Assert::AreEqual(length, 1.f, F32_EQUAL_TOLERANCE);

			HD_Vector4_f32 zeroVector = HD_Vector4_f32::Zero;
			zeroVector.Normalize();
			f32 zeroLength = zeroVector.GetLength();
			Assert::AreEqual(zeroLength, 0.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector4_f32 f32Vector(2.f, 2.f, 2.f, 2.f);
			HD_Vector4_f32 normalizedf32Vector = f32Vector.GetNormalized();
			f32 f32VectorLength = f32Vector.GetLength();
			f32 normalizedf32VectorLength = normalizedf32Vector.GetLength();
			Assert::AreEqual(f32VectorLength, 4.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedf32VectorLength, 1.f, F32_EQUAL_TOLERANCE);

			HD_Vector4_f32 zeroVector = HD_Vector4_f32::Zero;
			HD_Vector4_f32 normalizedZeroVector = zeroVector.GetNormalized();
			f32 zeroVectorLength = zeroVector.GetLength();
			f32 normalizedZeroVectorLength = normalizedZeroVector.GetLength();
			Assert::AreEqual(zeroVectorLength, 0.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(normalizedZeroVectorLength, 0.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2;
			f32Vector2 = f32Vector1;
			TestUtils::Vector4_AreEqual(f32Vector2, 1.f, 2.f, 3.f, 4.f);

			HD_Vector4_s32 s32Vector1(5, 6, 7, 8);
			HD_Vector4_s32 s32Vector2;
			s32Vector2 = s32Vector1;
			TestUtils::Vector4_AreEqual(s32Vector2, 5, 6, 7, 8);

			HD_Vector4_u32 u32Vector1(9u, 10u, 11u, 12u);
			HD_Vector4_u32 u32Vector2;
			u32Vector2 = u32Vector1;
			TestUtils::Vector4_AreEqual(u32Vector2, 9u, 10u, 11u, 12u);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2(5.f, 6.f, 7.f, 8.f);
			f32Vector1 += f32Vector2;
			TestUtils::Vector4_AreEqual(f32Vector1, 6.f, 8.f, 10.f, 12.f);

			HD_Vector4_s32 s32Vector1(1, 2, 3, 4);
			HD_Vector4_s32 s32Vector2(5, 6, 7, 8);
			s32Vector1 += s32Vector2;
			TestUtils::Vector4_AreEqual(s32Vector1, 6, 8, 10, 12);

			HD_Vector4_u32 u32Vector1(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32Vector2(5u, 6u, 7u, 8u);
			u32Vector1 += u32Vector2;
			TestUtils::Vector4_AreEqual(u32Vector1, 6u, 8u, 10u, 12u);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2(5.f, 6.f, 7.f, 8.f);
			f32Vector1 -= f32Vector2;
			TestUtils::Vector4_AreEqual(f32Vector1, -4.f, -4.f, -4.f, -4.f);

			HD_Vector4_s32 s32Vector1(1, 2, 3, 4);
			HD_Vector4_s32 s32Vector2(5, 6, 7, 8);
			s32Vector1 -= s32Vector2;
			TestUtils::Vector4_AreEqual(s32Vector1, -4, -4, -4, -4);

			HD_Vector4_u32 u32Vector1(5u, 6u, 7u, 8u);
			HD_Vector4_u32 u32Vector2(1u, 2u, 3u, 4u);
			u32Vector1 -= u32Vector2;
			TestUtils::Vector4_AreEqual(u32Vector1, 4u, 4u, 4u, 4u);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			f32Vector *= 2.f;
			TestUtils::Vector4_AreEqual(f32Vector, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4_s32 s32Vector(1, 2, 3, 4);
			s32Vector *= 2;
			TestUtils::Vector4_AreEqual(s32Vector, 2, 4, 6, 8);

			HD_Vector4_u32 u32Vector(1u, 2u, 3u, 4u);
			u32Vector *= 2u;
			TestUtils::Vector4_AreEqual(u32Vector, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			f32Vector /= 2.f;
			TestUtils::Vector4_AreEqual(f32Vector, 0.5f, 1.f, 1.5f, 2.f);

			HD_Vector4_s32 s32Vector(1, 2, 3, 4);
			s32Vector /= 2;
			TestUtils::Vector4_AreEqual(s32Vector, 0, 1, 1, 2);

			HD_Vector4_u32 u32Vector(1u, 2u, 3u, 4u);
			u32Vector /= 2u;
			TestUtils::Vector4_AreEqual(u32Vector, 0u, 1u, 1u, 2u);
		}

		TEST_METHOD(Length)
		{
			HD_Vector4_f32 f32Vector1(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector2(1.f, 1.f, 1.f, 1.f);
			f32 length = HD_Vector4_f32::Length(f32Vector1, f32Vector2);
			Assert::AreEqual(length, 2.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(Length2)
		{
			HD_Vector4_f32 f32Vector1(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector2(1.f, 1.f, 1.f, 1.f);
			f32 f32Length2 = HD_Vector4_f32::Length2(f32Vector1, f32Vector2);
			Assert::AreEqual(f32Length2, 4.f, F32_EQUAL_TOLERANCE);

			HD_Vector4_s32 s32Vector1(0, 0, 0, 0);
			HD_Vector4_s32 s32Vector2(2, 2, 2, 2);
			s32 s32Length2 = HD_Vector4_s32::Length2(s32Vector1, s32Vector2);
			Assert::AreEqual(s32Length2, 16);

			HD_Vector4_u32 u32Vector1(0u, 0u, 0u, 0u);
			HD_Vector4_u32 u32Vector2(3u, 3u, 3u, 3u);
			u32 u32Length2 = HD_Vector4_u32::Length2(u32Vector1, u32Vector2);
			Assert::AreEqual(u32Length2, 36u);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4_f32 f32VectorResult = f32Vector1 + f32Vector2;
			TestUtils::Vector4_AreEqual(f32VectorResult, 6.f, 8.f, 10.f, 12.f);

			HD_Vector4_s32 s32Vector1(1, 2, 3, 4);
			HD_Vector4_s32 s32Vector2(5, 6, 7, 8);
			HD_Vector4_s32 s32VectorResult = s32Vector1 + s32Vector2;
			TestUtils::Vector4_AreEqual(s32VectorResult, 6, 8, 10, 12);

			HD_Vector4_u32 u32Vector1(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32Vector2(5u, 6u, 7u, 8u);
			HD_Vector4_u32 u32VectorResult = u32Vector1 + u32Vector2;
			TestUtils::Vector4_AreEqual(u32VectorResult, 6u, 8u, 10u, 12u);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector4_f32 f32Vector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32Vector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4_f32 f32VectorResult = f32Vector1 - f32Vector2;
			TestUtils::Vector4_AreEqual(f32VectorResult, -4.f, -4.f, -4.f, -4.f);

			HD_Vector4_s32 s32Vector1(1, 2, 3, 4);
			HD_Vector4_s32 s32Vector2(5, 6, 7, 8);
			HD_Vector4_s32 s32VectorResult = s32Vector1 - s32Vector2;
			TestUtils::Vector4_AreEqual(s32VectorResult, -4, -4, -4, -4);

			HD_Vector4_u32 u32Vector1(5u, 6u, 7u, 8u);
			HD_Vector4_u32 u32Vector2(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32VectorResult = u32Vector1 - u32Vector2;
			TestUtils::Vector4_AreEqual(u32VectorResult, 4u, 4u, 4u, 4u);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32VectorResult = f32Vector * 2.f;
			TestUtils::Vector4_AreEqual(f32VectorResult, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4_s32 s32Vector(1, 2, 3, 4);
			HD_Vector4_s32 s32VectorResult = s32Vector * 2;
			TestUtils::Vector4_AreEqual(s32VectorResult, 2, 4, 6, 8);

			HD_Vector4_u32 u32Vector(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32VectorResult = u32Vector * 2u;
			TestUtils::Vector4_AreEqual(u32VectorResult, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32VectorResult = 2.f * f32Vector;
			TestUtils::Vector4_AreEqual(f32VectorResult, 2.f, 4.f, 6.f, 8.f);

			HD_Vector4_s32 s32Vector(1, 2, 3, 4);
			HD_Vector4_s32 s32VectorResult = 2 * s32Vector;
			TestUtils::Vector4_AreEqual(s32VectorResult, 2, 4, 6, 8);

			HD_Vector4_u32 u32Vector(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32VectorResult = 2u * u32Vector;
			TestUtils::Vector4_AreEqual(u32VectorResult, 2u, 4u, 6u, 8u);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector4_f32 f32Vector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4_f32 f32VectorResult = f32Vector / 2.f;
			TestUtils::Vector4_AreEqual(f32VectorResult, 0.5f, 1.f, 1.5f, 2.f);

			HD_Vector4_s32 s32Vector(1, 2, 3, 4);
			HD_Vector4_s32 s32VectorResult = s32Vector / 2;
			TestUtils::Vector4_AreEqual(s32VectorResult, 0, 1, 1, 2);

			HD_Vector4_u32 u32Vector(1u, 2u, 3u, 4u);
			HD_Vector4_u32 u32VectorResult = u32Vector / 2u;
			TestUtils::Vector4_AreEqual(u32VectorResult, 0u, 1u, 1u, 2u);
		}

		TEST_METHOD(Operator_Equals)
		{
			HD_Vector4_f32 f32Vector1(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector2(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector3(1.f, 1.f, 1.f, 1.f);

			Assert::IsTrue(f32Vector1 == f32Vector2);
			Assert::IsFalse(f32Vector1 == f32Vector3);
		}

		TEST_METHOD(Operator_Not_Equals)
		{
			HD_Vector4_f32 f32Vector1(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector2(0.f, 0.f, 0.f, 0.f);
			HD_Vector4_f32 f32Vector3(1.f, 1.f, 1.f, 1.f);

			Assert::IsFalse(f32Vector1 != f32Vector2);
			Assert::IsTrue(f32Vector1 != f32Vector3);
		}
	};
}
