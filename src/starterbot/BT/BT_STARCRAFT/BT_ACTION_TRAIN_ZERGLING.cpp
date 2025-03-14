#include "BT_ACTION_TRAIN_ZERGLING.h"
#include "../../Tools.h"
#include "../Data.h"

BT_ACTION_TRAIN_ZERGLING::BT_ACTION_TRAIN_ZERGLING(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BT_ACTION_TRAIN_ZERGLING::Evaluate(void* data)
{
    return ReturnState(TrainWorker(data));
}

std::string BT_ACTION_TRAIN_ZERGLING::GetDescription()
{
    return "TRAIN LING";
}


BT_NODE::State BT_ACTION_TRAIN_ZERGLING::TrainWorker(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::UnitType zergling = BWAPI::UnitType::getType("Zerg_Zergling");
    BWAPI::Unit larva = Tools::GetAvailableLarva();
    if (larva) {
        larva->morph(zergling);
    } else {
        return BT_NODE::FAILURE;
    }
    return BT_NODE::SUCCESS;
}