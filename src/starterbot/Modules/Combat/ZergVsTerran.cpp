#include "ZergVsTerran.h"

ZergVsTerran::ZergVsTerran() 
    : BT_DECORATOR("CombatEntryPoint", nullptr)
{
    pCombatBT = new BT_DECORATOR("CombatEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainCombatSequence", pCombatBT, 10);

    // Train Mutalisks
    BT_ACTION_TRAIN_MUTALISKS* pTrainMutas = new BT_ACTION_TRAIN_MUTALISKS("TrainMutalisks", pMainSeq);

    // Harass Enemy Workers
    BT_ACTION_HARASS_WORKERS* pHarassWorkers = new BT_ACTION_HARASS_WORKERS("HarassWorkers", pMainSeq);

    // Micro Mutalisks
    BT_ACTION_MICRO_MUTALISKS* pMicroMutas = new BT_ACTION_MICRO_MUTALISKS("MicroMutalisks", pMainSeq);
}

ZergVsTerran::~ZergVsTerran() {
    delete pCombatBT;
}
