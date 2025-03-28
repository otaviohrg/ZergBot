#include "ZergVsProtoss.h"

ZergVsProtoss::ZergVsProtoss() 
    : BT_DECORATOR("CombatEntryPoint", nullptr)
{
    pCombatBT = new BT_DECORATOR("CombatEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainCombatSequence", pCombatBT, 10);

    // Train Hydralisks
    BT_ACTION_TRAIN_HYDRALISKS* pTrainHydras = new BT_ACTION_TRAIN_HYDRALISKS("TrainHydralisks", pMainSeq);

    // Attack Move
    BT_ACTION_ATTACK_MOVE* pAttackMove = new BT_ACTION_ATTACK_MOVE("AttackMove", pMainSeq);

    // Micro Hydralisks
    BT_ACTION_MICRO_HYDRALISKS* pMicroHydras = new BT_ACTION_MICRO_HYDRALISKS("MicroHydralisks", pMainSeq);
}

ZergVsProtoss::~ZergVsProtoss() {
    delete pCombatBT;
}
