#ifndef WORLD_SESSION_HPP
#define WORLD_SESSION_HPP

#include "Shared/TCPSession.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/address.hpp>

class World;
class WorldSession;
typedef boost::asio::ip::tcp::resolver TCPResolver;
typedef boost::shared_ptr<WorldSession> WorldSessionPtr;

class WorldSession : public TCPSession
{
public:
    WorldSession(io_service& io);
    ~WorldSession();

    void HandleNULL();
    void HandleTemplate();
    void HandleLogin();
    void HandleObjectCreate();
    void HandleMove();

    void Login(std::string Username);
    void SendMoveHeroPacket(uint8 Direction);
    void Connect(std::string IP, std::string Port);

    void SetWorld(World* pWorld);
private:
    void OnConnect(const boost::system::error_code& Error);
    TCPResolver Resolver;
    World* pWorld;
};

#endif
