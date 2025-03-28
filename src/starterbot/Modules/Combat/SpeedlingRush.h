#ifndef SPEEDLING_RUSH_H
#define SPEEDLING_RUSH_H

#include "BaseCombatStrategy.h"
#include "../../Blackboard.h"
#include "utils.h"
#include <list>

class SpeedlingRush : public BaseCombatStrategy {
public:
    void Evaluate() override;

private:
    std::list<BWAPI::Unit> zerglings;
    Blackboard* blackboard;
    void recruitZerglings();
    void rushEnemy();
};

#endif // SPEEDLING_RUSH_H
