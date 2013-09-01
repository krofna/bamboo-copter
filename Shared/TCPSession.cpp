#include "Shared/TCPSession.hpp"
#include "Shared/Opcodes.hpp"
#include "Shared/Log.hpp"

#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/bind/bind.hpp>

TCPSession::TCPSession(io_service& io) :
Socket(io)
{
}

TCPSession::~TCPSession()
{
}

void TCPSession::Start()
{
    RecPckt = Packet((uint16)MSG_NULL);
    async_read(Socket, buffer(RecPckt.GetDataWithHeader(), Packet::HEADER_SIZE),
        boost::bind(&TCPSession::HandleHeader, shared_from_this(), placeholders::error));
}

void TCPSession::HandleHeader(const boost::system::error_code& Error)
{
    RecPckt.ReadHeader();
    if (RecPckt.GetSizeWithoutHeader() == 0 || Error)
        HandleReceive(Error);
    else
        async_read(Socket, buffer(RecPckt.GetDataWithoutHeader(), RecPckt.GetSizeWithoutHeader()),
            boost::bind(&TCPSession::HandleReceive, shared_from_this(), placeholders::error));
}

void TCPSession::HandleReceive(const boost::system::error_code& Error)
{
    RecPckt.ResetReadPos();

    if (Error)
    {
        sLog.Write(LOG_ERROR, "Failed to receive packet. TODO: Try Reconnect?");
        return;
    }

    if (RecPckt.GetOpcode() >= MSG_COUNT)
        sLog.Write(LOG_ERROR, "Received %u: Bad opcode!", RecPckt.GetOpcode());

    sLog.Write(LOG_INFO, "Received Packet: %s, size: %u", OpcodeTable[RecPckt.GetOpcode()].name, RecPckt.GetSizeWithoutHeader());

    switch (OpcodeTable[RecPckt.GetOpcode()].ThreadSafety)
    {
        case PROCESS_IN_PLACE:
            (((WorldSession*)this)->*OpcodeTable[RecPckt.GetOpcode()].Handler)();
            break;
        case PROCESS_WORLD_UPDATE:
            RecPcktsMutex.lock();
            RecPckts.push(RecPckt);
            RecPcktsMutex.unlock();
            break;
        default:
            sLog.Write(LOG_ERROR, "Opcode with invalid ThreadSafety. Check Opcodes.cpp");
            break;
    }

    Start();
}

void TCPSession::Send(Packet& Pckt)
{
    sLog.Write(LOG_INFO, "Sending Packet: %s, size: %u", OpcodeTable[Pckt.GetOpcode()].name, Pckt.GetSizeWithoutHeader());

    Pckt.UpdateSizeData();
    MessageQueue.push(Pckt);
    if (MessageQueue.size() == 1)
        async_write(Socket, buffer(Pckt.GetDataWithHeader(), Pckt.GetSizeWithHeader()),
            boost::bind(&TCPSession::HandleSend, shared_from_this(), placeholders::error));
}

void TCPSession::HandleSend(const boost::system::error_code& Error)
{
    if (!Error)
        sLog.Write(LOG_INFO, "Packet sent successfully!");
    else
        sLog.Write(LOG_ERROR, "Failed to send packet!");

    MessageQueue.pop();
    if (!MessageQueue.empty())
        async_write(Socket, buffer(MessageQueue.front().GetDataWithHeader(), MessageQueue.front().GetSizeWithHeader()),
            boost::bind(&TCPSession::HandleSend, shared_from_this(), placeholders::error));
}

void TCPSession::Update()
{
    RecPcktsMutex.lock();
    while (!RecPckts.empty())
    {
        (((WorldSession*)this)->*OpcodeTable[RecPckts.front().GetOpcode()].Handler)();
        RecPckts.pop();
    }
    RecPcktsMutex.unlock();
}
