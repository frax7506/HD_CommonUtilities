#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_AABB_2D.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_AABB_2D_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_AABB_2Df aabb2d;
			TestUtils::Vector2_AreEqual(aabb2d.myMin, 0.f, 0.f);
			TestUtils::Vector2_AreEqual(aabb2d.myMax, 0.f, 0.f);
		}

		TEST_METHOD(Constructor_Min_And_Max)
		{
			HD_Vector2f min(-1.f, -1.f);
			HD_Vector2f max(1.f, 1.f);
			HD_AABB_2Df aabb2d(min, max);
			TestUtils::Vector2_AreEqual(aabb2d.myMin, -1.f, -1.f);
			TestUtils::Vector2_AreEqual(aabb2d.myMax, 1.f, 1.f);
		}

		TEST_METHOD(Contains)
		{
			HD_Vector2f min(-1.f, -1.f);
			HD_Vector2f max(3.f, 3.f);
			HD_AABB_2Df aabb2d(min, max);

			Assert::IsTrue(aabb2d.Contains({ 2.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 2.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 0.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 0.f }));
			Assert::IsTrue(aabb2d.Contains({ 2.f, 0.f }));

			Assert::IsTrue(aabb2d.Contains({ 3.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 3.f, 3.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 3.f }));
			Assert::IsTrue(aabb2d.Contains({ -1.f, 3.f }));
			Assert::IsTrue(aabb2d.Contains({ -1.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ -1.f, -1.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, -1.f }));
			Assert::IsTrue(aabb2d.Contains({ 3.f, -1.f }));

			Assert::IsFalse(aabb2d.Contains({ 4.f, 1.f }));
			Assert::IsFalse(aabb2d.Contains({ 4.f, 4.f }));
			Assert::IsFalse(aabb2d.Contains({ 1.f, 4.f }));
			Assert::IsFalse(aabb2d.Contains({ -2.f, 4.f }));
			Assert::IsFalse(aabb2d.Contains({ -2.f, 1.f }));
			Assert::IsFalse(aabb2d.Contains({ -2.f, -2.f }));
			Assert::IsFalse(aabb2d.Contains({ 1.f, -2.f }));
			Assert::IsFalse(aabb2d.Contains({ 4.f, -2.f }));
		}

		TEST_METHOD(Intersects)
		{
			HD_Vector2f min(-1.f, -1.f);
			HD_Vector2f max(3.f, 3.f);
			HD_AABB_2Df aabb2d(min, max);

			Assert::IsTrue(aabb2d.Intersects(aabb2d));

			Assert::IsTrue(aabb2d.Intersects({ { 0.f, 0.f }, { 4.f, 4.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { -2.f, 0.f }, { 2.f, 4.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { -2.f, -2.f }, { 2.f, 2.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { 0.f, -2.f }, { 4.f, 2.f } }));

			Assert::IsTrue(aabb2d.Intersects({ { 1.f, 1.f }, { 5.f, 5.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { -3.f, 1.f }, { 1.f, 5.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { -3.f, -3.f }, { 1.f, 1.f } }));
			Assert::IsTrue(aabb2d.Intersects({ { 1.f, -3.f }, { 5.f, 1.f } }));

			Assert::IsFalse(aabb2d.Intersects({ { 4.f, 4.f }, { 8.f, 8.f } }));
			Assert::IsFalse(aabb2d.Intersects({ { -6.f, 4.f }, { -2.f, 8.f } }));
			Assert::IsFalse(aabb2d.Intersects({ { -6.f, -6.f }, { -2.f, -2.f } }));
			Assert::IsFalse(aabb2d.Intersects({ { 4.f, -6.f }, { 8.f, -2.f } }));
		}
	};
}
