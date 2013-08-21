#include "Utils.hpp"

#ifdef _MSC_VER

#include <cstring>
#include <cstdarg>
#include <cstdio>


char* Copy(char* String)
{
	int Size = strlen(String);
	char* cpy = new char[Size + 1];

	strncpy_s(cpy, Size, String, MAX_SIZE);

	cpy[Size] = '\0';

	return cpy;
}

char* Format(const char* toFormat, ...)
{
	char Formatted[MAX_SIZE];

	va_list ap;

	va_start(ap, toFormat);

	vsnprintf_s(Formatted, MAX_SIZE, toFormat, ap);

	va_end(ap);

	return Copy(Formatted);
}

char* Format(const char* toFormat, va_list* ap)
{
	char Formatted[MAX_SIZE];

	vsnprintf_s(Formatted, MAX_SIZE, toFormat, *ap);

	va_end(*ap);

	return Copy(Formatted);
}

char* Format(std::string const& toFormat, ...)
{
	char Formatted[MAX_SIZE];

	const char* toFormat_cstr = toFormat.c_str();

	va_list ap;

	va_start(ap, toFormat_cstr);

	vsnprintf_s(Formatted, MAX_SIZE, toFormat_cstr, ap);

	va_end(ap);

	return Copy(Formatted);
}

char* Format(std::string const& toFormat, va_list* ap)
{
	char Formatted[MAX_SIZE];

	const char* toFormat_cstr = toFormat.c_str();

	vsnprintf_s(Formatted, MAX_SIZE, toFormat_cstr, *ap);

	va_end(*ap);

	return Copy(Formatted);
}

#endif