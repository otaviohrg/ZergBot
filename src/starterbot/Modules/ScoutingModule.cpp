#include "ScoutingModule.h"
#include "../Tools.h"

ScoutingModule::ScoutingModule() {
    pScoutingBT = nullptr;
    pScoutingBT = new BT_DECORATOR("EntryPoint", nullptr);
    BT_SEQUENCER* pSequence = new BT_SEQUENCER("MainSequence", pScoutingBT, 10);

    // Check if there are not enough scouts
    BT_DECO_UNTIL_SUCCESS* pUntilEnoughScouts = new BT_DECO_UNTIL_SUCCESS("UntilEnoughScouts", pSequence);
    BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS* pNotEnoughScouts = new BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS("NotEnoughScouts", pUntilEnoughScouts);
    
    // Action to send idle worker to scout
    BT_ACTION_SEND_IDLE_SCOUT* pSendScout = new BT_ACTION_SEND_IDLE_SCOUT("SendScout", pNotEnoughScouts);

    // Repeat scouting action if scouts are not enough
    BT_DECO_REPEATER* pRepeatScouting = new BT_DECO_REPEATER("RepeatScouting", pSequence, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS* pNotEnoughScouts2 = new BT_DECO_CONDITION_NOT_ENOUGH_SCOUTS("NotEnoughScouts2", pRepeatScouting);
    BT_ACTION_SEND_IDLE_SCOUT* pSendScout2 = new BT_ACTION_SEND_IDLE_SCOUT("SendScout2", pNotEnoughScouts2);

}

ScoutingModule::~ScoutingModule() {
    delete (BT_DECORATOR*)pScoutingBT;
}

void ScoutingModule::updateScouting(Blackboard *bb) {
    bb->pData->currSupply = Tools::GetUnusedSupply(true);
    
    // If the behavior tree has finished running, reset it
    if (pScoutingBT != nullptr && pScoutingBT->Evaluate(bb->pData) != BT_NODE::RUNNING) {
        delete (BT_DECORATOR*)pScoutingBT;
        pScoutingBT = nullptr;
    }
}
