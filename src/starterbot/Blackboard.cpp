#include "Blackboard.h"

Blackboard::Blackboard()
{
    pData = new Data();
    pData->currMinerals = 0;
    pData->thresholdMinerals = THRESHOLD1_MINERALS;
    pData->currSupply = 0;
    pData->thresholdSupply = THRESHOLD1_UNUSED_SUPPLY;
    pData->currentWorkers = 0;
    pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;
    pData->nWantedWorkersFarmingMinerals = NWANTED_WORKERS_FARMING_MINERALS;
    pData->nWantedWorkersFarmingGas = NWANTED_WORKERS_FARMING_GAS;  // ✅ Initialize this
}

