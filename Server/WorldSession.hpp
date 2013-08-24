#ifndef WORLD_SESSION_HPP
#define WORLD_SESSION_HPP

#include "Shared/TCPSession.hpp"

class Player;

class WorldSession : public TCPSession
{
    friend class WorldAcceptor;
public:
    WorldSession(io_service& io);

    void SetPlayer(Player* pPlayer);

    void HandleNULL();
    void HandleLogin();
    void HandleMove();

private:
    Player* pPlayer;
};

#endif
