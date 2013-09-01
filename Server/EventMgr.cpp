#include "EventMgr.hpp"
#include <algorithm>

void EventMgr::Register(uint8 ID, std::function<void()> Callback, uint32 TimeFromNow, bool Perpetual)
{
    Events[ID] = Event { Callback, TimeFromNow, TimeFromNow, Perpetual };
}

void EventMgr::Unregister(uint8 ID)
{
    Events.erase(ID);
}

void EventMgr::Update()
{
    bool Erase;
    auto i = Events.begin();
    while (i != Events.end())
    {
        Erase = false;

        if (i->second.TimeLeft < HEARTBEAT)
        {
            i->second.Callback();
            if (!i->second.Perpetual)
                Erase = true;
            else
                i->second.TimeLeft = i->second.Time;
        }
        else
            i->second.TimeLeft -= HEARTBEAT;

        if (Erase)
            i = Events.erase(i);
        else
            ++i;
    }
}
