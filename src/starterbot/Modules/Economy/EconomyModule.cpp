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
    std::cout << "Updating economy" << std::endl;
    bb->pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    std::cout << "Current minerals: " << bb->pData->currMinerals << std::endl;
    bb->pData->currGas = BWAPI::Broodwar->self()->gas();
    std::cout << "Current gas: " << bb->pData->currGas << std::endl;
    bb->pData->currentWorkers = BWAPI::Broodwar->self()->allUnitCount();  // Adjust for worker count as necessary
    std::cout << "Current workers: " << bb->pData->currentWorkers << std::endl;

    // Check if we need to switch to emergency economy
    // if (bb->pData->currMinerals < EMERGENCY_MINERAL_THRESHOLD || bb->pData->currentWorkers < EMERGENCY_WORKER_THRESHOLD) {
    //     if (pEconomyBT == nullptr || dynamic_cast<EmergencyEconomyModule*>(pEconomyBT) == nullptr) {
    //         switchToEmergencyEconomy();
    //     }
    // } else {
    //     if (pEconomyBT == nullptr || dynamic_cast<StandardEconomyModule*>(pEconomyBT) == nullptr) {
    //         switchToStandardEconomy();
    //     }
    // }

    if (pEconomyBT != nullptr) {
        std::cout << "Evaluating economy BT" << std::endl;
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
