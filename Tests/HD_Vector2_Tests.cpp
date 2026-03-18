#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Vector2_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector2f floatVector;
			Assert::AreEqual(floatVector.myX, 0.f);
			Assert::AreEqual(floatVector.myY, 0.f);

			HD_Vector2i intVector;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 0);
		}

		TEST_METHOD(Constructor_X_And_Y)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);

			HD_Vector2i intVector(3, 4);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(floatVector1);
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);

			HD_Vector2i intVector1(3, 4);
			HD_Vector2i intVector2(intVector1);
			Assert::AreEqual(intVector2.myX, 3);
			Assert::AreEqual(intVector2.myY, 4);
		}

		TEST_METHOD(Set)
		{
			HD_Vector2f floatVector;
			floatVector.Set(1.f, 2.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);

			HD_Vector2i intVector;
			intVector.Set(3, 4);
			Assert::AreEqual(intVector.myX, 3);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Length)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			float length = floatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(length, HD_Sqrtf(2.f)));
		}

		TEST_METHOD(Length2)
		{
			HD_Vector2f floatVector(1.f, 1.f);
			float floatLength2 = floatVector.Length2();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(floatLength2, 2.f));

			HD_Vector2i intVector(2, 2);
			int intLength2 = intVector.Length2();
			Assert::AreEqual(intLength2, 8);
		}

		TEST_METHOD(Normalize)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			floatVector.Normalize();
			float length = floatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(length, 1.f));
		}

		TEST_METHOD(GetNormalized)
		{
			HD_Vector2f floatVector(2.f, 2.f);
			HD_Vector2f normalizedFloatVector = floatVector.GetNormalized();
			float floatVectorLength = floatVector.Length();
			float normalizedFloatVectorLength = normalizedFloatVector.Length();
			Assert::IsTrue(HD_Math::AreFloatValuesClose(floatVectorLength, HD_Sqrtf(8.f)));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(normalizedFloatVectorLength, 1.f));
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

			float upDotUp = up.Dot(up);
			float upDotUpRight = up.Dot(upRight);
			float upDotRight = up.Dot(right);
			float upDotDownRight = up.Dot(downRight);
			float upDotDown = up.Dot(down);
			float upDotDownLeft = up.Dot(downLeft);
			float upDotLeft = up.Dot(left);
			float upDotUpLeft = up.Dot(upLeft);

			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotUp, 1.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotUpRight, F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotRight, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotDownRight, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotDown, -1.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotDownLeft, -1.f * F_ONE_OVER_SQRT_TWO));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotLeft, 0.f));
			Assert::IsTrue(HD_Math::AreFloatValuesClose(upDotUpLeft, F_ONE_OVER_SQRT_TWO));
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2;
			floatVector2 = floatVector1;
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2;
			intVector2 = intVector1;
			Assert::AreEqual(intVector2.myX, 1);
			Assert::AreEqual(intVector2.myY, 2);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatResult = floatVector1 + floatVector2;
			Assert::AreEqual(floatResult.myX, 4.f);
			Assert::AreEqual(floatResult.myY, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intResult = intVector1 + intVector2;
			Assert::AreEqual(intResult.myX, 4);
			Assert::AreEqual(intResult.myY, 6);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			HD_Vector2f floatResult = floatVector1 - floatVector2;
			Assert::AreEqual(floatResult.myX, -2.f);
			Assert::AreEqual(floatResult.myY, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			HD_Vector2i intResult = intVector1 - intVector2;
			Assert::AreEqual(intResult.myX, -2);
			Assert::AreEqual(intResult.myY, -2);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = floatVector * 2.f;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = intVector * 2;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = 2.f * floatVector;
			Assert::AreEqual(floatResult.myX, 2.f);
			Assert::AreEqual(floatResult.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = 2 * intVector;
			Assert::AreEqual(intResult.myX, 2);
			Assert::AreEqual(intResult.myY, 4);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			HD_Vector2f floatResult = floatVector / 2.f;
			Assert::AreEqual(floatResult.myX, 0.5f);
			Assert::AreEqual(floatResult.myY, 1.f);

			HD_Vector2i intVector(1, 2);
			HD_Vector2i intResult = intVector / 2;
			Assert::AreEqual(intResult.myX, 0);
			Assert::AreEqual(intResult.myY, 1);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 += floatVector2;
			Assert::AreEqual(floatVector1.myX, 4.f);
			Assert::AreEqual(floatVector1.myY, 6.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 += intVector2;
			Assert::AreEqual(intVector1.myX, 4);
			Assert::AreEqual(intVector1.myY, 6);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector2f floatVector1(1.f, 2.f);
			HD_Vector2f floatVector2(3.f, 4.f);
			floatVector1 -= floatVector2;
			Assert::AreEqual(floatVector1.myX, -2.f);
			Assert::AreEqual(floatVector1.myY, -2.f);

			HD_Vector2i intVector1(1, 2);
			HD_Vector2i intVector2(3, 4);
			intVector1 -= intVector2;
			Assert::AreEqual(intVector1.myX, -2);
			Assert::AreEqual(intVector1.myY, -2);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector *= 2.f;
			Assert::AreEqual(floatVector.myX, 2.f);
			Assert::AreEqual(floatVector.myY, 4.f);

			HD_Vector2i intVector(1, 2);
			intVector *= 2;
			Assert::AreEqual(intVector.myX, 2);
			Assert::AreEqual(intVector.myY, 4);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector2f floatVector(1.f, 2.f);
			floatVector /= 2.f;
			Assert::AreEqual(floatVector.myX, 0.5f);
			Assert::AreEqual(floatVector.myY, 1.f);

			HD_Vector2i intVector(1, 2);
			intVector /= 2;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 1);
		}
	};
}
