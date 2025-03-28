#include "BT_SET_DESIRED_UNITS.h"
#include "../../Tools.h"
#include "../Data.h"

BT_SET_DESIRED_UNITS::BT_SET_DESIRED_UNITS(std::string name,BT_NODE* parent, int wantedUnit, std::string unitType)
    :  BT_ACTION(name,parent), wantedUnit(wantedUnit), unitType(unitType) {}

BT_NODE::State BT_SET_DESIRED_UNITS::Evaluate(void* data)
{
    return ReturnState(SetDesiredUnits(data));
}

std::string BT_SET_DESIRED_UNITS::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_SET_DESIRED_UNITS::SetDesiredUnits(void* data)
{
    Data* pData = (Data*)data;

    // Set the desired number of workers
    pData->desiredUnits[unitType] = std::max(pData->desiredUnits[unitType], wantedUnit);

    std::cout << "Set wanted units of type " << unitType << " to " << pData->desiredUnits[unitType] << std::endl;
    return BT_NODE::SUCCESS;
}