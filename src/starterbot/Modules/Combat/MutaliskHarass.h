#ifndef MUTALISK_HARASS_H
#define MUTALISK_HARASS_H

#include <BWAPI.h>
#include "../Micro/Squad.h"
#include "../Blackboard.h"
#include "utils.h"
class MutaliskHarass {
public:
    MutaliskHarass();
    void execute();
private:
    Squad combatSquad;
    Blackboard* blackboard;
};

#endif // MUTALISK_HARASS_H
