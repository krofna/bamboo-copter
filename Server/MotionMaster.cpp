#include "MotionMaster.hpp"
#include "Unit.hpp"
#include "Pathfinder.hpp"

#include <stack>

MotionMaster::MotionMaster(Unit* pMe) :
pPath(nullptr),
MotionStatus(MOTION_STOP),
pMe(pMe)
{
}

MotionMaster::~MotionMaster()
{
    delete pPath;
}

void MotionMaster::Update()
{
    switch (MotionStatus)
    {
        case MOTION_CHASE:
        case MOTION_MOVE_POINT:
        case MOTION_STOP:
            break;
    }
}

void MotionMaster::ClearMotionStatus()
{
    MotionStatus = MOTION_STOP;
}

void MotionMaster::MoveChase(Unit* pTarget)
{
    this->pTarget = pTarget;
}

void MotionMaster::MovePoint(sf::Vector2<uint16> Point)
{
    sPathfinder->Enqueue(this, Point);
}
