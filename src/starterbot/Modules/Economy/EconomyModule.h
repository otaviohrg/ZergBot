#ifndef ECONOMYMODULE_H
#define ECONOMYMODULE_H

#include "../../Tools.h"  // Assuming Tools.h contains useful helper functions
#include "../../BT/BT.h"  // Assuming BT_Decorator.h contains the definition of BT_DECORATOR
#include "../../Blackboard.h"  // Assuming Blackboard.h contains the Blackboard struct
class EconomyModule {
public:
    EconomyModule();
    ~EconomyModule();
    
    void updateEconomy(Blackboard* bb);

private:
    BT_DECORATOR* pEconomyBT;  // Pointer to the base tree

    void switchToStandardEconomy();
    void switchToEmergencyEconomy();
};

#endif // ECONOMYMODULE_H
