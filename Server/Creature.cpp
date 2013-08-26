#include "Creature.hpp"
#include "AIFactory.hpp"
#include "CreatureAI.hpp"

Creature::Creature(uint64 GUID, uint32 Entry, std::string ScriptName) :
Unit(GUID, Entry)
{
    pAI = AIFactory::CreateCreatureAI(ScriptName, this);
}
