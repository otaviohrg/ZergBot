#include "BT_SET_DESIRED_SUPPLY.h"
#include "../../Tools.h"
#include "../Data.h"

BT_SET_DESIRED_SUPPLY::BT_SET_DESIRED_SUPPLY(std::string name,BT_NODE* parent, int wantedSupply)
    :  BT_ACTION(name,parent), wantedSupply(wantedSupply) {}

BT_NODE::State BT_SET_DESIRED_SUPPLY::Evaluate(void* data)
{
    return ReturnState(SetWantedSupply(data));
}

std::string BT_SET_DESIRED_SUPPLY::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_SET_DESIRED_SUPPLY::SetWantedSupply(void* data)
{
    Data* pData = (Data*)data;

    // Set the desired number of workers
    pData->thresholdSupply = std::max(pData->nWantedWorkersTotal, wantedSupply);
    
    std::cout << "Set wanted supply to " << pData->thresholdSupply << std::endl;

    return BT_NODE::SUCCESS;
}