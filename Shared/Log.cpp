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

#ifdef _MSC_VER
void Log::Write(int Priority, std::string const& ToWrite, ...)
{
	if (Priority < LogLevel)
		return;

	int nArguments = CountArguments(ToWrite);
	va_list ArgumentPointer;

	va_start(ArgumentPointer, nArguments);
	
	char* bufFormated = new char[ToWrite.size() + 1];
	int r = vsnprintf_s(bufFormated, ToWrite.size(), ToWrite.size(), ToWrite.c_str(), ArgumentPointer);
	bufFormated[ToWrite.size()] = '\0';

	va_end(ArgumentPointer);

	if (r != ToWrite.size())
	{
		// An error may happened.
		if (r < 0) // Encoding error
			throw std::runtime_error("vsnprintf_s encoding error has happened, this is a bug.");
		else if (r == 0)
			throw std::runtime_error("vsnprintf_s has failed to write all string.");
		// We can suppose that all is okay, else.
	}

	boost::mutex::scoped_lock lock(LogMutex);
	std::cout << bufFormated << '\n';
	File << bufFormated << '\n';
}

int Log::CountArguments(std::string const& FormatString) const
{
	int nArguments = 0;
	for (std::string::const_iterator it = FormatString.begin() ; it != FormatString.end() ; ++it)
	{
		if ((*it) == '%' && *(it++) != '%')
			++nArguments;
	}
}
#endif

void Log::Flush()
{
    boost::mutex::scoped_lock lock(LogMutex);
    std::cout << std::flush;
    File << std::flush;
}
