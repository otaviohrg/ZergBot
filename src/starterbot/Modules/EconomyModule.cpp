#include "EconomyModule.h"
#include "../Tools.h"

EconomyModule::EconomyModule() {
    pEconomyBT = nullptr;
    pEconomyBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pEconomyBT, 10);

    //Farming Minerals forever
    BT_DECO_REPEATER* pFarmingMineralsForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarmingMinerals", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughWorkersFarmingMinerals = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("NotEnoughWorkersFarmingMinerals", pFarmingMineralsForeverRepeater);
    BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new BT_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pNotEnoughWorkersFarmingMinerals);

    //Training Workers
    BT_DECO_REPEATER* pTrainingWorkersForeverRepeater = new BT_DECO_REPEATER("RepeatForeverTrainingWorkers", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", pTrainingWorkersForeverRepeater);
    BT_ACTION_TRAIN_WORKER* pTrainWorker = new BT_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkers);

}

EconomyModule::~EconomyModule() {
    delete (BT_DECORATOR*)pEconomyBT;
}

void EconomyModule::updateEconomy(Blackboard* bb) {
    bb->updateResources();

    if (pEconomyBT != nullptr && pEconomyBT->Evaluate(bb->pData) != BT_NODE::RUNNING)
    {
        std::cout << "Economy BT is not running" << std::endl;
        delete (BT_DECORATOR*)pEconomyBT;
        pEconomyBT = nullptr;
    }
}