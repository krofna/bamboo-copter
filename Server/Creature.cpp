#include "Creature.hpp"
#include "AIFactory.hpp"
#include "CreatureAI.hpp"
#include "Shared/DataMgr.hpp"

Creature::Creature(uint64 GUID, uint32 Entry) :
Unit(GUID, Entry)
{
    pTemplate = sDataMgr->GetCreatureTemplate(Entry);
    pAI = AIFactory::CreateCreatureAI(GetTemplate()->ScriptName, this);
}

void Creature::Update()
{
    pAI->UpdateAI();
}

CreatureTemplate* Creature::GetTemplate()
{
    return (CreatureTemplate*)WorldObject::GetTemplate();
}
