#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>

class File
{
public:
    File(std::string Path, std::ios::openmode mode);
    void Close();

    template <class T> File& operator<< (T Data);
    template <class T> File& operator>> (T& Data);
    template <class T> void Read(T& Data);
    template <class T> void Write(T& Data);
    operator bool() const;

private:
    std::fstream Stream;
};

template <class T> File& File::operator<< (T Data)
{
    Write(Data);
    return *this;
}

template <class T> File& File::operator>> (T& Data)
{
    Read(Data);
    return *this;
}

template <class T> void File::Read(T& Data)
{
    Stream.read(reinterpret_cast<char*>(&Data), sizeof(Data));
}

template <class T> void File::Write(T& Data)
{
    Stream.write(reinterpret_cast<const char*>(&Data), sizeof(Data));
}

#endif
