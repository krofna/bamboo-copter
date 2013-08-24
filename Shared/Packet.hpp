#ifndef PACKET_HPP
#define PACKET_HPP

#include "Shared/BasicTypes.hpp"

#include <cassert>
#include <vector>
#include <cstring>
#include <string>

class Packet
{
public:
    Packet();
    Packet(uint16 Opcode);

    void* GetReadIterator();
    void* GetWriteIterator();
    void IncreaseBufferSize(uint16 Size);
    void* GetDataWithHeader();
    void* GetDataWithoutHeader();
    uint16 GetOpcode();
    void SetOpcode(uint16 Opcode);
    uint16 GetSizeWithHeader();
    uint16 GetSizeWithoutHeader();
    void ReadHeader();
    void UpdateSizeData();
    void UpdateWritePos();
    void ResetReadPos();
    bool EndOfPacket();
    void Write(char* data, uint16 size);

    operator bool();

    Packet& operator <<(uint8 data);
    Packet& operator <<(uint16 data);
    Packet& operator <<(uint32 data);
    Packet& operator <<(uint64 data);
    Packet& operator <<(int8 data);
    Packet& operator <<(int16 data);
    Packet& operator <<(int32 data);
    Packet& operator <<(int64 data);
    Packet& operator <<(float data);
    Packet& operator <<(std::string data);

    Packet& operator >>(uint8& data);
    Packet& operator >>(uint16& data);
    Packet& operator >>(uint32& data);
    Packet& operator >>(uint64& data);
    Packet& operator >>(int8& data);
    Packet& operator >>(int16& data);
    Packet& operator >>(int32& data);
    Packet& operator >>(int64& data);
    Packet& operator >>(float& data);
    Packet& operator >>(std::string& data);

    enum
    {
        HEADER_SIZE = 4
    };

    class BadPacket { public: BadPacket() {} };

private:
    template<class T> void Append(T data);
    template<class T> T Read();

    size_t ReadPos, WritePos;

    //|   0,1   |   2,3   | 4,5,6,7...
    //|   - -   |   - -   | - - - -...
    //|  Size   | Opcode  |  Data  ...
    std::vector<char> ByteBuffer;
};

template<class T> void Packet::Append(T data)
{
    IncreaseBufferSize(sizeof(data));
    std::memcpy(&ByteBuffer[WritePos], &data, sizeof(data));
    WritePos += sizeof(data);
}

template<class T> T Packet::Read()
{
    if (ReadPos + sizeof(T) > ByteBuffer.size())
        throw BadPacket();

    T data = *((T*)&ByteBuffer[ReadPos]);
    ReadPos += sizeof(T);
    return data;
}

#endif
