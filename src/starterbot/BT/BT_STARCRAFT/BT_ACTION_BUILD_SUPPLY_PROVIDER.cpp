#include "BT_ACTION_BUILD_SUPPLY_PROVIDER.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_BUILD_SUPPLY_PROVIDER::BT_ACTION_BUILD_SUPPLY_PROVIDER(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_BUILD_SUPPLY_PROVIDER::Evaluate(void* data)
{
    return ReturnState(BuildSupplyProvider(data));
}

std::string BT_ACTION_BUILD_SUPPLY_PROVIDER::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_SUPPLY_PROVIDER::BuildSupplyProvider(void* data)
{
    Data* pData = (Data*)data;

    // let's build a supply provider
    const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();
    const BWAPI::Unit myDepot = Tools::GetDepot();

    // if we have a valid depot unit and it's currently not training something, train a worker
    // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
    if (myDepot && !myDepot->isTraining()) {
        myDepot->train(supplyProviderType);
        BWAPI::Error error = BWAPI::Broodwar->getLastError();
        if (error != BWAPI::Errors::None)
            return BT_NODE::FAILURE;
        else return BT_NODE::SUCCESS;
    }

    return BT_NODE::FAILURE;
}