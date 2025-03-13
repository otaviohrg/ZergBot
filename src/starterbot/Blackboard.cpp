#include "Blackboard.h"

Blackboard::Blackboard()
{
    pData = new Data();
    pData->currMinerals = 0;
    pData->thresholdMinerals = THRESHOLD1_MINERALS;
    pData->currSupply = 0;
    pData->thresholdSupply = THRESHOLD1_UNUSED_SUPPLY;

    pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;
    pData->nWantedWorkersFarmingMinerals = NWANTED_WORKERS_FARMING_MINERALS;
}

void Blackboard::reserveResources(int minerals, int gas)
{
    pData->reservedMinerals += minerals;
    pData->reservedGas += gas;
}

void Blackboard::unreserveResources(int minerals, int gas)
{
    pData->reservedMinerals -= minerals;
    pData->reservedGas -= gas;
}

void Blackboard::updateResources()
{
    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    pData->currGas = BWAPI::Broodwar->self()->gas();
}

