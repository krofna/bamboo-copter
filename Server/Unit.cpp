#include "Unit.hpp"
#include "MotionMaster.hpp"

Unit::Unit(uint64 GUID, uint32 Entry) :
WorldObject(GUID, Entry),
pMotionMaster(new MotionMaster(this))
{
}

Unit::~Unit()
{
    delete pMotionMaster;
}
