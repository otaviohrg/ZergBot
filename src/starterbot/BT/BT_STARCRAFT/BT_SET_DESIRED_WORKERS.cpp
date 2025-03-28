#include "BT_SET_DESIRED_WORKERS.h"
#include "../../Tools.h"
#include "../Data.h"

BT_SET_DESIRED_WORKERS::BT_SET_DESIRED_WORKERS(std::string name,BT_NODE* parent, int nWantedWorkersTotal, int nWantedWorkersFarmingMinerals, int nWantedWorkersFarmingGas)
    :  BT_ACTION(name,parent), nWantedWorkersTotal(nWantedWorkersTotal), nWantedWorkersFarmingMinerals(nWantedWorkersFarmingMinerals), nWantedWorkersFarmingGas(nWantedWorkersFarmingGas) {}

BT_NODE::State BT_SET_DESIRED_WORKERS::Evaluate(void* data)
{
    return ReturnState(SetDesiredWorkers(data));
}

std::string BT_SET_DESIRED_WORKERS::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_SET_DESIRED_WORKERS::SetDesiredWorkers(void* data)
{
    Data* pData = (Data*)data;

    // Set the desired number of workers
    pData->nWantedWorkersTotal = std::max(pData->nWantedWorkersTotal, nWantedWorkersTotal);
    pData->nWantedWorkersFarmingMinerals = std::max(pData->nWantedWorkersFarmingMinerals, nWantedWorkersFarmingMinerals);
    pData->nWantedWorkersFarmingGas = std::max(pData->nWantedWorkersFarmingGas, nWantedWorkersFarmingGas);

    std::cout << "Set wanted workers to " << pData->nWantedWorkersTotal << std::endl;
    std::cout << "Set wanted workers farming minerals to " << pData->nWantedWorkersFarmingMinerals << std::endl;
    std::cout << "Set wanted workers farming gas to " << pData->nWantedWorkersFarmingGas << std::endl;

    return BT_NODE::SUCCESS;
}