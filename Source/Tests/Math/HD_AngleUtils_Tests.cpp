#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_AngleUtils.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_AngleUtils_Test)
	{
	public:
		TEST_METHOD(SignedAngleBetweenVectors)
		{
			HD_Vector2_f32 vector1(-1.f, 1.f);
			HD_Vector2_f32 vector2(1.f, 1.f);

			f32 signedAngleBetweenVectors1 = HD_AngleUtils::SignedAngleBetweenVectors(HD_Vector2_f32::Up, vector1);
			f32 signedAngleBetweenVectors2 = HD_AngleUtils::SignedAngleBetweenVectors(HD_Vector2_f32::Up, vector2);

			Assert::AreEqual(signedAngleBetweenVectors1, -1.f * (F_PI / 4.f), F32_EQUAL_TOLERANCE);
			Assert::AreEqual(signedAngleBetweenVectors2, F_PI / 4.f, F32_EQUAL_TOLERANCE);
		}

		TEST_METHOD(AngleBetweenVectors)
		{
			HD_Vector2_f32 vector1(-1.f, 1.f);
			HD_Vector2_f32 vector2(1.f, 1.f);

			f32 angleBetweenVectors1 = HD_AngleUtils::AngleBetweenVectors(HD_Vector2_f32::Up, vector1);
			f32 angleBetweenVectors2 = HD_AngleUtils::AngleBetweenVectors(HD_Vector2_f32::Up, vector2);

			Assert::AreEqual(angleBetweenVectors1, F_PI / 4.f, F32_EQUAL_TOLERANCE);
			Assert::AreEqual(angleBetweenVectors2, F_PI / 4.f, F32_EQUAL_TOLERANCE);
		}
	};
}

