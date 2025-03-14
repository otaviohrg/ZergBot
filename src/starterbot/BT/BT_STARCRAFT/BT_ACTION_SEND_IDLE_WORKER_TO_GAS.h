#pragma once
#include "../BT_ACTION.h"

class BT_ACTION_SEND_IDLE_WORKER_TO_GAS : public BT_ACTION {
public:
    BT_ACTION_SEND_IDLE_WORKER_TO_GAS(std::string name, BT_NODE* parent);
    BT_NODE::State Evaluate(void* data) override;
    std::string GetDescription() override;

private:
    BT_NODE::State SendIdleWorkerToGas(void* data);
};

