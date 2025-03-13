#include "StandardEconomyModule.h"


StandardEconomyModule::StandardEconomyModule() 
    : BT_DECORATOR("EconomyEntryPoint", nullptr)  // Call base class constructor
{
    // === Root Behavior Tree Node ===
    pEconomyBT = new BT_DECORATOR("EconomyEntryPoint", this);
    BT_PARALLEL_SEQUENCER* pMainSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pEconomyBT, 10);

    // === 1. Standard Mineral Farming Task ===
    BT_DECO_REPEATER* pMineralFarmingRepeater = new BT_DECO_REPEATER(
        "RepeatMineralFarming", pMainSeq, 0, true, false, false);  // Reset on failure
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughMineralsWorkers = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("CheckMineralWorkers", pMineralFarmingRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendMineralWorker = 
        new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendMineralWorker", pNotEnoughMineralsWorkers);

    // === 2. Worker Training Task ===
    BT_DECO_REPEATER* pWorkerTrainingRepeater = new BT_DECO_REPEATER(
        "RepeatWorkerTraining", pMainSeq, 0, true, false, false);  // Reset on failure
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkersCondition = 
        new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("CheckWorkers", pWorkerTrainingRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorkerAction = 
        new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkersCondition);

    // === 3. Expansion Logic (New Base at 20 Supply) ===
    BT_DECO_CONDITION_SUPPLY_REACHED* pExpansionCondition = 
        new BT_DECO_CONDITION_SUPPLY_REACHED("CheckExpansion", pMainSeq, 20);
    BT_ACTION_EXPAND_BASE* pExpandBase = 
        new BT_ACTION_EXPAND_BASE("ExpandBase", pExpansionCondition);

    // === 4. Refinery Construction (Start Gas Collection) ===
    BT_DECO_CONDITION_NEED_GAS* pNeedGasCondition = 
        new BT_DECO_CONDITION_NEED_GAS("CheckGasNeeded", pMainSeq);
    BT_ACTION_BUILD_REFINERY* pBuildRefinery = 
        new BT_ACTION_BUILD_REFINERY("BuildRefinery", pNeedGasCondition);

    // === 5. Supply Depot Management (Prevent Supply Block) ===
    BT_DECO_CONDITION_SUPPLY_NEEDED* pSupplyCheck = 
        new BT_DECO_CONDITION_SUPPLY_NEEDED("CheckSupply", pMainSeq);
    BT_ACTION_BUILD_SUPPLY_DEPOT* pBuildSupplyDepot = 
        new BT_ACTION_BUILD_SUPPLY_DEPOT("BuildSupplyDepot", pSupplyCheck);
}

StandardEconomyModule::~StandardEconomyModule() {
    delete pEconomyBT;  // Clean up behavior tree
}


