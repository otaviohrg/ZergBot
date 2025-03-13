#include "BT_DECO_WAIT_FOR_CONSTRUCTION.h"
#include "../Data.h"

BT_DECO_WAIT_FOR_CONSTRUCTION::BT_DECO_WAIT_FOR_CONSTRUCTION(std::string name, BT_NODE* parent, std::string buildingType)
    : BT_DECORATOR(name, parent), buildingType(buildingType) {}

BT_NODE::State BT_DECO_WAIT_FOR_CONSTRUCTION::Evaluate(void* data) {
    if(!buildingStarted) {
        BT_NODE::State childState = BT_DECORATOR::Evaluate(data);
        // Only proceed if child node succeeded (building process initiated)
        if (childState != BT_NODE::SUCCESS) {
            return childState;
        }
        buildingStarted = true;
    }
    
    Data* pData = (Data*)data;
    BWAPI::UnitType m_buildingType = BWAPI::UnitType::getType(buildingType);

    // Check if a building of this type is under construction
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == m_buildingType && unit->isBeingConstructed()) {
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::RUNNING;
}

std::string BT_DECO_WAIT_FOR_CONSTRUCTION::GetDescription() {
    return "DECO_WAIT_FOR_CONSTRUCTION " + buildingType;
}
