#include "WorldSession.hpp"
#include "Shared/Log.hpp"

void TCPSession::HandleTemplate()
{
    ((WorldSession*)this)->HandleSMSG();
}

void WorldSession::HandleSMSG()
{
    sLog.Write(LOG_INFO, "Got a SMSG from client");
}
