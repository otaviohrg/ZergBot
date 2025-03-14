#pragma once
#include "../Blackboard.h"
#include <BWAPI.h>
#include "../Tools.h"
#include "../BT/BT.h"

class CombatModule
{
private:
	BT_NODE* pCombatBT;
public:
    CombatModule();
	~CombatModule();
    void updateCombat(Blackboard *bb);
};
