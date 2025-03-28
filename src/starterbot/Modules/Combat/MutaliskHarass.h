#ifndef MUTALISK_HARASS_H
#define MUTALISK_HARASS_H

#include "BaseCombatStrategy.h"
#include "../../Blackboard.h"
#include "utils.h"
#include <list>

class MutaliskHarass : public BaseCombatStrategy {
public:
    void Evaluate() override;

private:
    std::list<BWAPI::Unit> mutalisks;
    Blackboard* blackboard;
    void recruitMutalisks();
    void harassEnemy();
};

#endif // MUTALISK_HARASS_H
