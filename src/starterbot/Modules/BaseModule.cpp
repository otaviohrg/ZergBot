#include "BaseModule.h"
#include "../Tools.h"

BaseModule::BaseModule(){
    pBaseBT = nullptr;
    pBaseBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_SEQUENCER* pSequence = new BT_SEQUENCER("MainSequence", pBaseBT, 10);

    //Build Pool after 9th Worker
    BT_DECO_UNTIL_SUCCESS* pUntil9Workers = new BT_DECO_UNTIL_SUCCESS("Until9Workers", pSequence);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pUntil9Workers);
    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForPool = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForPool", pNotEnoughSupply, "Zerg_Spawning_Pool");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResources = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForPool, "Zerg_Spawning_Pool");
    BT_ACTION_BUILD_BUILDING* pBuildSupplyProvider = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResources, "Zerg_Spawning_Pool");

    //Build Overlord
    BT_DECO_UNTIL_SUCCESS* pUntilBuildOverlord = new BT_DECO_UNTIL_SUCCESS("Until9Workers", pSequence);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildOverlord = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildOverlord", pUntilBuildOverlord);
}

BaseModule::~BaseModule(){
    delete (BT_DECORATOR*)pBaseBT;
}

void BaseModule::updateBase(Blackboard *bb){
    bb->pData->currSupply = Tools::GetUnusedSupply(true);

    if (pBaseBT != nullptr && pBaseBT->Evaluate(bb->pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pBaseBT;
        pBaseBT = nullptr;
    }
}