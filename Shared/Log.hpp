#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <boost/thread/mutex.hpp>
#include <boost/utility.hpp>
#include <boost/format.hpp>

enum Level
{
    LOG_INFO        = 0,
    LOG_ERROR       = 1,
    LOG_REQUESTED   = 2,
    LOG_NEVER       = 3
};

class Log : private boost::noncopyable
{
public:
    void Initialize(const char* File);
    void SetPriority(int Priority);

    template <typename... Arg>
    void Write(int Priority, std::string const& Format, Arg... Args);
    void Write(int Priority, std::string const& ToWrite);
    void Flush();

private:
    std::ofstream File;
    int LogLevel;
    boost::mutex LogMutex;
};

inline std::string Format(boost::format formater)
{
    return formater.str();
}

inline std::string Format(std::string const& toFormat)
{
    return toFormat;
}

template <typename T, typename... Values>
inline std::string Format(boost::format formater, T const& val, Values... values)
{
    return Format(formater % val, std::forward<Values>(values)...);
}

template <typename T, typename... Values>
inline std::string Format(std::string const& toFormat, T const& val, Values... values)
{
    return Format(boost::format(toFormat) % val, std::forward<Values>(values)...);
}

template <typename... Arg>
void Log::Write(int Priority, std::string const& String, Arg... Args)
{
    if (Priority < LogLevel)
        return;

    std::string Formated = Format(String, Args...);
    boost::mutex::scoped_lock lock(LogMutex);
    std::cout << Formated << '\n';
    File << Formated << '\n';
}

extern Log sLog;

#endif
