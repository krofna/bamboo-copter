#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"

class Player : public Unit
{
public:
    Player(uint64 GUID, uint32 Entry, uint32 x, uint32 y);
private:
};

#endif
