#include "BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS::BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughUnits) {}


std::string BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_WORKERS";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS::IsThereNotEnoughUnits(void *data)
{
    Data* pData = (Data*)data;

    std::cout << "Checking if there are not enough Zerglings" << std::endl;
    std::cout << "Desired Zerglings: " << pData->desiredUnits["Zerg_Zergling"] << std::endl;
    
    const BWAPI::UnitType unitType = BWAPI::UnitType::getType("Zerg_Zergling");
    int unitsOwned = Tools::CountUnitsOfType(unitType, BWAPI::Broodwar->self()->getUnits());
    return unitsOwned >= pData->desiredUnits["Zerg_Zergling"];
}
