#pragma once
#include "../Blackboard.h"
#include <BWAPI.h>
#include "../Tools.h"
#include "../BT/BT.h"

class EconomyModule
{
private:
	BT_NODE* pEconomyBT;
public:
	EconomyModule();
	~EconomyModule();
	void updateEconomy(Blackboard *bb);
};