#include "StandardEconomyModule.h"

StandardEconomyModule::StandardEconomyModule()
    : BT_DECORATOR("EconomyEntryPoint", nullptr) {
    SetupBehaviorTree();
}

StandardEconomyModule::~StandardEconomyModule() {
    delete pEconomyBT;
}

void StandardEconomyModule::SetupBehaviorTree() {
    // Root behavior tree node
    pEconomyBT = new BT_DECORATOR("EconomyEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEconomyBT, 10);

    // === 1. Worker Training ===
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, false);  // Reset on failure
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = 
        new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);

    // === 2. Gas and Mineral Allocation ===
    BT_DECO_REPEATER* pResourceRepeater = new BT_DECO_REPEATER(
        "RepeatResourceAllocation", pMainSeq, 0, true, false, false);  // Reset on failure
    
    // Allocate workers to gas first
    BT_ACTION_SEND_IDLE_WORKER_TO_GAS* pSendWorkerToGas = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_GAS("SendWorkerToGas", pResourceRepeater);
    
    // Remaining workers should go to minerals
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pResourceRepeater);
}

BT_NODE::State StandardEconomyModule::EvaluateEconomy(void* data) {
    if (pEconomyBT != nullptr) {
        return pEconomyBT->Evaluate(data);  // Start evaluation of economy tree
    }
    return BT_NODE::FAILURE;
}
