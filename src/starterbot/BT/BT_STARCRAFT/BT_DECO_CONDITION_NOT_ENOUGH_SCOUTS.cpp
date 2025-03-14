#include "BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS.h"
#include "../Data.h"

// Define the condition callback function to check if there are enough scouts.
bool NotEnoughScouts(void* data) {
    Data* pData = (Data*)data;
    
    // Check if the number of scouts (both farming minerals and gas) is less than the desired number.
    return (pData->unitsFarmingMinerals.size() + pData->unitsFarmingGas.size() < pData->nWantedWorkersTotal);
}

BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS::BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, NotEnoughScouts) {}  // Pass the condition callback to the base class constructor.

BT_NODE::State BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS::Evaluate(void* data) {
    // Call the base class' Evaluate method which will call the condition callback
    if (ConditionCBK(data)) {
        return BT_NODE::SUCCESS;  // Condition is met (not enough scouts), return SUCCESS
    }
    
    return BT_NODE::FAILURE;  // Condition is not met (enough scouts), return FAILURE
}

std::string BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS::GetDescription() {
    return "Check if there are not enough scouts to send out.";
}
