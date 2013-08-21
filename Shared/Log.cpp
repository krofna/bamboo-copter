#include "Log.hpp"

#include <iostream>
#include <cstdarg>
#include <cstdlib>
#include "Shared/Utils.hpp"

Log sLog;

void Log::Initialize(const char* File)
{
    this->File.open(File, std::ios::out | std::ios::app);
}

void Log::SetPriority(int Priority)
{
    LogLevel = Priority;
}

void Log::Write(int Priority, std::string const& ToWrite)
{
    if (Priority < LogLevel)
        return;

    LogMutex.lock();
    std::cout << ToWrite << '\n';
    File << ToWrite << '\n';
    LogMutex.unlock();
}

#ifdef _MSC_VER
void Log::Write(int Priority, std::string const& ToWrite, int /*dummy*/, ...)
{
	if (Priority < LogLevel)
		return;

	const char* cstr = ToWrite.c_str();
	va_list ArgumentPointer;

	va_start(ArgumentPointer, cstr);

	char* bufFormatted = Format(cstr, &ArgumentPointer);

	try
	{
		LogMutex.lock();
		std::cout << bufFormatted << '\n';
		File << bufFormatted << '\n';
		LogMutex.unlock();
	}
	catch (...)
	{
		LogMutex.unlock();
		delete[] bufFormatted;
		throw;
	}
}

#endif

void Log::Flush()
{
    LogMutex.lock();
    std::cout << std::flush;
    File << std::flush;
    LogMutex.unlock();
}
