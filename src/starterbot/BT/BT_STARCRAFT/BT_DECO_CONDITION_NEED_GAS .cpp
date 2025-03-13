#include "BT_DECO_CONDITION_NEED_GAS.h"
#include "../Data.h"

BT_DECO_CONDITION_NEED_GAS::BT_DECO_CONDITION_NEED_GAS(std::string name, BT_NODE* parent)
    : BT_DECORATOR(name, parent) {}

BT_NODE::State BT_DECO_CONDITION_NEED_GAS::Evaluate(void* data) {
    Data* pData = (Data*)data;

    // Check if the current gas is below the threshold for needing gas
    if (pData->currMinerals < 100 || pData->currSupply < 10) {
        return BT_NODE::SUCCESS;
    }
    return BT_NODE::FAILURE;
}

std::string BT_DECO_CONDITION_NEED_GAS::GetDescription() {
    return "CONDITION NEED GAS";
}
