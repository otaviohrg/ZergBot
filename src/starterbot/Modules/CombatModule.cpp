#include "CombatModule.h"
#include "../Tools.h"

CombatModule::CombatModule(){
    pCombatBT = nullptr;
    pCombatBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_SEQUENCER* pSequence = new BT_SEQUENCER("MainSequence", pCombatBT, 10);

    BT_DECO_REPEATER* pBuildLingsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildLings", pSequence, 0, true, false, false);
    BT_ACTION_TRAIN_ZERGLING* pSendWorkerToMinerals = new BT_ACTION_TRAIN_ZERGLING("SendWorkerToMinerals", pBuildLingsForeverRepeater);
}

CombatModule::~CombatModule(){
    delete (BT_DECORATOR*)pCombatBT;
}

void CombatModule::updateCombat(Blackboard *bb){
    if (pCombatBT != nullptr && pCombatBT->Evaluate(bb->pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pCombatBT;
        pCombatBT = nullptr;
    }
}