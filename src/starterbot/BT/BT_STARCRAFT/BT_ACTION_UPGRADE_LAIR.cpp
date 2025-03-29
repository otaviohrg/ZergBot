#include "BT_ACTION_UPGRADE_LAIR.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_UPGRADE_LAIR::BT_ACTION_UPGRADE_LAIR(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_UPGRADE_LAIR::Evaluate(void* data)
{
    return ReturnState(UpgradeLair(data));
}

std::string BT_ACTION_UPGRADE_LAIR::GetDescription()
{
    return "Upgrade Lair";
}


BT_NODE::State BT_ACTION_UPGRADE_LAIR::UpgradeLair(void* data)
{
    auto* pData = static_cast<Data*>(data);

    const BWAPI::Unit myHatchery = Tools::GetDepot();  // Assuming this gets a Hatchery

    // Check if we have a valid Hatchery, enough resources, and it's not morphing
    if (myHatchery && myHatchery->getType() == BWAPI::UnitTypes::Zerg_Hatchery &&
        myHatchery->isCompleted() && !myHatchery->isMorphing()) 
    {
        if (myHatchery->morph(BWAPI::UnitTypes::Zerg_Lair)) {
            return BT_NODE::SUCCESS;
        } else {
            return BT_NODE::FAILURE;
        }
    }

    return BT_NODE::FAILURE;
}