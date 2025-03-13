#include "BT_ACTION_BUILD_SUPPLY_DEPOT.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_BUILD_SUPPLY_DEPOT::BT_ACTION_BUILD_SUPPLY_DEPOT(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_BUILD_SUPPLY_DEPOT::Evaluate(void* data) {
    return ReturnState(BuildSupplyDepot(data));
}

std::string BT_ACTION_BUILD_SUPPLY_DEPOT::GetDescription() {
    return "BUILD SUPPLY DEPOT";
}

BT_NODE::State BT_ACTION_BUILD_SUPPLY_DEPOT::BuildSupplyDepot(void* data) {
    Data* pData = (Data*)data;

    // Build supply depot logic
    const BWAPI::UnitType supplyDepotType = BWAPI::UnitTypes::Terran_Supply_Depot;
    BWAPI::TilePosition buildLocation = BWAPI::Broodwar->self()->getStartLocation();

    if (BWAPI::Broodwar->canBuildHere(buildLocation, supplyDepotType)) {
        BWAPI::Unit builder = Tools::GetBuilderUnit();
        builder->build(supplyDepotType, buildLocation);
        return BT_NODE::SUCCESS;
    }

    return BT_NODE::FAILURE;
}
