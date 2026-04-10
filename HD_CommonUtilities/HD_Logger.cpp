#include "stdafx.h"
#include"HD_Logger.h"

HD_Logger::HD_Logger()
{
	myLogThread = std::thread(&HD_Logger::LogThread, this);
}

HD_Logger::~HD_Logger()
{
	myLogThread.join();
}
