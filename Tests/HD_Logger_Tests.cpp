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

		TEST_METHOD(Constructor_NonWide)
		{
			HD_LogMessage message("haha");

			char buffer[8]{ 0 };
			memcpy(buffer, "haha", 4);
			Assert::AreEqual(memcmp(message.myData, buffer, 5), 0);

			Assert::AreEqual(static_cast<char>(message.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));
		}

		TEST_METHOD(Constructor_Wide)
		{
			HD_LogMessage message(L"haha");

			wchar_t buffer[8]{ 0 };
			memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
			Assert::AreEqual(memcmp(message.myData, buffer, sizeof(wchar_t) * 5), 0);

			Assert::AreEqual(static_cast<char>(message.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));
		}

		TEST_METHOD(Destructor)
		{
			{
				HD_LogMessage message("haha");
				message.~HD_LogMessage();

				Assert::IsNull(message.myData);
			}

			{
				HD_LogMessage message(L"haha");
				message.~HD_LogMessage();

				Assert::IsNull(message.myData);
			}
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			{
				HD_LogMessage message1("haha");
				HD_LogMessage message2;

				message2 = HD_Move(message1);

				Assert::IsNull(message1.myData);
				Assert::IsNotNull(message2.myData);
				Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_NonWide));

				char buffer[8]{ 0 };
				memcpy(buffer, "haha", 4);
				Assert::AreEqual(memcmp(message2.myData, buffer, 5), 0);
			}

			{
				HD_LogMessage message1(L"haha");
				HD_LogMessage message2;

				message2 = HD_Move(message1);

				Assert::IsNull(message1.myData);
				Assert::IsNotNull(message2.myData);
				Assert::AreEqual(static_cast<char>(message2.myMode), static_cast<char>(HD_LogMessage::eStringMode_Wide));

				wchar_t buffer[8]{ 0 };
				memcpy(buffer, L"haha", sizeof(wchar_t) * 4);
				Assert::AreEqual(memcmp(message2.myData, buffer, sizeof(wchar_t) * 5), 0);
			}
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
		TEST_METHOD(Contstructor)
		{
			HD_LogEntry logEntry;
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Invalid));
		}

		TEST_METHOD(Constructor_NonWide)
		{
			HD_LogEntry logEntry("haha", eLogLevel_Log);
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Constructor_Wide)
		{
			HD_LogEntry logEntry(L"haha", eLogLevel_Log);
			Assert::AreEqual(static_cast<char>(logEntry.myLogLevel), static_cast<char>(eLogLevel_Log));
		}

		TEST_METHOD(Operator_Assignment_Move)
		{
			{
				HD_LogEntry logEntry1("haha", eLogLevel_Log);

				HD_LogEntry logEntry2;
				logEntry2 = HD_Move(logEntry1);

				// Successful move of myLogMessage is tested in that class's tests.
				Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
			}

			{
				HD_LogEntry logEntry1(L"haha", eLogLevel_Log);

				HD_LogEntry logEntry2;
				logEntry2 = HD_Move(logEntry1);

				// Successful move of myLogMessage is tested in that class's tests.
				Assert::AreEqual(static_cast<char>(logEntry2.myLogLevel), static_cast<char>(eLogLevel_Log));
			}
		}
	};
}
