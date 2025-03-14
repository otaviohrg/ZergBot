#include "BT_ACTION_BUILD_REFINERY.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_BUILD_REFINERY::BT_ACTION_BUILD_REFINERY(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_REFINERY::Evaluate(void* data) {
    return ReturnState(BuildRefinery(data));
}

std::string BT_ACTION_BUILD_REFINERY::GetDescription() {
    return "BUILD REFINERY";
}

BT_NODE::State BT_ACTION_BUILD_REFINERY::BuildRefinery(void* data) {
    Data* pData = (Data*)data;

    // Add your refinery building logic here
    const BWAPI::UnitType refineryType = BWAPI::UnitTypes::Zerg_Extractor;
    BWAPI::Unit myDepot = Tools::GetDepot();

    if (myDepot) {
        BWAPI::TilePosition buildLocation = BWAPI::Broodwar->self()->getStartLocation();
        if (BWAPI::Broodwar->canBuildHere(buildLocation, refineryType)) {
            myDepot->build(refineryType, buildLocation);
            return BT_NODE::SUCCESS;
        }
    }
    return BT_NODE::FAILURE;
}
