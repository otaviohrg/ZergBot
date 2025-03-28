#pragma once

#include "MapTools.h"
#include "BT/BT.h"
#include <BWAPI.h>
#include "BT/Data.h"
#include "Modules/BaseModule.h"
#include "Modules/Economy/EconomyModule.h"
#include "Modules/CombatModule.h"
#include "Modules/Micro/MicroModule.h"
#include "Modules/ScoutingModule.h"
#include "Blackboard.h"


class BotManager
{
private:
	MapTools m_mapTools;
	Blackboard* bb;
	BaseModule* pBaseModule;
	EconomyModule* pEconomyModule;
	CombatModule* pCombatModule;
	MicroModule* pMicroModule;
	ScoutingModule* pScoutingModule;

public:

	BotManager();

	// helper functions to get you started with bot programming and learn the API
	void drawDebugInformation();

	// functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
};