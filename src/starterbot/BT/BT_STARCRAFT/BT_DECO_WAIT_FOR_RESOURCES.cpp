#include "BT_DECO_WAIT_FOR_RESOURCES.h"
#include "../Data.h"

BT_DECO_WAIT_FOR_RESOURCES::BT_DECO_WAIT_FOR_RESOURCES(std::string name, BT_NODE* parent, std::string buildingType)
    : BT_DECORATOR(name, parent), buildingType(buildingType) {}

BT_NODE::State BT_DECO_WAIT_FOR_RESOURCES::Evaluate(void* data) {
    Data* pData = (Data*)data;
    BWAPI::UnitType m_buildingType = BWAPI::UnitType::getType(buildingType);

    // Check if we have enough resources
    if (pData->currMinerals < m_buildingType.mineralPrice() || 
        pData->currGas < m_buildingType.gasPrice()) {
        return BT_NODE::RUNNING;  // Keep waiting for resources
    }

    // If resources are available, execute child node
    return BT_DECORATOR::Evaluate(data);
}

std::string BT_DECO_WAIT_FOR_RESOURCES::GetDescription() {
    return "DECO_WAIT_FOR_RESOURCES " + buildingType;
}
