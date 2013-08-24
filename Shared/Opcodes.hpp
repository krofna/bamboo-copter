#ifndef OPCODES_HPP
#define OPCODES_HPP

class WorldSession;

enum Opcodes
{
    MSG_NULL            = 0x0,
    SMSG_TEMPLATE       = 0x1, // Deprecated
    MSG_LOGIN           = 0x2,
    SMSG_OBJECT_CREATE  = 0x3,
    CMSG_MOVE           = 0x4,
    SMSG_OBJECT_UPDATE  = 0x5,
    MSG_COUNT
};

struct OpcodeHandler
{
    char const* name;
    void (WorldSession::*Handler)();
};

extern OpcodeHandler OpcodeTable[MSG_COUNT];

#endif
