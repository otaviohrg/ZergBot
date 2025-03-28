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
    pData->nWantedWorkersFarmingGas = 0;
    pData->unitsFarmingMinerals = std::unordered_set<BWAPI::Unit>();
    pData->unitsFarmingGas = std::unordered_set<BWAPI::Unit>();
    pData->unitsScouting = std::unordered_set<BWAPI::Unit>();   
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
    pData->currSupply = BWAPI::Broodwar->self()->supplyUsed();
}


void Blackboard::setEnemyBase(const BWAPI::TilePosition& position) {
    enemyBase = position;
    pData->enemyBase = position;
}

BWAPI::TilePosition Blackboard::getEnemyBase() {
    return enemyBase;
}
