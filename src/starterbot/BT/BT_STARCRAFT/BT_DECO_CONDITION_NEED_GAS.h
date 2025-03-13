#pragma once
#include "../BT_DECORATOR.h"

class BT_DECO_CONDITION_NEED_GAS : public BT_DECORATOR {
public:
    BT_DECO_CONDITION_NEED_GAS(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
};
