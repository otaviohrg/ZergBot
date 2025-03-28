#include "EmergencyEconomyModule.h"

EmergencyEconomyModule::EmergencyEconomyModule()
    : BT_DECORATOR("EconomyEntryPoint", nullptr) {
    SetupEmergencyBehaviorTree();
}

EmergencyEconomyModule::~EmergencyEconomyModule() {
    delete pEmergencyEconomyBT;
}

void EmergencyEconomyModule::SetupEmergencyBehaviorTree() {
    // Root behavior tree node
    pEmergencyEconomyBT = new BT_DECORATOR("EconomyEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEmergencyEconomyBT, 10);

    // === 1. Emergency Worker Training ===
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, false);  // Reset on failure
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = 
        new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);

    // === 2. Emergency Mineral Gathering ===
    BT_DECO_REPEATER* pResourceRepeater = new BT_DECO_REPEATER(
        "RepeatResourceAllocation", pMainSeq, 0, true, false, false);  // Reset on failure
    
    // Send idle workers to minerals
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pResourceRepeater);
    
    // Send workers to gas only if gas is needed and not enough workers are assigned to gas
    BT_ACTION_SEND_IDLE_WORKER_TO_GAS* pSendWorkerToGas = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_GAS("SendWorkerToGas", pResourceRepeater);
}

BT_NODE::State EmergencyEconomyModule::EvaluateEmergencyEconomy(void* data) {
    if (pEmergencyEconomyBT != nullptr) {
        return pEmergencyEconomyBT->Evaluate(data);  // Start evaluation of emergency economy tree
    }
    return BT_NODE::FAILURE;
}
