#ifndef BASE_COMBAT_STRATEGY_H
#define BASE_COMBAT_STRATEGY_H

#include <BWAPI.h>

class BaseCombatStrategy {
public:
    virtual ~BaseCombatStrategy() = default;
    virtual void Evaluate() = 0;
};

#endif // BASE_COMBAT_STRATEGY_H
