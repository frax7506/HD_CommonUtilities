#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_AABB_3D.h"

#include "TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_AABB_3D_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_AABB_3Df aabb3d;
			TestUtils::Vector3_AreEqual(aabb3d.myMin, 0.f, 0.f, 0.f);
			TestUtils::Vector3_AreEqual(aabb3d.myMax, 0.f, 0.f, 0.f);
		}

		TEST_METHOD(Constructor_Min_And_Max)
		{
			HD_Vector3f min(-2.f, -2.f, -2.f);
			HD_Vector3f max(2.f, 2.f, 2.f);
			HD_AABB_3Df aabb3d(min, max);
			TestUtils::Vector3_AreEqual(aabb3d.myMin, -2.f, -2.f, -2.f);
			TestUtils::Vector3_AreEqual(aabb3d.myMax, 2.f, 2.f, 2.f);
		}

		TEST_METHOD(Contains)
		{
			HD_Vector3f min(-2.f, -2.f, -2.f);
			HD_Vector3f max(2.f, 2.f, 2.f);
			HD_AABB_3Df aabb3d(min, max);

			Assert::IsTrue(aabb3d.Contains({ -1.f, 1.f, -1.f }));
			Assert::IsTrue(aabb3d.Contains({ 1.f, 1.f, -1.f }));
			Assert::IsTrue(aabb3d.Contains({ -1.f, -1.f, -1.f }));
			Assert::IsTrue(aabb3d.Contains({ 1.f, -1.f, -1.f }));
			Assert::IsTrue(aabb3d.Contains({ -1.f, 1.f, 1.f }));
			Assert::IsTrue(aabb3d.Contains({ 1.f, 1.f, 1.f }));
			Assert::IsTrue(aabb3d.Contains({ -1.f, -1.f, 1.f }));
			Assert::IsTrue(aabb3d.Contains({ 1.f, -1.f, 1.f }));

			Assert::IsFalse(aabb3d.Contains({ -3.f, 3.f, -3.f }));
			Assert::IsFalse(aabb3d.Contains({ 3.f, 3.f, -3.f }));
			Assert::IsFalse(aabb3d.Contains({ -3.f, -3.f, -3.f }));
			Assert::IsFalse(aabb3d.Contains({ 3.f, -3.f, -3.f }));
			Assert::IsFalse(aabb3d.Contains({ -3.f, 3.f, 3.f }));
			Assert::IsFalse(aabb3d.Contains({ 3.f, 3.f, 3.f }));
			Assert::IsFalse(aabb3d.Contains({ -3.f, -3.f, 3.f }));
			Assert::IsFalse(aabb3d.Contains({ 3.f, -3.f, 3.f }));
		}

		TEST_METHOD(Intersects)
		{
			HD_Vector3f min(-2.f, -2.f, -2.f);
			HD_Vector3f max(2.f, 2.f, 2.f);
			HD_AABB_3Df aabb3d(min, max);

			Assert::IsTrue(aabb3d.Intersects(aabb3d));

			Assert::IsTrue(aabb3d.Intersects({ { -2.f, 0.f, -2.f }, { 0.f, 2.f, 0.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { 0.f, 0.f, -2.f }, { 2.f, 2.f, 0.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { -2.f, -2.f, -2.f }, { 0.f, 0.f, 0.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { 0.f, -2.f, -2.f }, { 2.f, 0.f, 0.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { -2.f, 0.f, 0.f }, { 0.f, 2.f, 2.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { 0.f, 0.f, 0.f }, { 2.f, 2.f, 2.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { -2.f, -2.f, 0.f }, { 0.f, 0.f, 2.f } }));
			Assert::IsTrue(aabb3d.Intersects({ { 0.f, -2.f, 0.f }, { 2.f, 0.f, 2.f } }));

			Assert::IsFalse(aabb3d.Intersects({ { -5.f, 3.f, -5.f }, { -3.f, 5.f, -3.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { 3.f, 3.f, -5.f }, { 5.f, 5.f, -3.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { -5.f, -5.f, -5.f }, { -3.f, -3.f, -3.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { 3.f, -5.f, -5.f }, { 5.f, -3.f, -3.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { -5.f, 3.f, 3.f }, { -3.f, 5.f, 5.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { 3.f, 3.f, 3.f }, { 5.f, 5.f, 5.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { -5.f, -5.f, 3.f }, { -3.f, -3.f, 5.f } }));
			Assert::IsFalse(aabb3d.Intersects({ { 3.f, -5.f, 3.f }, { 5.f, -3.f, 5.f } }));
		}
	};
}
