#include "WorldSession.hpp"
#include "Shared/Log.hpp"
#include "PlayerHolder.hpp"
#include "Map.hpp"
#include "Shared/Opcodes.hpp"
#include "Shared/Defines.hpp"

WorldSession::WorldSession(io_service& io) :
TCPSession(io),
pPlayer(nullptr)
{
}

void WorldSession::HandleLogin()
{
    std::string Username;
    RecPckt >> Username;

    if ((pPlayer = ObjectHolder<Player>::Find(Username)))
    {
        pPlayer->pSession = this;
        pPlayer->GetMap()->AddPlayer(pPlayer);
    }
}

void WorldSession::HandleMove()
{
    uint8 Direction;
    RecPckt >> Direction;

    switch (Direction)
    {
    case MOVE_UP:
        pPlayer->SetY(pPlayer->GetY() - 1);
        break;
    case MOVE_DOWN:
        pPlayer->SetY(pPlayer->GetY() + 1);
        break;
    case MOVE_LEFT:
        pPlayer->SetX(pPlayer->GetX() - 1);
        break;
    case MOVE_RIGHT:
        pPlayer->SetX(pPlayer->GetX() + 1);
        break;
    }
}

void WorldSession::HandleNULL()
{
    sLog.Write(LOG_ERROR, "Received strange opcode: %s", OpcodeTable[RecPckt.GetOpcode()].name);
}
