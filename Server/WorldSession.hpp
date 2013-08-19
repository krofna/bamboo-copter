#ifndef WORLD_SESSION_HPP
#define WORLD_SESSION_HPP

#include "Shared/TCPSession.hpp"

class WorldSession : public TCPSession
{
public:
    WorldSession(io_service& io);
    ~WorldSession();

    void HandleSMSG();

private:
};

#endif
