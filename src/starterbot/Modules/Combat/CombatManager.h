#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "../../Blackboard.h"
#include "../../BT/BT.h"
#include "ZergVsTerran.h"
#include "ZergVsProtoss.h"
#include "ZergVsZerg.h"

class CombatManager {
public:
    CombatManager();
    ~CombatManager();

    void updateCombat(Blackboard* bb);

private:
    BT_DECORATOR* pCombatBT;
    void switchToStrategy(BWAPI::Race enemyRace);
};

#endif // COMBAT_MANAGER_H
