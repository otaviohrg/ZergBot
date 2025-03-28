#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "SpeedlingRush.h"
#include "HydraHarass.h"
#include "MutaliskHarass.h"

class CombatManager {
public:
    CombatManager();
    void update();
private:
    void executeStrategy();
    BWAPI::Race enemyRace;
};

#endif // COMBAT_MANAGER_H
