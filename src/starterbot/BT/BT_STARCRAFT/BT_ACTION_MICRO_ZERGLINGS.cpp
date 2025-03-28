#include "BT_ACTION_MICRO_ZERGLINGS.h"

BT_ACTION_MICRO_ZERGLINGS::BT_ACTION_MICRO_ZERGLINGS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_MICRO_ZERGLINGS::Evaluate(void* data) {
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == BWAPI::UnitTypes::Zerg_Zergling && unit->isIdle()) {
            BWAPI::UnitInterface* target = nullptr;
            double closestDist = std::numeric_limits<double>::max();

            for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits()) {
                if (enemy->exists()) {
                    double dist = unit->getDistance(enemy);
                    if (dist < closestDist) {
                        closestDist = dist;
                        target = enemy;
                    }
                }
            }

            if (target) {
                unit->attack(target);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::RUNNING;
}

std::string BT_ACTION_MICRO_ZERGLINGS::GetDescription() {
    return "Micro Zerglings to attack the closest enemy unit.";
}

BT_NODE::State BT_ACTION_MICRO_ZERGLINGS::MicroZerglings(void* data) {
    return static_cast<BT_ACTION_MICRO_ZERGLINGS*>(data)->Evaluate(data);
}
