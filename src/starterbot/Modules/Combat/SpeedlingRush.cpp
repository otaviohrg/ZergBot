#include "SpeedlingRush.h"

SpeedlingRush::SpeedlingRush() {}

void SpeedlingRush::execute() {
    BWAPI::Broodwar->printf("Executing Speedling Rush...");

    bool hasSpawningPool = false;
    for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool) {
            hasSpawningPool = true;
            break;
        }
    }
    if (!hasSpawningPool) {
        return;  // Wait until Spawning Pool is built
    }

    for (auto &hatchery : BWAPI::Broodwar->self()->getUnits()) {
        if (hatchery->getType() == BWAPI::UnitTypes::Zerg_Hatchery && hatchery->isCompleted()) {
            hatchery->train(BWAPI::UnitTypes::Zerg_Zergling);
        }
    }

    if (!BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Metabolic_Boost)) {
        for (auto &spawningPool : BWAPI::Broodwar->self()->getUnits()) {
            if (spawningPool->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool && spawningPool->isCompleted()) {
                spawningPool->upgrade(BWAPI::UpgradeTypes::Metabolic_Boost);
                break;
            }
        }
    }

    if (combatSquad.isEmpty()) {
        for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling) {
                combatSquad.addUnit(unit);
                if (combatSquad.units.size() >= 12) {
                    BWAPI::Position target = from_Tile_position(blackboard->getEnemyBase());
                    for (auto &zergling : combatSquad.units) {
                        zergling->attack(target);
                    }
                    combatSquad.units.clear();
                }
            }
        }
    }
}
