#pragma once
#include "../Blackboard.h"
#include <BWAPI.h>
#include "../Tools.h"
#include "../BT/BT.h"

class ScoutingModule
{
private:
    BT_NODE* pScoutingBT;  // Root of the behavior tree for scouting
public:
    ScoutingModule();
    ~ScoutingModule();
    
    // Function to update the scouting behavior tree
    void updateScouting(Blackboard* bb);
};
