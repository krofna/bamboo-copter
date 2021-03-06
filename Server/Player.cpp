#include "Player.hpp"
#include "Shared/DataMgr.hpp"

Player::Player(uint64 GUID, uint32 Entry, std::string Username) :
Unit(GUID, Entry),
pSession(nullptr),
Username(Username)
{
    pTemplate = sDataMgr->GetHeroTemplate(Entry);
}

void Player::Update()
{
    if (pSession)
        pSession->Update();
}

void Player::SendPacket(Packet& Pckt)
{
    pSession->Send(Pckt);
}

std::string Player::GetName() const
{
    return Username;
}
