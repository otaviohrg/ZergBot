#include "BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS::BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughWorkersFarmingGas) {}

std::string BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GAS::IsThereNotEnoughWorkersFarmingGas(void* data)
{
    Data* pData = (Data*)data;
    
    return (int)pData->unitsFarmingGas.size() < pData->nWantedWorkersFarmingGas;
}
