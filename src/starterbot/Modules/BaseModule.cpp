#include "BaseModule.h"
#include "../Tools.h"

BaseModule::BaseModule(){
    pBaseBT = nullptr;
    pBaseBT = new BT_SELECTOR("EntryPoint", nullptr, 3);
    BT_DECO_CONDITION* pOpponentIsZerg = new BT_DECO_CONDITION("OpponentIsZerg", pBaseBT, Tools::IsEnemyZerg);
    BT_DECO_CONDITION* pOpponentIsTerran = new BT_DECO_CONDITION("OpponentIsTerran", pBaseBT, Tools::IsEnemyTerran);
    BT_DECO_CONDITION* pOpponentIsProtoss = new BT_DECO_CONDITION("OpponentIsProtoss", pBaseBT, Tools::IsEnemyProtoss);
    
    ///Vs Terran - 5 Pool

    //Build Pool after 5th Worker
    BT_SEQUENCER* pSequenceTerran = new BT_SEQUENCER("TerranSequence", pOpponentIsTerran, 20);

    BT_SET_DESIRED_SUPPLY* pSetInitialSupply = new BT_SET_DESIRED_SUPPLY("SetSupply", pSequenceTerran, 10);
    BT_SET_DESIRED_WORKERS* pSetInitialWorkers = new BT_SET_DESIRED_WORKERS("SetWorkers", pSequenceTerran, 5, 5, 0);
    
    BT_DECO_UNTIL_SUCCESS* pUntil5Drones = new BT_DECO_UNTIL_SUCCESS("Until5Drones", pSequenceTerran);
    BT_DECO_CONDITION_SUPPLY_REACHED* p5DronesReached = new BT_DECO_CONDITION_SUPPLY_REACHED("5DronesReached", pUntil5Drones, 5);
    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForPool = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForPool", p5DronesReached, "Zerg_Spawning_Pool");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesPool = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForPool, "Zerg_Spawning_Pool");
    BT_ACTION_BUILD_BUILDING* pBuildPool = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResourcesPool, "Zerg_Spawning_Pool");

    BT_SET_DESIRED_SUPPLY* pSetPostPoolSupply = new BT_SET_DESIRED_SUPPLY("SetSupply", pSequenceTerran, 18);

    BT_SET_DESIRED_WORKERS* pSetPostPoolWorkers = new BT_SET_DESIRED_WORKERS("SetWorkers", pSequenceTerran, 6, 6, 0);

    BT_SET_DESIRED_UNITS* pSetInitialZerglings = new BT_SET_DESIRED_UNITS("SetLings", pSequenceTerran, 6, "Zerg_Zergling");

    BT_DECO_UNTIL_SUCCESS* pUntil6Lings = new BT_DECO_UNTIL_SUCCESS("Until6Zerglings", pSequenceTerran);
    BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS* p9SupplyReached = new BT_DECO_CONDITION_NOT_ENOUGH_ZERGLINGS("6LingsReached", pUntil6Lings);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildOverlord = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildOverlord", p9SupplyReached);

    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForExtractor = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForExtractor", pSequenceTerran, "Zerg_Extractor");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesExtractor = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForExtractor, "Zerg_Extractor");
    BT_ACTION_BUILD_BUILDING* pBuildExtractor = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResourcesExtractor, "Zerg_Extractor");




    /*
    //Build Pool after 9th Worker
    BT_DECO_UNTIL_SUCCESS* pUntil9Workers = new BT_DECO_UNTIL_SUCCESS("Until9Workers", pSequence);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pUntil9Workers);
    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForPool = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForPool", pNotEnoughSupply, "Zerg_Spawning_Pool");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResources = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForPool, "Zerg_Spawning_Pool");
    BT_ACTION_BUILD_BUILDING* pBuildSupplyProvider = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResources, "Zerg_Spawning_Pool");

    //Build Overlord
    BT_DECO_UNTIL_SUCCESS* pUntilBuildOverlord = new BT_DECO_UNTIL_SUCCESS("Until9Workers", pSequence);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildOverlord = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildOverlord", pUntilBuildOverlord);

    //Build Overlord if not enough supply
    BT_DECO_REPEATER* pRepeatOverlord = new BT_DECO_REPEATER("RepeatOverlordProducing", pSequence, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply2 = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pRepeatOverlord);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildOverlord2 = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildOverlord", pNotEnoughSupply2);
    */
    

}

BaseModule::~BaseModule(){
    delete (BT_DECORATOR*)pBaseBT;
}

void BaseModule::updateBase(Blackboard *bb){
    bb->pData->currSupply = Tools::GetUnusedSupply(true);

    if (pBaseBT != nullptr && pBaseBT->Evaluate(bb->pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pBaseBT;
        pBaseBT = nullptr;
    }
}