#ifndef HYDRA_BUST_H
#define HYDRA_BUST_H

#include "BaseCombatStrategy.h"
#include "../../Blackboard.h"
#include "utils.h"
#include <list>

class HydraBust : public BaseCombatStrategy {
public:
    void Evaluate() override;

private:
    std::list<BWAPI::Unit> hydralisks;
    Blackboard* blackboard;
    void recruitHydralisks();
    void attackEnemy();
};

#endif // HYDRA_BUST_H
