#ifndef TCP_SESSION_HPP
#define TCP_SESSION_HPP

#include "Shared/Packet.hpp"
#include <queue>
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
#ifndef _MSC_VER
template <class T> using Queue = std::queue<T>;
#endif

class TCPSession : private boost::noncopyable, public boost::enable_shared_from_this<TCPSession>
{
public:
    TCPSession(io_service& io);
    virtual ~TCPSession();

    void Send(Packet& Pckt);

protected:
    void Start();
    void HandleSend(const boost::system::error_code& Error);
    void HandleReceive(const boost::system::error_code& Error);
    void HandleHeader(const boost::system::error_code& Error);

    TCPSocket Socket;
    Packet RecPckt;

#ifndef _MSC_VER
    Queue<Packet> MessageQueue;
#else
	std::queue<Packet> MessageQueue;
#endif
};

#endif
