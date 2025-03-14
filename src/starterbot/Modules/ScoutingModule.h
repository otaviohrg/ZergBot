#pragma once
#include <BWAPI.h>
#include "../Blackboard.h"
#include "../Tools.h"

class ScoutingModule {
private:
    bool foundEnemyBase = false;  // Flag to track if the enemy base was found
    BWAPI::TilePosition targetLocation;  // Stores the target location for the scout

public:
    ScoutingModule();  // Constructor
    ~ScoutingModule();  // Destructor

    // Send a scout unit to explore a target position
    void SendScoutToExplore(BWAPI::Unit scout, BWAPI::TilePosition target);

    // Find the enemy base location (could be using known spawn locations or based on fog of war)
    BWAPI::TilePosition FindEnemyBase();

    // Update scouting logic: move scouts and check for enemy base
    void UpdateScouting(Blackboard* bb);

    // Handle logic after enemy base is found (e.g., report, attack, expand)
    void ScoutFoundEnemyBase();
};
