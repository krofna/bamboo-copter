#ifndef UTILS_DEFINED_HPP
#define UTILS_DEFINED_HPP

#ifdef _MSC_VER

// Simulate Variadic Templates
#define SIMULATE_VARIADIC_TEMPLATE

char* Format(const char* toFormat, ...);
char* Format(std::string const& toFormat, ...);


#endif

#endif