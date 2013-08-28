#ifndef UNIT_HPP
#define UNIT_HPP

#include "WorldObject.hpp"

class MotionMaster;

class Unit : public WorldObject
{
public:
    Unit(uint64 GUID, uint32 Entry);
    ~Unit();

    virtual void Update();

    MotionMaster* GetMotionMaster() const;

private:
    MotionMaster* pMotionMaster;
};

#endif
