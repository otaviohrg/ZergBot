#include "BaseModule.h"
#include "../Tools.h"

BaseModule::BaseModule(){
    pBaseBT = nullptr;
    pBaseBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBaseBT, 10);

    //Build Additional Supply Provider
    BT_DECO_REPEATER* pBuildSupplyProviderForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildSupplyProvider", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pBuildSupplyProviderForeverRepeater);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildSupplyProvider = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildSupplyProvider", pNotEnoughSupply);
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