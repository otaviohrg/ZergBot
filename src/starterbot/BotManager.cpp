#include "BotManager.h"
#include "Tools.h"
#include "MapTools.h"
#include "BT/Data.h"
#include <format>

#include "BT/BT.h"

BotManager::BotManager()
{
    bb = new Blackboard();
	pBaseModule = new BaseModule();
	pEconomyModule = new EconomyModule();
    pCombatModule = new CombatModule();
    pMicroModule = new MicroModule();
}

// Called when the bot starts!
void BotManager::onStart()
{
    // Set our BWAPI options here    
    BWAPI::Broodwar->setLocalSpeed(10);
    BWAPI::Broodwar->setFrameSkip(0);

    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();

}

// Called on each frame of the game
void BotManager::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

	pEconomyModule->updateEconomy(bb);
	pBaseModule->updateBase(bb);
    pCombatModule->updateCombat(bb);
    pMicroModule->updateMicro();

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

// Draw some relevent information to the screen to help us debug the bot
void BotManager::drawDebugInformation()
{
    BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, World!\n");
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever the game ends and tells you if you won or not
void BotManager::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

// Called whenever a unit is destroyed, with a pointer to the unit
void BotManager::onUnitDestroy(BWAPI::Unit unit)
{
    //if the unit is farming then remove it from data structure
    if (bb->pData->unitsFarmingMinerals.contains(unit)) bb->pData->unitsFarmingMinerals.erase(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void BotManager::onUnitMorph(BWAPI::Unit unit)
{

}

// Called whenever a text is sent to the game by a user
void BotManager::onSendText(std::string text)
{
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void BotManager::onUnitCreate(BWAPI::Unit unit)
{

}

// Called whenever a unit finished construction, with a pointer to the unit
void BotManager::onUnitComplete(BWAPI::Unit unit)
{

}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void BotManager::onUnitShow(BWAPI::Unit unit)
{

}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void BotManager::onUnitHide(BWAPI::Unit unit)
{

}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void BotManager::onUnitRenegade(BWAPI::Unit unit)
{

}