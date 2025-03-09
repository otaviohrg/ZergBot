#include "EmergencyEconomyModule.h"

EmergencyEconomyModule::EmergencyEconomyModule() : BT_DECORATOR("EconomyEntryPoint", nullptr) {
    
    // Initialize entry point for the behavior tree
    pEconomyBT = new BT_DECORATOR("EconomyEntryPoint", nullptr);

    // Create a parallel sequence to execute multiple tasks
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEconomyBT, 10);

    // Emergency Mineral Farming task (different from the standard one)
    BT_DECO_REPEATER* pMineralFarmingRepeater = new BT_DECO_REPEATER(
        "RepeatMineralFarming", pMainSeq, 0, true, false, true);  // Adding resetChildOnRepeat
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughMineralsWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("CheckMineralWorkers", pMineralFarmingRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendMineralWorker = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendMineralWorker", pNotEnoughMineralsWorkers);

    // Emergency Worker Training task (maybe different urgency here)
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, true);  // Adding resetChildOnRepeat
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);

    // Emergency specific condition or task can go here...
    // You can add more tasks like repair, build defense, etc.
}

EmergencyEconomyModule::~EmergencyEconomyModule() {
    delete pEconomyBT;  // Clean up the behavior tree
}
