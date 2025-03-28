#include "CombatManager.h"

CombatManager::CombatManager() : enemyRace(BWAPI::Races::Unknown) {}

CombatManager::~CombatManager() {}

void CombatManager::setEnemyRace(BWAPI::Race race) {
    enemyRace = race;
    selectStrategy();
}

void CombatManager::selectStrategy() {
    if (enemyRace == BWAPI::Races::Terran) {
        currentStrategy = std::make_unique<MutaliskHarass>();
    } else if (enemyRace == BWAPI::Races::Protoss) {
        currentStrategy = std::make_unique<HydraBust>();
    } else if (enemyRace == BWAPI::Races::Zerg) {
        currentStrategy = std::make_unique<SpeedlingRush>();
    }
}

void CombatManager::update() {
    if (currentStrategy) {
        currentStrategy->Evaluate();
    }
}
