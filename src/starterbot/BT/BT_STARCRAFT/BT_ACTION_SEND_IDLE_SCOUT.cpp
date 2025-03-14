#include "BT_ACTION_SEND_IDLE_SCOUT.h"
#include "../Data.h"
#include <BWAPI.h>
#include "../../Tools.h"

BT_ACTION_SEND_IDLE_SCOUT::BT_ACTION_SEND_IDLE_SCOUT(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_SEND_IDLE_SCOUT::Evaluate(void* data) {
    Data* pData = (Data*)data;
    
    // Find an idle worker unit
    for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
        if (unit->getType().isWorker() && unit->isIdle()) {
            // Send the worker to scout, could be a random position or to a known location
            BWAPI::Position scoutPosition = BWAPI::Position(2000, 2000); // Example: Random position for scouting
            unit->rightClick(scoutPosition); // Command worker to move
            
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE; // No idle worker found
}

std::string BT_ACTION_SEND_IDLE_SCOUT::GetDescription() {
    return "Send an idle worker to scout";
}
