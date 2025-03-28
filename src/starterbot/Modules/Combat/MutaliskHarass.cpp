#include "MutaliskHarass.h"

void MutaliskHarass::Evaluate() {
    recruitMutalisks();
    harassEnemy();
}

void MutaliskHarass::recruitMutalisks() {
    mutalisks.clear();
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk) {
            mutalisks.push_back(unit);
        }
    }
}

void MutaliskHarass::harassEnemy() {
    if (mutalisks.empty()) return;

    BWAPI::Position enemyBase = from_Tile_position(blackboard->getEnemyBase());
    for (auto& muta : mutalisks) {
        if (muta && muta->exists()) {
            muta->move(enemyBase);
        }
    }
}
