#ifndef UTILS_DEFINED_HPP
#define UTILS_DEFINED_HPP


// MSVC Support
#ifdef _MSC_VER
#include <string>

// Simulate Variadic Templates
#define SIMULATE_VARIADIC_TEMPLATE

#define MAX_SIZE 4096

char* Copy(char* String); // Return an copy of the string.

char* Format(const char* toFormat, ...);
char* Format(const char* toFormat, va_list* ap);
char* Format(std::string const& toFormat, ...);
char* Format(std::string const& toFormat, va_list* ap);


#endif

#endif