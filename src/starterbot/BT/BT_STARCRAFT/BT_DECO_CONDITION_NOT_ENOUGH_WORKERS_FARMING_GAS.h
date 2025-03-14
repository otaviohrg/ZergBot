#pragma once
#include "BT_DECO_CONDITION.h"

class BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS : public BT_DECO_CONDITION {
public:
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS(std::string name, BT_NODE* parent);

    std::string GetDescription() override;
    static bool IsThereNotEnoughWorkersFarmingGas(void* data);
};

