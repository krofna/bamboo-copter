#include "WorldSession.hpp"
#include "Shared/Log.hpp"

WorldSession::WorldSession(io_service& io) :
TCPSession(io)
{
}

void TCPSession::HandleTemplate()
{
    ((WorldSession*)this)->HandleSMSG();
}

void WorldSession::HandleSMSG()
{
    sLog.Write(LOG_INFO, "Got a SMSG from client");
}
