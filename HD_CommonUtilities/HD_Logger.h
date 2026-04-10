#pragma once

#include "HD_Singleton.h"

#include <thread>

class HD_Logger : public HD_Singleton<HD_Logger>
{
public:
	enum LogLevel : char
	{
		Invalid,
		Log,
		Warning,
		Error,
	};

private:
	HD_Logger();
	~HD_Logger();

	void LogThread();

	std::thread myLogThread;
};
