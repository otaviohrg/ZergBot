#pragma once
#include <cassert>
#include "../BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_SET_DESIRED_WORKERS: public BT_ACTION {
public:
    BT_SET_DESIRED_WORKERS(std::string name, BT_NODE* parent, int nWantedWorkersTotal, int nWantedWorkersFarmingMinerals, int nWantedWorkersFarmingGas);

private:
    int nWantedWorkersTotal;
    int nWantedWorkersFarmingMinerals;
    int nWantedWorkersFarmingGas;
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State SetDesiredWorkers(void* data);
};
//----------