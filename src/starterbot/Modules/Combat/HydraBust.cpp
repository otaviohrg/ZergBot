#include "HydraBust.h"

void HydraBust::Evaluate() {
    recruitHydralisks();
    attackEnemy();
}

void HydraBust::recruitHydralisks() {
    hydralisks.clear();
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk) {
            hydralisks.push_back(unit);
        }
    }
}

void HydraBust::attackEnemy() {
    if (hydralisks.empty()) return;

    BWAPI::Position enemyBase =from_Tile_position(blackboard->getEnemyBase());
    for (auto& hydra : hydralisks) {
        if (hydra && hydra->exists()) {
            hydra->attack(enemyBase);
        }
    }
}
