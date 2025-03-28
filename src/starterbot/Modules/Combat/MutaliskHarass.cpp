#include "MutaliskHarass.h"

MutaliskHarass::MutaliskHarass() {}

void MutaliskHarass::execute() {
    BWAPI::Broodwar->printf("Executing Mutalisk Harass...");

    bool hasSpire = false;
    for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Spire) {
            hasSpire = true;
            break;
        }
    }
    if (!hasSpire) {
        return;
    }

    for (auto &hatchery : BWAPI::Broodwar->self()->getUnits()) {
        if (hatchery->getType() == BWAPI::UnitTypes::Zerg_Hatchery && hatchery->isCompleted()) {
            hatchery->train(BWAPI::UnitTypes::Zerg_Mutalisk);
        }
    }

    if (combatSquad.isEmpty()) {
        for (auto &unit : BWAPI::Broodwar->self()->getUnits()) {
            if (unit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk) {
                combatSquad.addUnit(unit);
                if (combatSquad.units.size() >= 6) {
                    BWAPI::Position target = from_Tile_position(blackboard->getEnemyBase());
                    for (auto &mutalisk : combatSquad.units) {
                        mutalisk->attack(target);
                    }
                    combatSquad.units.clear();
                }
            }
        }
    }
}
