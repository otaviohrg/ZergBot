#pragma once
#include "../Blackboard.h"
#include <BWAPI.h>
#include "../Tools.h"
#include "../BT/BT.h"

class BaseModule
{
private:
	BT_NODE* pBaseBT;
public:
	BaseModule();
	~BaseModule();
    void updateBase(Blackboard *bb);
};
