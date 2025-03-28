#ifndef ZERG_VS_ZERG_H
#define ZERG_VS_ZERG_H

#include "../../BT/BT.h"

class ZergVsZerg : public BT_DECORATOR {
public:
    ZergVsZerg();
    ~ZergVsZerg();
private:
    BT_DECORATOR* pCombatBT;

};

#endif // ZERG_VS_ZERG_H
