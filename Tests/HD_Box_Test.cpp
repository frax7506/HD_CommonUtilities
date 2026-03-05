#include "stdafx.h"
#include "CppUnitTest.h"

#include "HD_Box.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_Box_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_Box box;
			Assert::AreEqual(box.myCenter.myX, 0.f);
			Assert::AreEqual(box.myCenter.myY, 0.f);
			Assert::AreEqual(box.myHalfSize, 0.f);
		}

		TEST_METHOD(Constructor_Center_And_Size)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 1.f);
			Assert::AreEqual(box.myCenter.myX, 1.f);
			Assert::AreEqual(box.myCenter.myY, 1.f);
			Assert::AreEqual(box.myHalfSize, 0.5f);
		}

		TEST_METHOD(Contains)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 2.f);

			Assert::IsTrue(box.Contains({ 1.f, 1.f }));

			Assert::IsTrue(box.Contains({ 1.5f, 1.f }));
			Assert::IsTrue(box.Contains({ 1.f, 1.5f }));
			Assert::IsTrue(box.Contains({ 0.5f, 1.f }));
			Assert::IsTrue(box.Contains({ 1.f, 0.5f }));

			Assert::IsTrue(box.Contains({ 2.f, 1.f }));
			Assert::IsTrue(box.Contains({ 2.f, 2.f }));
			Assert::IsTrue(box.Contains({ 1.f, 2.f }));
			Assert::IsTrue(box.Contains({ 0.f, 2.f }));
			Assert::IsTrue(box.Contains({ 0.f, 1.f }));
			Assert::IsTrue(box.Contains({ 0.f, 0.f }));
			Assert::IsTrue(box.Contains({ 1.f, 0.f }));
			Assert::IsTrue(box.Contains({ 2.f, 0.f }));

			Assert::IsFalse(box.Contains({ 3.f, 1.f }));
			Assert::IsFalse(box.Contains({ 3.f, 2.f }));
			Assert::IsFalse(box.Contains({ 3.f, 3.f }));
			Assert::IsFalse(box.Contains({ 2.f, 3.f }));
			Assert::IsFalse(box.Contains({ 1.f, 3.f }));
			Assert::IsFalse(box.Contains({ 0.f, 3.f }));
			Assert::IsFalse(box.Contains({ -1.f, 3.f }));
			Assert::IsFalse(box.Contains({ -1.f, 2.f }));
			Assert::IsFalse(box.Contains({ -1.f, 1.f }));
			Assert::IsFalse(box.Contains({ -1.f, 0.f }));
			Assert::IsFalse(box.Contains({ -1.f, -1.f }));
			Assert::IsFalse(box.Contains({ 0.f, -1.f }));
			Assert::IsFalse(box.Contains({ 1.f, -1.f }));
			Assert::IsFalse(box.Contains({ 2.f, -1.f }));
			Assert::IsFalse(box.Contains({ 3.f, -1.f }));
			Assert::IsFalse(box.Contains({ 3.f, 0.f }));
		}

		TEST_METHOD(Intersects)
		{
			HD_Vector2f center(1.f, 1.f);
			HD_Box box(center, 2.f);

			Assert::IsTrue(box.Intersects(box));

			Assert::IsTrue(box.Intersects({ { 2.f, 2.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 0.f, 2.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 0.f, 0.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 2.f, 0.f }, 2.f }));

			Assert::IsTrue(box.Intersects({ { 3.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 1.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, 3.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, 1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { -1.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 1.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 3.f, -1.f }, 2.f }));
			Assert::IsTrue(box.Intersects({ { 3.f, 1.f }, 2.f }));

			Assert::IsFalse(box.Intersects({ { 4.f, 1.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 4.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 1.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, 4.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, 1.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { -2.f, -2.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 1.f, -2.f }, 2.f }));
			Assert::IsFalse(box.Intersects({ { 4.f, -1.f }, 2.f }));
		}
	};
}
