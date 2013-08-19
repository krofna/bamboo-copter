#ifndef OPCODES_HPP
#define OPCODES_HPP

class TCPSession;

enum Opcodes
{
    MSG_NULL        = 0x0,
    SMSG_TEMPLATE   = 0x1,
    MSG_COUNT
};

struct OpcodeHandler
{
    char const* name;
    void (TCPSession::*Handler)();
};

extern OpcodeHandler OpcodeTable[MSG_COUNT];

#endif
