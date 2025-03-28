#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include "BaseCombatStrategy.h"
#include "MutaliskHarass.h"
#include "HydraBust.h"
#include "SpeedlingRush.h"
#include <BWAPI.h>
#include <memory>

class CombatManager {
public:
    CombatManager();
    ~CombatManager();

    void update();
    void setEnemyRace(BWAPI::Race race);

private:
    std::unique_ptr<BaseCombatStrategy> currentStrategy;
    BWAPI::Race enemyRace;

    void selectStrategy();
};

#endif // COMBAT_MANAGER_H
