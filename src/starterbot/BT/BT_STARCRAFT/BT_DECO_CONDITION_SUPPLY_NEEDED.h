#pragma once
#include "../BT_DECORATOR.h"

class BT_DECO_CONDITION_SUPPLY_NEEDED : public BT_DECORATOR {
public:
    BT_DECO_CONDITION_SUPPLY_NEEDED(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
};
