#pragma once
#include "../BT_DECO_CONDITION.h"

class BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS : public BT_DECO_CONDITION {
public:
    BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
};
