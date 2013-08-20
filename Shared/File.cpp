#include "File.hpp"

File::File(std::string Path, std::ios::openmode mode) :
Stream(Path, std::ios::binary | mode)
{
}

void File::Close()
{
    Stream.close();
}

File::operator bool() const
{
    return !Stream.eof() && Stream.good();
}

template <> File& File::operator>> (std::string& Data)
{
    getline(Stream, Data, '\0');
    return *this;
}

template <> File& File::operator<< (std::string Data)
{
    char null = 0;
    Stream.write(Data.c_str(), Data.size());
    Write<char>(null);
    return *this;
}
