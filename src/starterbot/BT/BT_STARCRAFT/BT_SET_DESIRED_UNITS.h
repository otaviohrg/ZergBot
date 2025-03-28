#pragma once
#include <cassert>
#include "../BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BT_SET_DESIRED_UNITS: public BT_ACTION {
public:
    BT_SET_DESIRED_UNITS(std::string name, BT_NODE* parent, int wantedUnit, std::string unitType);

private:
    int wantedUnit;
    std::string unitType;
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    BT_NODE::State SetDesiredUnits(void* data);
};
//----------