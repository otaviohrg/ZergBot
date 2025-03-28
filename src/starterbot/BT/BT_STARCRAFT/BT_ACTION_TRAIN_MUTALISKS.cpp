#include "BT_ACTION_TRAIN_MUTALISKS.h"

BT_ACTION_TRAIN_MUTALISKS::BT_ACTION_TRAIN_MUTALISKS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_TRAIN_MUTALISKS::Evaluate(void* data) {
    if (BWAPI::Broodwar->self()->minerals() >= 100 && BWAPI::Broodwar->self()->gas() >= 100) {
        for (auto& hatchery : BWAPI::Broodwar->self()->getUnits()) {
            if (hatchery->getType().isResourceDepot() && hatchery->isIdle()) {
                hatchery->train(BWAPI::UnitTypes::Zerg_Mutalisk);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::RUNNING;
}

std::string BT_ACTION_TRAIN_MUTALISKS::GetDescription() {
    return "Train Mutalisk if enough resources are available.";
}

BT_NODE::State BT_ACTION_TRAIN_MUTALISKS::TrainMutalisk(void* data) {
    return static_cast<BT_ACTION_TRAIN_MUTALISKS*>(data)->Evaluate(data);
}
