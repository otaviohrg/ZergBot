#include "CombatModule.h"
#include "../Tools.h"

CombatModule::CombatModule(){
    pCombatBT = nullptr;
    pCombatBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_PARALLEL_SEQUENCER* pSequence = new BT_PARALLEL_SEQUENCER("MainSequence", pCombatBT, 10);

    BT_DECO_REPEATER* pMidGameRepeater = new BT_DECO_REPEATER("RepeatForeverTrainingOverlords", pSequence, 0, true, false, false);
    BT_SELECTOR * pRace = new BT_SELECTOR("Selector", pMidGameRepeater, 3);
    
    BT_DECO_CONDITION* pOpponentIsZerg = new BT_DECO_CONDITION("OpponentIsZerg", pRace, Tools::IsEnemyZerg);
    BT_DECO_CONDITION* pOpponentIsTerran = new BT_DECO_CONDITION("OpponentIsTerran", pRace, Tools::IsEnemyTerran);
    BT_DECO_CONDITION* pOpponentIsProtoss = new BT_DECO_CONDITION("OpponentIsProtoss", pRace, Tools::IsEnemyProtoss);

    BT_DECO_REPEATER* pTrainMutaForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildMuta", pOpponentIsTerran, 0, true, false, false);
    BT_ACTION_TRAIN_MUTALISKS* pTrainMuta = new BT_ACTION_TRAIN_MUTALISKS("TrainMuta", pTrainMutaForeverRepeater);
    
    BT_DECO_REPEATER* pTrainHydraForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildHydra", pOpponentIsProtoss, 0, true, false, false);
    BT_ACTION_TRAIN_MUTALISKS* pTrainHydra = new BT_ACTION_TRAIN_MUTALISKS("TrainHydra", pTrainHydraForeverRepeater);

    BT_DECO_REPEATER* pBuildLingsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildLings", pOpponentIsZerg, 0, true, false, false);
    BT_ACTION_TRAIN_ZERGLING* pBuildInfiniteLings = new BT_ACTION_TRAIN_ZERGLING("TrainLings", pBuildLingsForeverRepeater);

    BT_DECO_REPEATER* pBuild10LingsRepeater = new BT_DECO_REPEATER("RepeatBuildLings", pSequence, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS* pNotEnoughLings = new BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS("NotEnoughLings", pBuild10LingsRepeater);
    BT_ACTION_TRAIN_ZERGLING* pBuildLings = new BT_ACTION_TRAIN_ZERGLING("TrainLings", pNotEnoughLings);
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