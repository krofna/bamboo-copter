#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Unit.hpp"

class Creature : public Unit
{
public:
    Creature(uint64 GUID, uint32 Entry);
};

#endif
