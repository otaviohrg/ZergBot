#include "ZergVsZerg.h"

ZergVsZerg::ZergVsZerg() 
    : BT_DECORATOR("CombatEntryPoint", nullptr)
{
    pCombatBT = new BT_DECORATOR("CombatEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainCombatSequence", pCombatBT, 10);

    // Train Zerglings
    BT_ACTION_TRAIN_ZERGLING* pTrainLings = new BT_ACTION_TRAIN_ZERGLING("TrainZerglings", pMainSeq);

    // Attack Move
    BT_ACTION_ATTACK_MOVE* pAttackMove = new BT_ACTION_ATTACK_MOVE("AttackMove", pMainSeq);

    // Micro Zerglings
    BT_ACTION_MICRO_ZERGLINGS* pMicroLings = new BT_ACTION_MICRO_ZERGLINGS("MicroZerglings", pMainSeq);
}

ZergVsZerg::~ZergVsZerg() {
    delete pCombatBT;
}
