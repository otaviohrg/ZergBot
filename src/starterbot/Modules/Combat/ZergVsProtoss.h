#ifndef ZERG_VS_PROTOSS_H
#define ZERG_VS_PROTOSS_H

#include "../../BT/BT.h"

class ZergVsProtoss : public BT_DECORATOR {
public:
    ZergVsProtoss();
    ~ZergVsProtoss();
private:
    BT_DECORATOR* pCombatBT;
};

#endif // ZERG_VS_PROTOSS_H
