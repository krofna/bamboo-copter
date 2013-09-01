#include "WorldAcceptor.hpp"
#include "Shared/Log.hpp"
#include "WorldSession.hpp"
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

WorldAcceptor::WorldAcceptor(boost::asio::io_service& io) :
Endpoint(boost::asio::ip::tcp::v4(), 0xBEEF),
Acceptor(io, Endpoint)
{
}

void WorldAcceptor::HandleAccept(WorldSessionPtr Session, const boost::system::error_code& error)
{
    if (!error)
    {
        sLog.Write(LOG_INFO, "Connection established");
        Session->Start();
    }
    else
        sLog.Write(LOG_ERROR, "Connection refused (%s)", error.message());

    Accept();
}

void WorldAcceptor::Accept()
{
    NewSession = boost::make_shared<WorldSession>(Acceptor.get_io_service());
    Acceptor.async_accept(NewSession->Socket,
        boost::bind(&WorldAcceptor::HandleAccept, shared_from_this(), NewSession,
        boost::asio::placeholders::error));
}
