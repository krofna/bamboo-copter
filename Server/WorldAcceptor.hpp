#ifndef WORLD_ACCEPTOR_H
#define WORLD_ACCEPTOR_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/utility.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;

class WorldSession;
typedef boost::shared_ptr<WorldSession> WorldSessionPtr;
typedef boost::asio::ip::tcp::endpoint TCPEndpoint;
typedef boost::asio::ip::tcp::acceptor TCPAcceptor;

class WorldAcceptor : private boost::noncopyable, public boost::enable_shared_from_this<WorldAcceptor>
{
public:
    WorldAcceptor(boost::asio::io_service& io);

    void Accept();
private:
    void HandleAccept(WorldSessionPtr Session, const boost::system::error_code& error);

    TCPEndpoint Endpoint;
    TCPAcceptor Acceptor;
    WorldSessionPtr NewSession;
};

#endif
