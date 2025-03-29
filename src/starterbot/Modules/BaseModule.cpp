#include "BaseModule.h"
#include "../Tools.h"

BaseModule::BaseModule(){
    pBaseBT = nullptr;
    pBaseBT = new BT_SEQUENCER("EntryPoint", nullptr, 50);
    
    //Build Pool after 5th Worker

    BT_SET_DESIRED_SUPPLY* pSetInitialSupply = new BT_SET_DESIRED_SUPPLY("SetSupply", pBaseBT, 10);
    BT_SET_DESIRED_WORKERS* pSetInitialWorkers = new BT_SET_DESIRED_WORKERS("SetWorkers", pBaseBT, 5, 5, 0);
    
    BT_DECO_UNTIL_SUCCESS* pUntil5Drones = new BT_DECO_UNTIL_SUCCESS("Until5Drones", pBaseBT);
    BT_DECO_CONDITION_SUPPLY_REACHED* p5DronesReached = new BT_DECO_CONDITION_SUPPLY_REACHED("5DronesReached", pUntil5Drones, 5);
    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForPool = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForPool", p5DronesReached, "Zerg_Spawning_Pool");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesPool = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForPool, "Zerg_Spawning_Pool");
    BT_ACTION_BUILD_BUILDING* pBuildPool = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResourcesPool, "Zerg_Spawning_Pool");

    BT_SET_DESIRED_SUPPLY* pSetPostPoolSupply = new BT_SET_DESIRED_SUPPLY("SetSupply", pBaseBT, 18);

    BT_SET_DESIRED_WORKERS* pSetPostPoolWorkers = new BT_SET_DESIRED_WORKERS("SetWorkers", pBaseBT, 6, 6, 0);

    BT_SET_DESIRED_UNITS* pSetInitialZerglings = new BT_SET_DESIRED_UNITS("SetLings", pBaseBT, 6, "Zerg_Zergling");

    BT_DECO_UNTIL_SUCCESS* pUntil6Lings = new BT_DECO_UNTIL_SUCCESS("Until6Zerglings", pBaseBT);
    BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS* p6LingsReached = new BT_DECO_CONDITION_WAIT_ENOUGH_ZERGLINGS("6ZerglingsReached", pUntil6Lings);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pBuildOverlord = new BT_ACTION_BUILD_SUPPLY_PROVIDER("BuildOverlord", p6LingsReached);

    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForExtractor = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForExtractor", pBaseBT, "Zerg_Extractor");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesExtractor = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResources", pWaitForExtractor, "Zerg_Extractor");
    BT_ACTION_BUILD_BUILDING* pBuildExtractor = new BT_ACTION_BUILD_BUILDING("BuildPool", pUntilEnoughResourcesExtractor, "Zerg_Extractor");

    BT_DECO_UNTIL_SUCCESS* pUntilUpgradeLair = new BT_DECO_UNTIL_SUCCESS("UntilUpgradeLair", pBaseBT);
    BT_ACTION_UPGRADE_LAIR* pUpgradeLair = new BT_ACTION_UPGRADE_LAIR("UpgradeLair", pUntilUpgradeLair);

    BT_SET_DESIRED_WORKERS* pSetPostExtractorWorkers = new BT_SET_DESIRED_WORKERS("SetWorkers", pBaseBT, 15, 12, 3);

    BT_PARALLEL_SEQUENCER * pMidGameSeq = new BT_PARALLEL_SEQUENCER("MainSequence", pBaseBT, 10);

    BT_DECO_REPEATER* pTrainOverlordsForever = new BT_DECO_REPEATER("RepeatForeverTrainingOverlords", pMidGameSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pTrainOverlordsForever);
    BT_ACTION_BUILD_SUPPLY_PROVIDER* pTrainOverlord = new BT_ACTION_BUILD_SUPPLY_PROVIDER("TrainOverlord", pNotEnoughSupply);

    BT_SELECTOR * pRace = new BT_SELECTOR("Selector", pMidGameSeq, 3);
    
    BT_DECO_CONDITION* pOpponentIsZerg = new BT_DECO_CONDITION("OpponentIsZerg", pRace, Tools::IsEnemyZerg);
    BT_DECO_CONDITION* pOpponentIsTerran = new BT_DECO_CONDITION("OpponentIsTerran", pRace, Tools::IsEnemyTerran);
    BT_DECO_CONDITION* pOpponentIsProtoss = new BT_DECO_CONDITION("OpponentIsProtoss", pRace, Tools::IsEnemyProtoss);

    BT_DECO_UNTIL_SUCCESS* pUntilMetabolicBoost = new BT_DECO_UNTIL_SUCCESS("UntilMetabolicBoost", pOpponentIsZerg);
    BT_ACTION_RESEARCH_METABOLIC_BOOST* pResearchBoost = new BT_ACTION_RESEARCH_METABOLIC_BOOST("MetabolicBoost", pUntilMetabolicBoost);

    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForSpire = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForSpire", pOpponentIsTerran, "Zerg_Spire");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesSpire = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResourcesSpire", pWaitForSpire, "Zerg_Spire");
    BT_ACTION_BUILD_BUILDING* pBuildSpire = new BT_ACTION_BUILD_BUILDING("BuildSpire", pUntilEnoughResourcesSpire, "Zerg_Spire");

    BT_DECO_WAIT_FOR_CONSTRUCTION* pWaitForDen = new BT_DECO_WAIT_FOR_CONSTRUCTION("WaitForDen", pOpponentIsProtoss, "Zerg_Hydralisk_Den");
    BT_DECO_WAIT_FOR_RESOURCES* pUntilEnoughResourcesDen = new BT_DECO_WAIT_FOR_RESOURCES("UntilEnoughResourcesDen", pWaitForDen, "Zerg_Hydralisk_Den");
    BT_ACTION_BUILD_BUILDING* pBuildDen = new BT_ACTION_BUILD_BUILDING("BuildDen", pUntilEnoughResourcesDen, "Zerg_Hydralisk_Den");


}

BaseModule::~BaseModule(){
    delete (BT_DECORATOR*)pBaseBT;
}

void BaseModule::updateBase(Blackboard *bb){
    bb->pData->currSupply = Tools::GetUnusedSupply(true);
    std::cout << "Current Supply: " << bb->pData->currSupply << std::endl;
    if (pBaseBT != nullptr && pBaseBT->Evaluate(bb->pData) != BT_NODE::RUNNING)
    {
        std::cout << "Base BT is not running" << std::endl;
        delete (BT_DECORATOR*)pBaseBT;
        pBaseBT = nullptr;
    }
}