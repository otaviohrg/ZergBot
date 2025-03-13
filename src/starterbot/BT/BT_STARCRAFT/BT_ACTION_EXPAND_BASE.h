#pragma once
#include "../BT_ACTION.h"

class BT_ACTION_EXPAND_BASE : public BT_ACTION {
public:
    BT_ACTION_EXPAND_BASE(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;

private:
    BT_NODE::State ExpandBase(void* data);
};

