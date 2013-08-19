#include "Shared/Packet.hpp"
#include "Shared/Opcodes.hpp"

Packet::Packet() :
ByteBuffer    (HEADER_SIZE)
{
    ResetReadPos();
    UpdateWritePos();
}

Packet::Packet(uint16 Opcode) :
ByteBuffer    (HEADER_SIZE)
{
    ResetReadPos();
    UpdateWritePos();
    SetOpcode(Opcode);
}

void* Packet::GetReadIterator()
{
    return &ByteBuffer[ReadPos];
}

void* Packet::GetWriteIterator()
{
    return &ByteBuffer[WritePos];
}

void Packet::IncreaseBufferSize(uint16 Size)
{
    ByteBuffer.resize(ByteBuffer.size() + Size);
}

uint16 Packet::GetSizeWithHeader()
{
    return ByteBuffer.size();
}

uint16 Packet::GetSizeWithoutHeader()
{
    return ByteBuffer.size() - HEADER_SIZE;
}

void* Packet::GetDataWithHeader()
{
    return &ByteBuffer[0];
}

void* Packet::GetDataWithoutHeader()
{
    return &ByteBuffer[HEADER_SIZE];
}

uint16 Packet::GetOpcode()
{
    return *(uint16*)&ByteBuffer[2];
}

void Packet::SetOpcode(uint16 Opcode)
{
    std::memcpy(&ByteBuffer[2], &Opcode, 2);
}

void Packet::ReadHeader()
{
    ByteBuffer.resize(HEADER_SIZE + *(uint16*)&ByteBuffer[0]);
}

void Packet::UpdateSizeData()
{
    uint16 SizeWithoutHeader = GetSizeWithoutHeader();
    std::memcpy(&ByteBuffer[0], &SizeWithoutHeader, 2);
}

void Packet::UpdateWritePos()
{
    WritePos = ByteBuffer.size();
}

void Packet::ResetReadPos()
{
    ReadPos = HEADER_SIZE;
}

bool Packet::EndOfPacket()
{
    return ReadPos == ByteBuffer.size();
}

void Packet::Write(char* data, uint16 size)
{
    IncreaseBufferSize(size);
    std::memcpy(&ByteBuffer[WritePos], data, size);
    WritePos += size;
}

Packet& Packet::operator <<(uint8 data)   { Append<uint8>(data);  return *this; }
Packet& Packet::operator <<(uint16 data)  { Append<uint16>(data); return *this; }
Packet& Packet::operator <<(uint32 data)  { Append<uint32>(data); return *this; }
Packet& Packet::operator <<(uint64 data)  { Append<uint64>(data); return *this; }
Packet& Packet::operator <<(int8 data)    { Append<int8>(data);   return *this; }
Packet& Packet::operator <<(int16 data)   { Append<int16>(data);  return *this; }
Packet& Packet::operator <<(int32 data)   { Append<int32>(data);  return *this; }
Packet& Packet::operator <<(int64 data)   { Append<int64>(data);  return *this; }
Packet& Packet::operator <<(float data)   { Append<float>(data);  return *this; }
Packet& Packet::operator <<(std::string data)
{
    IncreaseBufferSize(data.size() + 1);

    std::copy(data.begin(), data.end(), &ByteBuffer[WritePos]); // Raito : std::copy is better because it will know what it should call : memmove or memcpy.
    ByteBuffer[WritePos + data.size()] = '\0'; // We can do more simpler, by using std::copy(data.c_str(), data.c_str() + data.size() + 1), but ... the code is more complex. As you wish.

    WritePos += data.size(); ++WritePos;
    return *this; 
}

Packet& Packet::operator >>(uint8& data)  { data = Read<uint8>(); return *this; }
Packet& Packet::operator >>(uint16& data) { data = Read<uint16>();return *this; }
Packet& Packet::operator >>(uint32& data) { data = Read<uint32>();return *this; }
Packet& Packet::operator >>(uint64& data) { data = Read<uint64>();return *this; }
Packet& Packet::operator >>(int8& data)   { data = Read<int8>();  return *this; }
Packet& Packet::operator >>(int16& data)  { data = Read<int16>(); return *this; }
Packet& Packet::operator >>(int32& data)  { data = Read<int32>(); return *this; }
Packet& Packet::operator >>(int64& data)  { data = Read<int64>(); return *this; }
Packet& Packet::operator >>(float& data)  { data = Read<float>(); return *this; }
Packet& Packet::operator >>(std::string& data)
{
    // Raito : You've recreated std::strlen.
    data.assign(&ByteBuffer[ReadPos], std::char_traits<char>::length(&ByteBuffer[ReadPos])); // This should copy only characters, and exclude \0 character.
    ReadPos += data.size(); ++ReadPos;
    return *this; 
}
