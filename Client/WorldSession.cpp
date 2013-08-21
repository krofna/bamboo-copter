#include "WorldSession.hpp"
#include "Shared/Log.hpp"
#include "DataMgr.hpp"
#include "Shared/Opcodes.hpp"
#include "WorldObject.hpp"
#include "Shared/World.hpp"
#include <boost/asio/connect.hpp>
#include <boost/bind/bind.hpp>

WorldSession::WorldSession(io_service& io, World* pWorld) :
TCPSession(io),
Resolver(io),
pWorld(pWorld)
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
        LogWrite(LOG_ERROR, "Failed to connect.");
    else
        Start();
}

void WorldSession::HandleTemplate()
{
    sDataMgr->ProcessPacket(RecPckt);
}

void WorldSession::HandleLogin()
{
}

void WorldSession::HandleObjectCreate()
{
    uint64 GUID;
    uint32 Entry;
    uint32 x, y;
    RecPckt >> GUID >> Entry >> x >> y;
    WorldObject* pObject = new WorldObject(Entry);
    pObject->SetPosition(sf::Vector2f(x, y));
    pObject->SetAnimationSpeed(sf::milliseconds(300)); // Placeholder: Should be part of animation template
    pWorld->Insert(pObject);
}

void WorldSession::HandleNULL()
{
    LogWrite(LOG_ERROR, "Received strange opcode: %s", OpcodeTable[RecPckt.GetOpcode()].name);
}

