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
            if (!IsPathEmpty())
                pMe->SetPosition(PopCheckpoint());
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
    MotionStatus = MOTION_MOVE_POINT;
    sPathfinder->Enqueue(this, Point);
}

void MotionMaster::SetPath(std::stack<sf::Vector2<uint16> >* pPath)
{
    PathMutex.lock();
    delete this->pPath;
    this->pPath = pPath;
    PathMutex.unlock();
}

bool MotionMaster::IsPathEmpty()
{
    return !pPath || pPath->empty();
}

sf::Vector2<uint16> MotionMaster::PopCheckpoint()
{
    PathMutex.lock();
    sf::Vector2<uint16> Ret = pPath->top();
    pPath->pop();
    PathMutex.unlock();
    return Ret;
}
