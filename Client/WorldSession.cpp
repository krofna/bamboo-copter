#include "WorldSession.hpp"
#include "Shared/Log.hpp"
#include "DataMgr.hpp"

#include <boost/asio/connect.hpp>
#include <boost/bind/bind.hpp>

WorldSession::WorldSession(io_service& io) :
TCPSession(io),
Resolver(io)
{
}

WorldSession::~WorldSession()
{
}

void WorldSession::Connect(std::string IP, std::string Port)
{
    async_connect(Socket, Resolver.resolve(TCPResolver::query(IP, Port)),
        boost::bind(&WorldSession::OnConnect, this, placeholders::error));
}

void WorldSession::OnConnect(const boost::system::error_code& Error)
{
    if (Error)
        sLog.Write(LOG_ERROR, "Failed to connect.");
    else
        Start();
}

void TCPSession::HandleTemplate()
{
    sDataMgr->ProcessPacket(RecPckt);
}
