#pragma once
#include "../BT_ACTION.h"

class BT_ACTION_SEND_IDLE_SCOUT : public BT_ACTION {
public:
    BT_ACTION_SEND_IDLE_SCOUT(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;
};
