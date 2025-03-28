#pragma once
#include <BWAPI.h>
#include "../BT.h"

class StandardEconomyModule : public BT_DECORATOR {
public:
    StandardEconomyModule();
    ~StandardEconomyModule();

private:
    void SetupBehaviorTree();
    BT_NODE::State EvaluateEconomy(void* data);

    BT_DECORATOR* pEconomyBT;
};
