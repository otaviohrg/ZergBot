#include "BT_DECO_CONDITION_SUPPLY_NEEDED.h"
#include "../Data.h"

BT_DECO_CONDITION_SUPPLY_NEEDED::BT_DECO_CONDITION_SUPPLY_NEEDED(std::string name, BT_NODE* parent)
    : BT_DECORATOR(name, parent) {}

BT_NODE::State BT_DECO_CONDITION_SUPPLY_NEEDED::Evaluate(void* data) {
    Data* pData = (Data*)data;

    // Check if we need more supply
    if (pData->currSupply < 10) {
        return BT_NODE::SUCCESS;
    }
    return BT_NODE::FAILURE;
}

std::string BT_DECO_CONDITION_SUPPLY_NEEDED::GetDescription() {
    return "CONDITION SUPPLY NEEDED";
}
