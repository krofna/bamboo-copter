#include "Log.hpp"

#include <iostream>
#include <cstdarg>
#include <cstdlib>

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

void Log::Flush()
{
    LogMutex.lock();
    std::cout << std::flush;
    File << std::flush;
    LogMutex.unlock();
}
