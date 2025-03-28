#ifndef HYDRA_BUST_H
#define HYDRA_BUST_H

#include <BWAPI.h>
#include "../Micro/Squad.h"
#include "../Blackboard.h"
#include "utils.h"
class HydraBust {
public:
    HydraBust();
    void execute();
private:
    Squad combatSquad;
    Blackboard* blackboard;
};

#endif // HYDRA_BUST_H
