#include "EconomyModule.h"
#include "../../Tools.h" // Assuming BehaviorTree.h contains necessary node declarations
#include "../../BT/BT.h"
#ifndef STANDARDECONOMYMODULE_H
#define STANDARDECONOMYMODULE_H

class StandardEconomyModule : public BT_DECORATOR {
public:
    StandardEconomyModule();
    ~StandardEconomyModule();

private:
    BT_DECORATOR* pEconomyBT;
};

#endif // STANDARDECONOMYMODULE_H

