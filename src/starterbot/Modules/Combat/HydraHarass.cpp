#include "HydraHarass.h"

HydraBust::HydraBust() {}

void HydraBust::execute() {
    BWAPI::Broodwar->printf("Executing Hydra Bust...");

    bool hasHydraliskDen = false;
    for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk_Den) {
            hasHydraliskDen = true;
            break;
        }
    }
    if (!hasHydraliskDen) {
        return;
    }

    for (auto &hatchery : BWAPI::Broodwar->self()->getUnits()) {
        if (hatchery->getType() == BWAPI::UnitTypes::Zerg_Hatchery && hatchery->isCompleted()) {
            hatchery->train(BWAPI::UnitTypes::Zerg_Hydralisk);
        }
    }

    for (auto &den : BWAPI::Broodwar->self()->getUnits()) {
        if (den->getType() == BWAPI::UnitTypes::Zerg_Hydralisk_Den && den->isCompleted()) {
            if (!BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Grooved_Spines)) {
                den->upgrade(BWAPI::UpgradeTypes::Grooved_Spines);
            }
            if (!BWAPI::Broodwar->self()->isUpgrading(BWAPI::UpgradeTypes::Muscular_Augments)) {
                den->upgrade(BWAPI::UpgradeTypes::Muscular_Augments);
            }
        }
    }

    if (combatSquad.isEmpty()) {
        for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk) {
                combatSquad.addUnit(unit);
                if (combatSquad.units.size() >= 12) {
                    BWAPI::Position target = from_Tile_position(blackboard->getEnemyBase());
                    for (auto &hydra : combatSquad.units) {
                        hydra->attack(target);
                    }
                    combatSquad.units.clear();
                }
            }
        }
    }
}
