#include "BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS::BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughUnits) {}


std::string BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS::GetDescription()
{
    return "BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS";
}

bool BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS::IsThereNotEnoughUnits(void *data)
{
    Data* pData = (Data*)data;
    
    const BWAPI::UnitType unitType = BWAPI::UnitType::getType("Zerg_Zergling");
    int unitsOwned = Tools::CountUnitsOfType(unitType, BWAPI::Broodwar->self()->getUnits());
    return unitsOwned >= pData->desiredUnits["Zerg_Zergling"];
}
