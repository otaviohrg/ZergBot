#include "EconomyModule.h"
#include "StandardEconomyModule.h"  // Include standard economy module
#include "EmergencyEconomyModule.h" // Include emergency economy module
#define EMERGENCY_MINERAL_THRESHOLD 50  // Define your threshold value here
#define EMERGENCY_WORKER_THRESHOLD 5    // Similarly, define the worker threshold

EconomyModule::EconomyModule() {
    pEconomyBT = nullptr;
    switchToStandardEconomy();
}

EconomyModule::~EconomyModule() {
    delete pEconomyBT;
}

void EconomyModule::updateEconomy(Blackboard* bb) {
    bb->pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    bb->pData->currentWorkers = BWAPI::Broodwar->self()->allUnitCount();  // Adjust for worker count as necessary

    // Check if we need to switch to emergency economy
    if (bb->pData->currMinerals < EMERGENCY_MINERAL_THRESHOLD || bb->pData->currentWorkers < EMERGENCY_WORKER_THRESHOLD) {
        if (pEconomyBT == nullptr || dynamic_cast<EmergencyEconomyModule*>(pEconomyBT) == nullptr) {
            switchToEmergencyEconomy();
        }
    } else {
        if (pEconomyBT == nullptr || dynamic_cast<StandardEconomyModule*>(pEconomyBT) == nullptr) {
            switchToStandardEconomy();
        }
    }

    if (pEconomyBT != nullptr) {
        pEconomyBT->Evaluate(bb->pData);
    }
}

void EconomyModule::switchToStandardEconomy() {
    delete pEconomyBT;
    pEconomyBT = new StandardEconomyModule();
}

void EconomyModule::switchToEmergencyEconomy() {
    delete pEconomyBT;
    pEconomyBT = new EmergencyEconomyModule();
}
