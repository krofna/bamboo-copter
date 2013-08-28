#include "EventMgr.hpp"
#include <algorithm>

void EventMgr::Register(uint8 ID, std::function<void()> Callback, uint32 TimeFromNow)
{
    Events[ID] = Event { Callback, TimeFromNow };
}

void EventMgr::Unregister(uint8 ID)
{
    Events.erase(ID);
}

void EventMgr::Update()
{
    std::for_each(Events.begin(), Events.end(),
    [](EventVal& i)
    {
        if (i.second.TimeLeft < HEARTBEAT)
        {
            i.second.Callback();
            // Unregister(i.first);
        }
        else
            i.second.TimeLeft -= HEARTBEAT;
    }
    );
}
