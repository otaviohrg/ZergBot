#include "BT_ACTION_TRAIN_HYDRALISKS.h"

BT_ACTION_TRAIN_HYDRALISKS::BT_ACTION_TRAIN_HYDRALISKS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_TRAIN_HYDRALISKS::Evaluate(void* data) {
    if (BWAPI::Broodwar->self()->minerals() >= 100 && BWAPI::Broodwar->self()->gas() >= 50) {
        for (auto& hatchery : BWAPI::Broodwar->self()->getUnits()) {
            if (hatchery->getType().isResourceDepot() && hatchery->isIdle()) {
                hatchery->train(BWAPI::UnitTypes::Zerg_Hydralisk);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::RUNNING;
}

std::string BT_ACTION_TRAIN_HYDRALISKS::GetDescription() {
    return "Train Hydralisk if enough resources are available.";
}

BT_NODE::State BT_ACTION_TRAIN_HYDRALISKS::TrainHydralisk(void* data) {
    return static_cast<BT_ACTION_TRAIN_HYDRALISKS*>(data)->Evaluate(data);
}
