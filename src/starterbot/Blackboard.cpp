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
    std::cout << "Updating resources" << std::endl;
    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    std::cout << "Current minerals: " << pData->currMinerals << std::endl;
    pData->currGas = BWAPI::Broodwar->self()->gas();
    std::cout << "Current gas: " << pData->currGas << std::endl;
    pData->currSupply = BWAPI::Broodwar->self()->supplyUsed();
    std::cout << "Current supply: " << pData->currSupply << std::endl;
}


void Blackboard::setEnemyBase(const BWAPI::TilePosition& position) {
    enemyBase = position;
    pData->enemyBase = position;
}

BWAPI::TilePosition Blackboard::getEnemyBase() {
    return enemyBase;
}
