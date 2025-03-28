#include "SpeedlingRush.h"

void SpeedlingRush::Evaluate() {
    recruitZerglings();
    rushEnemy();
}

void SpeedlingRush::recruitZerglings() {
    zerglings.clear();
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
            zerglings.push_back(unit);
        }
    }
}

void SpeedlingRush::rushEnemy() {
    if (zerglings.empty()) return;

    BWAPI::Position enemyBase = from_Tile_position(blackboard->getEnemyBase());
    for (auto& ling : zerglings) {
        if (ling && ling->exists()) {
            ling->attack(enemyBase);
        }
    }
}
