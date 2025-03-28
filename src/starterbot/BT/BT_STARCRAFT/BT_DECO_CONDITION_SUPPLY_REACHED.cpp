#include "BT_DECO_CONDITION_SUPPLY_REACHED.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_DECO_CONDITION_SUPPLY_REACHED::BT_DECO_CONDITION_SUPPLY_REACHED(std::string name, BT_NODE* parent, int threshold)
    : BT_DECO_CONDITION(name, parent, IsSupplyReached), m_threshold(threshold) {
}

std::string BT_DECO_CONDITION_SUPPLY_REACHED::GetDescription()
{
    return "DECO_CONDITION_SUPPLY_REACHED (Threshold: " + std::to_string(m_threshold) + ")";
}

bool BT_DECO_CONDITION_SUPPLY_REACHED::IsSupplyReached(void* data)
{
    Data* pData = static_cast<Data*>(data);

    // Get total supply available
    int totalSupply = BWAPI::Broodwar->self()->supplyUsed();

    // If current total supply reaches the threshold, return true
    if (totalSupply >= pData->thresholdSupply) {
        return BT_NODE::SUCCESS;
    }
    

    return BT_NODE::FAILURE;
}