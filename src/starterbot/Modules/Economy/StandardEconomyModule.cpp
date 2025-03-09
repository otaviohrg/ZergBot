#include "StandardEconomyModule.h"

StandardEconomyModule::StandardEconomyModule() 
    : BT_DECORATOR("EconomyEntryPoint", nullptr)  // Call the constructor of BT_DECORATOR with proper arguments
{
    // Create a parallel sequence to execute multiple tasks
    // Create a parallel sequence to execute multiple tasks
    pEconomyBT = new BT_DECORATOR("EconomyEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEconomyBT, 10);

    // Standard Mineral Farming task
    BT_DECO_REPEATER* pMineralFarmingRepeater = new BT_DECO_REPEATER(
        "RepeatMineralFarming", pMainSeq, 0, true, false, true);  // Add the missing argument here
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughMineralsWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("CheckMineralWorkers", pMineralFarmingRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendMineralWorker = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendMineralWorker", pNotEnoughMineralsWorkers);

    // Standard Worker Training task
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, true);  // Add the missing argument here
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);
}

StandardEconomyModule::~StandardEconomyModule() {
    delete pEconomyBT;  // Clean up the behavior tree
}


