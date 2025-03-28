#ifndef SPEEDLING_RUSH_H
#define SPEEDLING_RUSH_H

#include <BWAPI.h>
#include "../Micro/Squad.h"
#include"utils.h"
#include "../Blackboard.h"
class SpeedlingRush {
public:
    SpeedlingRush();
    void execute();
private:
    Blackboard* blackboard;
    Squad combatSquad;
};

#endif // SPEEDLING_RUSH_H
