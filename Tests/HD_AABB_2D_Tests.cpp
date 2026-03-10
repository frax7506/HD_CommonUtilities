#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_AABB_2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_AABB_2D_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_AABB_2D aabb2d;
			Assert::AreEqual(aabb2d.myCenter.myX, 0.f);
			Assert::AreEqual(aabb2d.myCenter.myY, 0.f);
			Assert::AreEqual(aabb2d.myHalfSize, 0.f);
		}

		TEST_METHOD(Constructor_Center_And_Size)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_AABB_2D aabb2d(center, 1.f);
			Assert::AreEqual(aabb2d.myCenter.myX, 1.f);
			Assert::AreEqual(aabb2d.myCenter.myY, 1.f);
			Assert::AreEqual(aabb2d.myHalfSize, 0.5f);
		}

		TEST_METHOD(Contains)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_AABB_2D aabb2d(center, 2.f);

			Assert::IsTrue(aabb2d.Contains({ 1.f, 1.f }));

			Assert::IsTrue(aabb2d.Contains({ 1.5f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 1.5f }));
			Assert::IsTrue(aabb2d.Contains({ 0.5f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 0.5f }));

			Assert::IsTrue(aabb2d.Contains({ 2.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 2.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 2.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 1.f }));
			Assert::IsTrue(aabb2d.Contains({ 0.f, 0.f }));
			Assert::IsTrue(aabb2d.Contains({ 1.f, 0.f }));
			Assert::IsTrue(aabb2d.Contains({ 2.f, 0.f }));

			Assert::IsFalse(aabb2d.Contains({ 3.f, 1.f }));
			Assert::IsFalse(aabb2d.Contains({ 3.f, 2.f }));
			Assert::IsFalse(aabb2d.Contains({ 3.f, 3.f }));
			Assert::IsFalse(aabb2d.Contains({ 2.f, 3.f }));
			Assert::IsFalse(aabb2d.Contains({ 1.f, 3.f }));
			Assert::IsFalse(aabb2d.Contains({ 0.f, 3.f }));
			Assert::IsFalse(aabb2d.Contains({ -1.f, 3.f }));
			Assert::IsFalse(aabb2d.Contains({ -1.f, 2.f }));
			Assert::IsFalse(aabb2d.Contains({ -1.f, 1.f }));
			Assert::IsFalse(aabb2d.Contains({ -1.f, 0.f }));
			Assert::IsFalse(aabb2d.Contains({ -1.f, -1.f }));
			Assert::IsFalse(aabb2d.Contains({ 0.f, -1.f }));
			Assert::IsFalse(aabb2d.Contains({ 1.f, -1.f }));
			Assert::IsFalse(aabb2d.Contains({ 2.f, -1.f }));
			Assert::IsFalse(aabb2d.Contains({ 3.f, -1.f }));
			Assert::IsFalse(aabb2d.Contains({ 3.f, 0.f }));
		}

		TEST_METHOD(Intersects)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_AABB_2D aabb2d(center, 2.f);

			Assert::IsTrue(aabb2d.Intersects(aabb2d));

			Assert::IsTrue(aabb2d.Intersects({ { 2.f, 2.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 0.f, 2.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 0.f, 0.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 2.f, 0.f }, 2.f }));

			Assert::IsTrue(aabb2d.Intersects({ { 3.f, 3.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 1.f, 3.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { -1.f, 3.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { -1.f, 1.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { -1.f, -1.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 1.f, -1.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 3.f, -1.f }, 2.f }));
			Assert::IsTrue(aabb2d.Intersects({ { 3.f, 1.f }, 2.f }));

			Assert::IsFalse(aabb2d.Intersects({ { 4.f, 1.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { 4.f, 4.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { 1.f, 4.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { -2.f, 4.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { -2.f, 1.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { -2.f, -2.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { 1.f, -2.f }, 2.f }));
			Assert::IsFalse(aabb2d.Intersects({ { 4.f, -1.f }, 2.f }));
		}
	};
}
