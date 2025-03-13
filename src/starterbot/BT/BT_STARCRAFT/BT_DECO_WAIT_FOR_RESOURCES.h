#pragma once
#include <cassert>
#include "../BT_DECORATOR.h"

//The until failure task will keep executing its child task until the child task returns failure.
// 
//--------------------
class BT_DECO_WAIT_FOR_RESOURCES : public BT_DECORATOR {
private:
    std::string buildingType;
public:
    BT_DECO_WAIT_FOR_RESOURCES(std::string name, BT_NODE* parent, std::string buildingType);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
};
//----------