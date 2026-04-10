#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_ExeArgs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define DEBUG_ARGC 16

static char* debugExeCommandLine[DEBUG_ARGC] = { "C/testy",
	"-aIntName", "4",
	"-aFloatName", "2.5",
	"-aBoolName", "1",
	"-aVector2Name", "0.1", "0.2",
	"-aVector3Name", "0.1", "0.2", "0.3",
	"-aStringName", "haha"
};

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_ExeArgs_Test)
	{
	public:
		TEST_METHOD(Init)
		{
			HD_ExeArgs exeArgs;
			exeArgs.Init(DEBUG_ARGC, debugExeCommandLine);

			const HD_String* intValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aIntName");
			const HD_String* floatValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aFloatName");
			const HD_String* boolValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aBoolName");
			const HD_String* vector2ValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aVector2Name");
			const HD_String* vector3ValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aVector3Name");
			const HD_String* stringValueAsString = exeArgs.myExeArgToValueMap.GetIfExists("aStringName");

			Assert::IsNotNull(intValueAsString);
			Assert::IsNotNull(floatValueAsString);
			Assert::IsNotNull(boolValueAsString);
			Assert::IsNotNull(vector2ValueAsString);
			Assert::IsNotNull(vector3ValueAsString);
			Assert::IsNotNull(stringValueAsString);

			Assert::IsTrue(*intValueAsString == "4");
			Assert::IsTrue(*floatValueAsString == "2.5");
			Assert::IsTrue(*boolValueAsString == "1");
			Assert::IsTrue(*vector2ValueAsString == "0.1 0.2");
			Assert::IsTrue(*vector3ValueAsString == "0.1 0.2 0.3");
			Assert::IsTrue(*stringValueAsString == "haha");
		}

		TEST_METHOD(IsPresent)
		{
			HD_ExeArgs exeArgs;
			exeArgs.Init(DEBUG_ARGC, debugExeCommandLine);

			Assert::IsTrue(exeArgs.IsPresent("aIntName"));
			Assert::IsTrue(exeArgs.IsPresent("aFloatName"));
			Assert::IsTrue(exeArgs.IsPresent("aBoolName"));
			Assert::IsTrue(exeArgs.IsPresent("aVector2Name"));
			Assert::IsTrue(exeArgs.IsPresent("aVector3Name"));
			Assert::IsTrue(exeArgs.IsPresent("aStringName"));
			Assert::IsFalse(exeArgs.IsPresent("aNotPresentName"));
		}

		TEST_METHOD(GetValue)
		{
			HD_ExeArgs exeArgs;
			exeArgs.Init(DEBUG_ARGC, debugExeCommandLine);

			s32 intValue = exeArgs.GetValue<s32>("aIntName");
			f32 floatValue = exeArgs.GetValue<f32>("aFloatName");
			bool boolValue = exeArgs.GetValue<bool>("aBoolName");
			HD_Vector2f vector2Value = exeArgs.GetValue<HD_Vector2f>("aVector2Name");
			HD_Vector3f vector3Value = exeArgs.GetValue<HD_Vector3f>("aVector3Name");
			HD_String stringValue = exeArgs.GetValue<HD_String>("aStringName");

			Assert::AreEqual(intValue, 4);
			Assert::AreEqual(floatValue, 2.5f);
			Assert::IsTrue(boolValue);
			Assert::AreEqual(vector2Value.myX, 0.1f);
			Assert::AreEqual(vector2Value.myY, 0.2f);
			Assert::AreEqual(vector3Value.myX, 0.1f);
			Assert::AreEqual(vector3Value.myY, 0.2f);
			Assert::AreEqual(vector3Value.myZ, 0.3f);
			Assert::IsTrue(stringValue == "haha");
		}
	};
}
