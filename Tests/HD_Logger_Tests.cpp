#include "stdafx.h"
#include "CppUnitTest.h"

// Hack to access private members
#define protected public
#define private public

#include "HD_Logger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HD_CommonUtilities
{
	TEST_CLASS(HD_LogMessage_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_LogMessage message;
			Assert::IsNull(message.myData);
			Assert::AreEqual(static_cast<char>(message.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
		}

		TEST_METHOD(Constructor_Copy_NonWide)
		{
			HD_LogMessage message1("haha");
			HD_LogMessage message2(message1);

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(message2.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Constructor_Copy_Wide)
		{
			HD_LogMessage message1(L"haha");
			HD_LogMessage message2(message1);

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(message2.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}

		TEST_METHOD(Constructor_Move_NonWide)
		{
			HD_LogMessage message1("haha");
			HD_LogMessage message2(HD_Move(message1));

			Assert::IsNull(message1.myData);
			Assert::AreEqual(static_cast<char>(message1.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(message2.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Constructor_Move_Wide)
		{
			HD_LogMessage message1(L"haha");
			HD_LogMessage message2(HD_Move(message1));

			Assert::IsNull(message1.myData);
			Assert::AreEqual(static_cast<char>(message1.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(message2.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}

		TEST_METHOD(Constructor_CString_NonWide)
		{
			HD_LogMessage message("haha");

			Assert::IsNotNull(message.myData);
			Assert::AreEqual(HD_Strcmp(message.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(message.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Constructor_CString_Wide)
		{
			HD_LogMessage message(L"haha");

			Assert::IsNotNull(message.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(message.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(message.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}

		TEST_METHOD(Destructor_NonWide)
		{
			HD_LogMessage message("haha");
			message.~HD_LogMessage();

			Assert::IsNull(message.myData);
		}

		TEST_METHOD(Destructor_Wide)
		{
			HD_LogMessage message(L"haha");
			message.~HD_LogMessage();

			Assert::IsNull(message.myData);
		}

		TEST_METHOD(Operator_Assignment_Copy_NonWide)
		{
			HD_LogMessage message1("haha");
			HD_LogMessage message2;
			message2 = message1;

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(message2.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Operator_Assignment_Copy_Wide)
		{
			HD_LogMessage message1(L"haha");
			HD_LogMessage message2;
			message2 = message1;

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(message2.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}
		TEST_METHOD(Operator_Assignment_Move_NonWide)
		{
			HD_LogMessage message1("haha");
			HD_LogMessage message2;

			message2 = HD_Move(message1);

			Assert::IsNull(message1.myData);
			Assert::AreEqual(static_cast<char>(message1.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(message2.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Operator_Assignment_Move_Wide)
		{
			HD_LogMessage message1(L"haha");
			HD_LogMessage message2;

			message2 = HD_Move(message1);

			Assert::IsNull(message1.myData);
			Assert::AreEqual(static_cast<char>(message1.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));

			Assert::IsNotNull(message2.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(message2.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}

		TEST_METHOD(GetBuffer)
		{
			HD_LogMessage message1("haha");
			const char* message2 = message1.GetBuffer();
			Assert::AreEqual(memcmp(message2, "haha", 4), 0);

			// Should trigger assert
			//const wchar_t* assertTest = message1.GetWBuffer();
			//HD_Unused(assertTest);
		}

		TEST_METHOD(GetWBuffer)
		{
			HD_LogMessage message1(L"haha");
			const wchar_t* message2 = message1.GetWBuffer();
			Assert::AreEqual(memcmp(message2, L"haha", sizeof(wchar_t) * 4), 0);

			// Should trigger assert
			//const char* assertTest = message1.GetBuffer();
			//HD_Unused(assertTest);
		}

		TEST_METHOD(GetIsWide)
		{
			HD_LogMessage nonWide("haha");
			HD_LogMessage wide(L"haha");

			Assert::IsFalse(nonWide.GetIsWide());
			Assert::IsTrue(wide.GetIsWide());
		}
	};

	TEST_CLASS(HD_LogEntry_Test)
	{
	public:
		TEST_METHOD(Constructor)
		{
			HD_LogEntry logEntry;

			Assert::IsNull(logEntry.myLogMessage.myData);
			Assert::AreEqual(static_cast<char>(logEntry.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Invalid));
		}

		TEST_METHOD(Constructor_Copy_NonWide)
		{
			HD_LogEntry logEntry1("haha", eLogLevel_Log);
			HD_LogEntry logEntry2(logEntry1);

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(logEntry2.myLogMessage.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_Copy_Wide)
		{
			HD_LogEntry logEntry1(L"haha", eLogLevel_Log);
			HD_LogEntry logEntry2(logEntry1);

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(logEntry2.myLogMessage.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_Move_NonWide)
		{
			HD_LogEntry logEntry1("haha", eLogLevel_Log);
			HD_LogEntry logEntry2(HD_Move(logEntry1));

			Assert::IsNull(logEntry1.myLogMessage.myData);
			Assert::AreEqual(static_cast<char>(logEntry1.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
			Assert::AreEqual(static_cast<char>(logEntry1.myLogLevel), static_cast<char>(eLogLevel_Invalid));

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(logEntry2.myLogMessage.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_Move_Wide)
		{
			HD_LogEntry logEntry1(L"haha", eLogLevel_Log);
			HD_LogEntry logEntry2(HD_Move(logEntry1));

			Assert::IsNull(logEntry1.myLogMessage.myData);
			Assert::AreEqual(static_cast<char>(logEntry1.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
			Assert::AreEqual(static_cast<char>(logEntry1.myLogLevel), static_cast<char>(eLogLevel_Invalid));

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(logEntry2.myLogMessage.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_CString_NonWide)
		{
			HD_LogEntry logEntry("haha", eLogLevel_Log);

			Assert::IsNotNull(logEntry.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(logEntry.myLogMessage.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_CString_Wide)
		{
			HD_LogEntry logEntry(L"haha", eLogLevel_Log);

			Assert::IsNotNull(logEntry.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(logEntry.myLogMessage.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Operator_Assignment_Copy_NonWide)
		{
			HD_LogEntry logEntry1("haha", eLogLevel_Log);
			HD_LogEntry logEntry2;
			logEntry2 = logEntry1;

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(logEntry2.myLogMessage.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Operator_Assignment_Copy_Wide)
		{
			HD_LogEntry logEntry1(L"haha", eLogLevel_Log);
			HD_LogEntry logEntry2;
			logEntry2 = logEntry1;

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(logEntry2.myLogMessage.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Operator_Assignment_Move_NonWide)
		{
			HD_LogEntry logEntry1("haha", eLogLevel_Log);
			HD_LogEntry logEntry2;
			logEntry2 = HD_Move(logEntry1);

			Assert::IsNull(logEntry1.myLogMessage.myData);
			Assert::AreEqual(static_cast<char>(logEntry1.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
			Assert::AreEqual(static_cast<char>(logEntry1.myLogLevel), static_cast<char>(eLogLevel_Invalid));

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(logEntry2.myLogMessage.myData, "haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Operator_Assignment_Move_Wide)
		{
			HD_LogEntry logEntry1(L"haha", eLogLevel_Log);
			HD_LogEntry logEntry2;
			logEntry2 = HD_Move(logEntry1);

			Assert::IsNull(logEntry1.myLogMessage.myData);
			Assert::AreEqual(static_cast<char>(logEntry1.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Invalid));
			Assert::AreEqual(static_cast<char>(logEntry1.myLogLevel), static_cast<char>(eLogLevel_Invalid));

			Assert::IsNotNull(logEntry2.myLogMessage.myData);
			Assert::AreEqual(HD_Strcmp(reinterpret_cast<wchar_t*>(logEntry2.myLogMessage.myData), L"haha"), 0);
			Assert::AreEqual(static_cast<char>(logEntry2.myLogMessage.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
			Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
		}
	};
}
