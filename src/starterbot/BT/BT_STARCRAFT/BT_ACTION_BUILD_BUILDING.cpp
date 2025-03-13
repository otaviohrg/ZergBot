#include "BT_ACTION_BUILD_BUILDING.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_BUILD_BUILDING::BT_ACTION_BUILD_BUILDING(std::string name,BT_NODE* parent,std::string buildingType): BT_ACTION(name,parent), buildingType(buildingType) {}

BT_ACTION_BUILD_BUILDING::State BT_ACTION_BUILD_BUILDING::Evaluate(void* data)
{
    return ReturnState(BuildConstruction(data));
}

std::string BT_ACTION_BUILD_BUILDING::GetDescription()
{
    return "BUILD " + buildingType;
}



BT_NODE::State BT_ACTION_BUILD_BUILDING::BuildConstruction(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::UnitType m_buildingType = BWAPI::UnitType::getType(buildingType);

    const bool startedBuilding = Tools::BuildBuilding(m_buildingType);
    if (!startedBuilding)
        return BT_NODE::FAILURE;
    std::cout << "Building " << buildingType << " started: " << startedBuilding << std::endl;

    return BT_NODE::SUCCESS;
}