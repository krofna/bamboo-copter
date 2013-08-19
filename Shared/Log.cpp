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

    boost::mutex::scoped_lock lock(LogMutex);
    std::cout << ToWrite << '\n';
    File << ToWrite << '\n';
}

void Log::Flush()
{
    boost::mutex::scoped_lock lock(LogMutex);
    std::cout << std::flush;
    File << std::flush;
}
