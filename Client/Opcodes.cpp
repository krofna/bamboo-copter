#include "Shared/Opcodes.hpp"
#include "WorldSession.hpp"

OpcodeHandler OpcodeTable[MSG_COUNT] =
{
    { "MSG_NULL", &WorldSession::HandleNULL, PROCESS_IN_PLACE },
    { "MSG_LOGIN", &WorldSession::HandleLogin },
    { "SMSG_OBJECT_CREATE", &WorldSession::HandleObjectCreate },
    { "CMSG_MOVE", &WorldSession::HandleNULL },
    { "SMSG_OBJECT_UPDATE", &WorldSession::HandleObjectUpdate }
};
