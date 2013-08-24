#include "WorldSession.hpp"
#include "Shared/Log.hpp"
#include "PlayerHolder.hpp"
#include "Map.hpp"
#include "Shared/Opcodes.hpp"

WorldSession::WorldSession(io_service& io) :
TCPSession(io)
{
}

void WorldSession::HandleLogin()
{
    std::string Username;
    RecPckt >> Username;

    if (Player* pPlayer = ObjectHolder<Player>::Find(Username))
    {
        pPlayer->pSession = this;
        pPlayer->GetMap()->AddPlayer(pPlayer);
    }
}

void WorldSession::HandleMove()
{
    uint8 Direction;
    RecPckt >> Direction;
}

void WorldSession::HandleNULL()
{
    sLog.Write(LOG_ERROR, "Received strange opcode: %s", OpcodeTable[RecPckt.GetOpcode()].name);
}
