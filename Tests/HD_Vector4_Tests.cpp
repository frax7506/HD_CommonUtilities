#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Vector4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Vector4_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Vector4f floatVector;
			Assert::AreEqual(floatVector.myX, 0.f);
			Assert::AreEqual(floatVector.myY, 0.f);
			Assert::AreEqual(floatVector.myZ, 0.f);
			Assert::AreEqual(floatVector.myW, 0.f);

			HD_Vector4i intVector;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 0);
			Assert::AreEqual(intVector.myZ, 0);
			Assert::AreEqual(intVector.myW, 0);

			// htodo: complement this test file with tests for HD_Vector4ui
		}

		TEST_METHOD(Constructor_X_And_Y_And_Z_And_W)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);
			Assert::AreEqual(floatVector.myZ, 3.f);
			Assert::AreEqual(floatVector.myW, 4.f);

			HD_Vector4i intVector(5, 6, 7, 8);
			Assert::AreEqual(intVector.myX, 5);
			Assert::AreEqual(intVector.myY, 6);
			Assert::AreEqual(intVector.myZ, 7);
			Assert::AreEqual(intVector.myW, 8);
		}

		TEST_METHOD(Constructor_Copy)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(floatVector1);
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);
			Assert::AreEqual(floatVector2.myZ, 3.f);
			Assert::AreEqual(floatVector2.myW, 4.f);

			HD_Vector4i intVector1(5, 6, 7, 8);
			HD_Vector4i intVector2(intVector1);
			Assert::AreEqual(intVector2.myX, 5);
			Assert::AreEqual(intVector2.myY, 6);
			Assert::AreEqual(intVector2.myZ, 7);
			Assert::AreEqual(intVector2.myW, 8);
		}

		TEST_METHOD(Set)
		{
			HD_Vector4f floatVector;
			floatVector.Set(1.f, 2.f, 3.f, 4.f);
			Assert::AreEqual(floatVector.myX, 1.f);
			Assert::AreEqual(floatVector.myY, 2.f);
			Assert::AreEqual(floatVector.myZ, 3.f);
			Assert::AreEqual(floatVector.myW, 4.f);

			HD_Vector4i intVector;
			intVector.Set(5, 6, 7, 8);
			Assert::AreEqual(intVector.myX, 5);
			Assert::AreEqual(intVector.myY, 6);
			Assert::AreEqual(intVector.myZ, 7);
			Assert::AreEqual(intVector.myW, 8);
		}

		TEST_METHOD(Operator_Plus)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4f floatVectorResult = floatVector1 + floatVector2;
			Assert::AreEqual(floatVectorResult.myX, 6.f);
			Assert::AreEqual(floatVectorResult.myY, 8.f);
			Assert::AreEqual(floatVectorResult.myZ, 10.f);
			Assert::AreEqual(floatVectorResult.myW, 12.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			HD_Vector4i intVectorResult = intVector1 + intVector2;
			Assert::AreEqual(intVectorResult.myX, 6);
			Assert::AreEqual(intVectorResult.myY, 8);
			Assert::AreEqual(intVectorResult.myZ, 10);
			Assert::AreEqual(intVectorResult.myW, 12);
		}

		TEST_METHOD(Operator_Minus)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			HD_Vector4f floatVectorResult = floatVector1 - floatVector2;
			Assert::AreEqual(floatVectorResult.myX, -4.f);
			Assert::AreEqual(floatVectorResult.myY, -4.f);
			Assert::AreEqual(floatVectorResult.myZ, -4.f);
			Assert::AreEqual(floatVectorResult.myW, -4.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			HD_Vector4i intVectorResult = intVector1 - intVector2;
			Assert::AreEqual(intVectorResult.myX, -4);
			Assert::AreEqual(intVectorResult.myY, -4);
			Assert::AreEqual(intVectorResult.myZ, -4);
			Assert::AreEqual(intVectorResult.myW, -4);
		}

		TEST_METHOD(Operator_Multiplication_Vector_With_Constant)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = floatVector * 2.f;
			Assert::AreEqual(floatVectorResult.myX, 2.f);
			Assert::AreEqual(floatVectorResult.myY, 4.f);
			Assert::AreEqual(floatVectorResult.myZ, 6.f);
			Assert::AreEqual(floatVectorResult.myW, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = intVector * 2;
			Assert::AreEqual(intVectorResult.myX, 2);
			Assert::AreEqual(intVectorResult.myY, 4);
			Assert::AreEqual(intVectorResult.myZ, 6);
			Assert::AreEqual(intVectorResult.myW, 8);
		}

		TEST_METHOD(Operator_Multiplication_Constant_With_Vector)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = 2.f * floatVector;
			Assert::AreEqual(floatVectorResult.myX, 2.f);
			Assert::AreEqual(floatVectorResult.myY, 4.f);
			Assert::AreEqual(floatVectorResult.myZ, 6.f);
			Assert::AreEqual(floatVectorResult.myW, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = 2 * intVector;
			Assert::AreEqual(intVectorResult.myX, 2);
			Assert::AreEqual(intVectorResult.myY, 4);
			Assert::AreEqual(intVectorResult.myZ, 6);
			Assert::AreEqual(intVectorResult.myW, 8);
		}

		TEST_METHOD(Operator_Division_Vector_With_Constant)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVectorResult = floatVector / 2.f;
			Assert::AreEqual(floatVectorResult.myX, 0.5f);
			Assert::AreEqual(floatVectorResult.myY, 1.f);
			Assert::AreEqual(floatVectorResult.myZ, 1.5f);
			Assert::AreEqual(floatVectorResult.myW, 2.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			HD_Vector4i intVectorResult = intVector / 2;
			Assert::AreEqual(intVectorResult.myX, 0);
			Assert::AreEqual(intVectorResult.myY, 1);
			Assert::AreEqual(intVectorResult.myZ, 1);
			Assert::AreEqual(intVectorResult.myW, 2);
		}

		TEST_METHOD(Operator_Assignment)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2;
			floatVector2 = floatVector1;
			Assert::AreEqual(floatVector2.myX, 1.f);
			Assert::AreEqual(floatVector2.myY, 2.f);
			Assert::AreEqual(floatVector2.myZ, 3.f);
			Assert::AreEqual(floatVector2.myW, 4.f);

			HD_Vector4i intVector1(5, 6, 7, 8);
			HD_Vector4i intVector2;
			intVector2 = intVector1;
			Assert::AreEqual(intVector2.myX, 5);
			Assert::AreEqual(intVector2.myY, 6);
			Assert::AreEqual(intVector2.myZ, 7);
			Assert::AreEqual(intVector2.myW, 8);
		}

		TEST_METHOD(Operator_PlusEquals)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			floatVector1 += floatVector2;
			Assert::AreEqual(floatVector1.myX, 6.f);
			Assert::AreEqual(floatVector1.myY, 8.f);
			Assert::AreEqual(floatVector1.myZ, 10.f);
			Assert::AreEqual(floatVector1.myW, 12.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			intVector1 += intVector2;
			Assert::AreEqual(intVector1.myX, 6);
			Assert::AreEqual(intVector1.myY, 8);
			Assert::AreEqual(intVector1.myZ, 10);
			Assert::AreEqual(intVector1.myW, 12);
		}

		TEST_METHOD(Operator_MinusEquals)
		{
			HD_Vector4f floatVector1(1.f, 2.f, 3.f, 4.f);
			HD_Vector4f floatVector2(5.f, 6.f, 7.f, 8.f);
			floatVector1 -= floatVector2;
			Assert::AreEqual(floatVector1.myX, -4.f);
			Assert::AreEqual(floatVector1.myY, -4.f);
			Assert::AreEqual(floatVector1.myZ, -4.f);
			Assert::AreEqual(floatVector1.myZ, -4.f);

			HD_Vector4i intVector1(1, 2, 3, 4);
			HD_Vector4i intVector2(5, 6, 7, 8);
			intVector1 -= intVector2;
			Assert::AreEqual(intVector1.myX, -4);
			Assert::AreEqual(intVector1.myY, -4);
			Assert::AreEqual(intVector1.myZ, -4);
			Assert::AreEqual(intVector1.myW, -4);
		}

		TEST_METHOD(Operator_MultiplicationEquals)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			floatVector *= 2.f;
			Assert::AreEqual(floatVector.myX, 2.f);
			Assert::AreEqual(floatVector.myY, 4.f);
			Assert::AreEqual(floatVector.myZ, 6.f);
			Assert::AreEqual(floatVector.myW, 8.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			intVector *= 2;
			Assert::AreEqual(intVector.myX, 2);
			Assert::AreEqual(intVector.myY, 4);
			Assert::AreEqual(intVector.myZ, 6);
			Assert::AreEqual(intVector.myW, 8);
		}

		TEST_METHOD(Operator_DivisionEquals)
		{
			HD_Vector4f floatVector(1.f, 2.f, 3.f, 4.f);
			floatVector /= 2.f;
			Assert::AreEqual(floatVector.myX, 0.5f);
			Assert::AreEqual(floatVector.myY, 1.f);
			Assert::AreEqual(floatVector.myZ, 1.5f);
			Assert::AreEqual(floatVector.myW, 2.f);

			HD_Vector4i intVector(1, 2, 3, 4);
			intVector /= 2;
			Assert::AreEqual(intVector.myX, 0);
			Assert::AreEqual(intVector.myY, 1);
			Assert::AreEqual(intVector.myZ, 1);
			Assert::AreEqual(intVector.myW, 2);
		}
	};
}
