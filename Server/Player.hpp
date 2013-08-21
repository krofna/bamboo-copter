#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"
#include "Shared/Packet.hpp"
#include "WorldSession.hpp"

class Player : public Unit
{
public:
    Player(uint64 GUID, uint32 Entry, uint32 x, uint32 y);

    void SendPacket(Packet& Pckt);
private:
    WorldSession* pSession;
};

#endif
