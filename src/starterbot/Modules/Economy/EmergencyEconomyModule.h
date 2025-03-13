#ifndef EMERGENCYEconomyModule_H
#define EMERGENCYEconomyModule_H

#include "../../Tools.h"   // Include necessary tools
#include "../../BT/BT.h"   // Assuming you have the BT structure defined

class EmergencyEconomyModule : public BT_DECORATOR {
public:
    EmergencyEconomyModule();
    ~EmergencyEconomyModule();

private:
    BT_DECORATOR* pEconomyBT;  // Base behavior tree for the economy module
};

#endif // EMERGENCYEconomyModule_H
