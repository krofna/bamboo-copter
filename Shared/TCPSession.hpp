#ifndef TCP_SESSION_HPP
#define TCP_SESSION_HPP

#include "Shared/Packet.hpp"
#include <queue>
#include <mutex>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/utility.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;

typedef boost::asio::deadline_timer DeadlineTimer;
typedef boost::asio::ip::tcp::endpoint TCPEndpoint;
typedef boost::asio::ip::tcp::socket TCPSocket;

class TCPSession : private boost::noncopyable, public boost::enable_shared_from_this<TCPSession>
{
public:
    TCPSession(io_service& io);
    virtual ~TCPSession() = 0;

    void Send(Packet& Pckt);

    void Update();

protected:
    void Start();
    void HandleSend(const boost::system::error_code& Error);
    void HandleReceive(const boost::system::error_code& Error);
    void HandleHeader(const boost::system::error_code& Error);

    TCPSocket Socket;
    Packet RecPckt;

    std::queue<Packet> RecPckts; // Received
	std::queue<Packet> MessageQueue; // To send

    std::mutex RecPcktsMutex;
};

#endif
