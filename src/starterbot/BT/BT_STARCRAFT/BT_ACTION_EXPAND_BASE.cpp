#include "BT_ACTION_EXPAND_BASE.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_EXPAND_BASE::BT_ACTION_EXPAND_BASE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_EXPAND_BASE::Evaluate(void* data) {
    return ReturnState(ExpandBase(data));
}

std::string BT_ACTION_EXPAND_BASE::GetDescription() {
    return "EXPAND BASE";
}

BT_NODE::State BT_ACTION_EXPAND_BASE::ExpandBase(void* data) {
    Data* pData = (Data*)data;

    // Add your base expansion logic here
    const BWAPI::UnitType baseType = BWAPI::UnitTypes::Zerg_Hatchery;
    BWAPI::TilePosition buildLocation = BWAPI::Broodwar->self()->getStartLocation();

    // Check if a base can be built at the specified location
    if (BWAPI::Broodwar->canBuildHere(buildLocation, baseType)) {
        BWAPI::Unit builder = Tools::GetBuilderUnit();
        builder->build(baseType, buildLocation);
        return BT_NODE::SUCCESS;
    }

    return BT_NODE::FAILURE;
}
