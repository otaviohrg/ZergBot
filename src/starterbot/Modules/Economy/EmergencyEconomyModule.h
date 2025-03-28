#pragma once
#include <BWAPI.h>
#include "../BT.h"

class EmergencyEconomyModule : public BT_DECORATOR {
public:
    EmergencyEconomyModule();
    ~EmergencyEconomyModule();

private:
    void SetupEmergencyBehaviorTree();
    BT_NODE::State EvaluateEmergencyEconomy(void* data);

    BT_DECORATOR* pEmergencyEconomyBT;
};
