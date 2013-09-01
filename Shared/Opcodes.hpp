#ifndef OPCODES_HPP
#define OPCODES_HPP

class WorldSession;

enum
{
    PROCESS_IN_PLACE        = 0, // Thread-safe
    PROCESS_WORLD_UPDATE    = 1  // Thread-unsafe
};

enum Opcodes
{
    MSG_NULL            = 0x0,
    MSG_LOGIN           = 0x1,
    SMSG_OBJECT_CREATE  = 0x2,
    CMSG_MOVE           = 0x3,
    SMSG_OBJECT_UPDATE  = 0x4,
    MSG_COUNT
};

struct OpcodeHandler
{
    char const* name;
    void (WorldSession::*Handler)();
    unsigned char ThreadSafety;
};

extern OpcodeHandler OpcodeTable[MSG_COUNT];

#endif
