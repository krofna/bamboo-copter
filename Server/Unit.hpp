#ifndef UNIT_HPP
#define UNIT_HPP

#include "WorldObject.hpp"

class Unit : public WorldObject
{
public:
    Unit(uint64 GUID, uint32 Entry, uint32 x, uint32 y);
private:
};

#endif
