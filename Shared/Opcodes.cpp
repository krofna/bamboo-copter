#include "Shared/Opcodes.hpp"
#include "Shared/TCPSession.hpp"

OpcodeHandler OpcodeTable[MSG_COUNT] = 
{
    { "MSG_NULL", &TCPSession::HandleNULL },
    { "SMSG_TEMPLATE", &TCPSession::HandleTemplate }
};
