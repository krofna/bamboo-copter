#include "Shared/Opcodes.hpp"
#include "WorldSession.hpp"

OpcodeHandler OpcodeTable[MSG_COUNT] =
{
    { "MSG_NULL", &WorldSession::HandleNULL, PROCESS_IN_PLACE },
    { "MSG_LOGIN", &WorldSession::HandleLogin, PROCESS_IN_PLACE},
    { "SMSG_OBJECT_CREATE", &WorldSession::HandleNULL, PROCESS_IN_PLACE },
    { "CMSG_MOVE", &WorldSession::HandleMove, PROCESS_WORLD_UPDATE },
    { "SMSG_OBJECT_UPDATE", &WorldSession::HandleNULL, PROCESS_IN_PLACE }
};
