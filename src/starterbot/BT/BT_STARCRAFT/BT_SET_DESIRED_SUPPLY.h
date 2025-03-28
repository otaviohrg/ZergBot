#pragma once
#include <cassert>
#include "../BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_SET_DESIRED_SUPPLY: public BT_ACTION {
public:
    BT_SET_DESIRED_SUPPLY(std::string name, BT_NODE* parent, int wantedSupply);

private:
	int wantedSupply;
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State SetWantedSupply(void* data);
};
//----------