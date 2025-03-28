#include "CombatManager.h"

CombatManager::CombatManager() {
    pCombatBT = nullptr;
}

CombatManager::~CombatManager() {
    delete pCombatBT;
}

void CombatManager::updateCombat(Blackboard* bb) {
    if (!pCombatBT) {
        switchToStrategy(BWAPI::Broodwar->enemy()->getRace());
    }
    
    if (pCombatBT) {
        pCombatBT->Evaluate(bb->pData);
    }
}

void CombatManager::switchToStrategy(BWAPI::Race enemyRace) {
    delete pCombatBT;  // Clean up existing strategy

    if (enemyRace == BWAPI::Races::Terran) {
        pCombatBT = new ZergVsTerran();
    } else if (enemyRace == BWAPI::Races::Protoss) {
        pCombatBT = new ZergVsProtoss();
    } else {
        pCombatBT = new ZergVsZerg();
    }
}
