#include "BT_ACTION_HARASS_WORKERS.h"

BT_ACTION_HARASS_WORKERS::BT_ACTION_HARASS_WORKERS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_HARASS_WORKERS::Evaluate(void* data) {
    // Iterate through Zerg units (Zerglings or Mutalisks)
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        // Check if the unit is idle and is a Zergling or Mutalisk
        if ((unit->getType() == BWAPI::UnitTypes::Zerg_Zergling || unit->getType() == BWAPI::UnitTypes::Zerg_Mutalisk) && unit->isIdle()) {
            BWAPI::UnitInterface* target = nullptr;
            double closestDist = std::numeric_limits<double>::max();

            // Find the closest enemy worker
            for (auto& enemyUnit : BWAPI::Broodwar->enemy()->getUnits()) {
                if (enemyUnit->getType().isWorker() && enemyUnit->exists()) {
                    double dist = unit->getDistance(enemyUnit);
                    if (dist < closestDist) {
                        closestDist = dist;
                        target = enemyUnit;
                    }
                }
            }

            // If a target worker is found, attack the worker
            if (target) {
                unit->attack(target);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::RUNNING;
}

std::string BT_ACTION_HARASS_WORKERS::GetDescription() {
    return "Harass enemy workers by attacking the closest worker with idle Mutalisks or Zerglings.";
}

BT_NODE::State BT_ACTION_HARASS_WORKERS::HarassWorkers(void* data) {
    return static_cast<BT_ACTION_HARASS_WORKERS*>(data)->Evaluate(data);
}
