#ifndef CREATURE_AI_HPP
#define CREATURE_AI_HPP

#include "Shared/BasicTypes.hpp"

class Unit;
class Creature;

class CreatureAI
{
    friend class AIFactory;
protected:
    CreatureAI(Creature* pCreature) : pMe(pCreature) { }

public:
    virtual ~CreatureAI(){}

    // Called on World Update
    virtual void UpdateAI(){}

    // Called when creature enters combat
    virtual void EnterCombat(Unit* pEnemy){}

    // Called when creature leaves combat
    virtual void LeaveCombat(){}

    // Called when creature dies
    virtual void JustDied(Unit* pKiller){}

    // Called when creature kills unit
    virtual void KilledUnit(Unit* pVictim){}

    // Called before creature is hit by melee attack
    virtual void Hit(Unit* pAttacker, int32& Damage){}

    void DoMeleeAttackIfReady();

protected:
    Creature* pMe;
};

#endif
