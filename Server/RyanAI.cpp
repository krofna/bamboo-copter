#include "CreatureAI.hpp"
#include "Shared/Log.hpp"
#include "AIFactory.hpp"

class RyanAI : public CreatureAI
{
public:
    RyanAI(Creature* pCreature) : CreatureAI(pCreature)
    {
        sLog.Write(LOG_REQUESTED, "Loading RyanAI");
    }
};

CreatureAI* CreateRyanAI(Creature* pCreature)
{
    return new RyanAI(pCreature);
}

void LoadRyanAI()
{
    AIFactory::RegisterCreatureAI("creature_ryan", &CreateRyanAI);
}
