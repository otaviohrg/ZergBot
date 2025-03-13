#include "EmergencyEconomyModule.h"

EmergencyEconomyModule::EmergencyEconomyModule() : BT_DECORATOR("EconomyEntryPoint", nullptr) {
    
    // === Root Behavior Tree Node ===
    pEconomyBT = new BT_DECORATOR("EconomyEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEconomyBT, 10);

    // === 1. Emergency Mineral Farming Task ===
    // Reusing the standard Mineral Farming task with higher urgency (reset on failure)
    BT_DECO_REPEATER* pMineralFarmingRepeater = new BT_DECO_REPEATER(
        "RepeatMineralFarming", pMainSeq, 0, true, false, true);  // Reset on failure for emergency
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughMineralsWorkers = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("CheckMineralWorkers", pMineralFarmingRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendMineralWorker = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendMineralWorker", pNotEnoughMineralsWorkers);

    // === 2. Emergency Worker Training Task ===
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, true);  // Reset on failure for emergency
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = 
        new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);

    // === 3. Emergency Expansion Logic ===
    // Reuse expansion condition but add urgency (trigger at lower supply)
    BT_DECO_CONDITION_SUPPLY_REACHED* pExpansionCondition = 
        new BT_DECO_CONDITION_SUPPLY_REACHED("CheckExpansion", pMainSeq, 15);  // Lower supply threshold
    BT_ACTION_EXPAND_BASE* pExpandBase = 
        new BT_ACTION_EXPAND_BASE("ExpandBase", pExpansionCondition);

    // === 4. Refinery Construction (Emergency Gas Collection) ===
    // Reuse the need gas condition but add urgency in case of gas shortage
    BT_DECO_CONDITION_NEED_GAS* pNeedGasCondition = 
        new BT_DECO_CONDITION_NEED_GAS("CheckGasNeeded", pMainSeq);
    BT_ACTION_BUILD_REFINERY* pBuildRefinery = 
        new BT_ACTION_BUILD_REFINERY("BuildRefinery", pNeedGasCondition);

    // === 5. Emergency Supply Depot Management ===
    // Prevent supply block under emergency conditions
    BT_DECO_CONDITION_SUPPLY_NEEDED* pSupplyCheck = 
        new BT_DECO_CONDITION_SUPPLY_NEEDED("CheckSupply", pMainSeq);
    BT_ACTION_BUILD_SUPPLY_DEPOT* pBuildSupplyDepot = 
        new BT_ACTION_BUILD_SUPPLY_DEPOT("BuildSupplyDepot", pSupplyCheck);

    // Other emergency-specific tasks can be added similarly...
}

EmergencyEconomyModule::~EmergencyEconomyModule() {
    delete pEconomyBT;  // Clean up behavior tree
}
