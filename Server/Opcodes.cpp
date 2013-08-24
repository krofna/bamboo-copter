#include "Shared/Opcodes.hpp"
#include "WorldSession.hpp"

OpcodeHandler OpcodeTable[MSG_COUNT] = 
{
    { "MSG_NULL", &WorldSession::HandleNULL },
    { "SMSG_TEMPLATE", &WorldSession::HandleNULL },
    { "MSG_LOGIN", &WorldSession::HandleLogin },
    { "SMSG_OBJECT_CREATE", &WorldSession::HandleNULL },
    { "CMSG_MOVE", &WorldSession::HandleMove },
    { "SMSG_OBJECT_UPDATE", &WorldSession::HandleNULL }
};
