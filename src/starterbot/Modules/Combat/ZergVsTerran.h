#ifndef ZERG_VS_TERRAN_H
#define ZERG_VS_TERRAN_H

#include "../../BT/BT.h"

class ZergVsTerran : public BT_DECORATOR {
public:
    ZergVsTerran();
    ~ZergVsTerran();
private:
    BT_DECORATOR* pCombatBT;

    // Add more actions as needed
};

#endif // ZERG_VS_TERRAN_H
