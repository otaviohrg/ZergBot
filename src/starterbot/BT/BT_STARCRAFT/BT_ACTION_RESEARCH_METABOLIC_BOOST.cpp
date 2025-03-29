#include "BT_ACTION_RESEARCH_METABOLIC_BOOST.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_RESEARCH_METABOLIC_BOOST::BT_ACTION_RESEARCH_METABOLIC_BOOST(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_RESEARCH_METABOLIC_BOOST::Evaluate(void* data)
{
    return ReturnState(ResearchMetabolicBoost(data));
}

std::string BT_ACTION_RESEARCH_METABOLIC_BOOST::GetDescription()
{
    return "Research Metabolic Boost";
}


BT_NODE::State BT_ACTION_RESEARCH_METABOLIC_BOOST::ResearchMetabolicBoost(void* data)
{
    auto* pData = static_cast<Data*>(data);

    const BWAPI::UnitType spawningPoolType = BWAPI::UnitTypes::Zerg_Spawning_Pool;
    const BWAPI::TechType upgradeType = BWAPI::TechTypes::None;
    const BWAPI::UpgradeType metabolicBoost = BWAPI::UpgradeTypes::Metabolic_Boost;

    // Find a completed Spawning Pool
    for (const auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType() == spawningPoolType && unit->isCompleted() && !unit->isUpgrading()) {
            // Check if we have enough resources
            if (BWAPI::Broodwar->self()->minerals() >= metabolicBoost.mineralPrice() &&
                BWAPI::Broodwar->self()->gas() >= metabolicBoost.gasPrice()) 
            {
                if (unit->upgrade(metabolicBoost)) {
                    return BT_NODE::SUCCESS;
                } else {
                    return BT_NODE::FAILURE;
                }
            }
        }
    }

    return BT_NODE::FAILURE;
}
