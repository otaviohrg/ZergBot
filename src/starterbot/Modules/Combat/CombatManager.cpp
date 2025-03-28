#include "CombatManager.h"

CombatManager::CombatManager() {
    enemyRace = BWAPI::Broodwar->enemy()->getRace();
}

void CombatManager::update() {
    executeStrategy();
}

void CombatManager::executeStrategy() {
    if (enemyRace == BWAPI::Races::Protoss) {
        SpeedlingRush strategy;
        strategy.execute();
    } else if (enemyRace == BWAPI::Races::Terran) {
        HydraBust strategy;
        strategy.execute();
    } else if (enemyRace == BWAPI::Races::Zerg) {
        MutaliskHarass strategy;
        strategy.execute();
    }
}
