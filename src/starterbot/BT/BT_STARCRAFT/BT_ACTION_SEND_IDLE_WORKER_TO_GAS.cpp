#include "BT_ACTION_SEND_IDLE_WORKER_TO_GAS.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_ACTION_SEND_IDLE_WORKER_TO_GAS::BT_ACTION_SEND_IDLE_WORKER_TO_GAS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

std::string BT_ACTION_SEND_IDLE_WORKER_TO_GAS::GetDescription() {
    return "ACTION_SEND_IDLE_WORKER_TO_GAS";
}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_GAS::Evaluate(void* data) {
    return SendIdleWorkerToGas(data);
}

BT_NODE::State BT_ACTION_SEND_IDLE_WORKER_TO_GAS::SendIdleWorkerToGas(void* data) {
    Data* pData = (Data*)data;

    // Find an idle worker
    for (auto& worker : BWAPI::Broodwar->self()->getUnits()) {
        if (worker->getType().isWorker() && worker->isIdle()) {

            // Find a refinery to send the worker to
            for (auto& refinery : BWAPI::Broodwar->self()->getUnits()) {
                if (refinery->getType().isRefinery() && refinery->exists()) {
                    
                    // Send the worker to gather gas
                    worker->rightClick(refinery);
                    pData->unitsFarmingGas.insert(worker);
                    
                    return BT_NODE::SUCCESS;
                }
            }
        }
    }

    return BT_NODE::FAILURE; // No idle workers or no refineries found
}
