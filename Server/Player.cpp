#include "Player.hpp"

Player::Player(uint64 GUID, uint32 Entry, uint32 x, uint32 y) :
Unit(GUID, Entry, x, y)
{
}

void Player::SendPacket(Packet& Pckt)
{
    pSession->Send(Pckt);
}
