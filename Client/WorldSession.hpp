#ifndef WORLD_SESSION_HPP
#define WORLD_SESSION_HPP

#include "Shared/TCPSession.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>

typedef boost::asio::ip::tcp::resolver TCPResolver;

class WorldSession : public TCPSession
{
public:
    WorldSession(io_service& io);
    ~WorldSession();

    void Connect(std::string IP, std::string Port);

private:
    void OnConnect(const boost::system::error_code& Error);
    TCPResolver Resolver;
};

#endif
